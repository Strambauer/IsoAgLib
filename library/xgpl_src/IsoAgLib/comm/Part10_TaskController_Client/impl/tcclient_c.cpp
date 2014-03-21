/*
  tcclient_c.cpp: central managing instance for all Task Controller-Clients

  (C) Copyright 2009 - 2013 by OSB AG and developing partners

  See the repository-log for details on the authors and file-history.
  (Repository information can be found at <http://isoaglib.com/download>)

  Use, modification and distribution are subject to the GNU General
  Public License with exceptions for ISOAgLib. (See accompanying
  file LICENSE.txt or copy at <http://isoaglib.com/download/license>)
*/
#include "tcclient_c.h"

#include <IsoAgLib/comm/impl/isobus_c.h>
#include <IsoAgLib/comm/Part5_NetworkManagement/impl/isoitem_c.h>
#include <IsoAgLib/comm/Part10_TaskController_Client/impl/processpkg_c.h>
#include <IsoAgLib/comm/Part10_TaskController_Client/impl/procdata/procdata_c.h>
#include <IsoAgLib/util/iassert.h>

#include <list>

#if defined(_MSC_VER)
#pragma warning( disable : 4355 )
#endif

namespace __IsoAgLib {

  TcClient_c&
  getTcClientInstance( uint8_t instance ) {
    MACRO_MULTITON_GET_INSTANCE_BODY( TcClient_c, PRT_INSTANCE_CNT, instance );
  }

  TcClient_c::TcClient_c()
    : m_handler( *this )
    , m_customer( *this )
    , m_stateHandler( NULL )
    , m_pdMessageHandler( NULL )
    , m_identdata()
    , m_server()
  {
  }

        
  void
  TcClient_c::init() {
    isoaglib_assert ( !initialized() );

    __IsoAgLib::getIsoMonitorInstance4Comm().registerControlFunctionStateHandler( m_handler );
#ifdef HAL_USE_SPECIFIC_FILTERS
    getIsoBusInstance4Comm().insertFilter( m_customer, IsoAgLib::iMaskFilter_c( ( 0x3FFFF00UL ), ( PROCESS_DATA_PGN | 0xFF ) << 8 ), 8 );
#else
    getIsoBusInstance4Comm().insertFilter( m_customer, IsoAgLib::iMaskFilter_c( ( 0x3FF0000UL ), PROCESS_DATA_PGN << 8 ), 8 );
#endif

    setInitialized();
  }


  void
  TcClient_c::close() {
    isoaglib_assert ( initialized() );

#ifdef HAL_USE_SPECIFIC_FILTERS
    getIsoBusInstance4Comm().deleteFilter( m_customer, IsoAgLib::iMaskFilter_c( ( 0x3FFFF00UL ), ( PROCESS_DATA_PGN | 0xFF ) << 8 ) );
#else
    getIsoBusInstance4Comm().deleteFilter( m_customer, IsoAgLib::iMaskFilter_c( ( 0x3FF0000UL ), PROCESS_DATA_PGN << 8 ) );
#endif

    getIsoMonitorInstance4Comm().deregisterControlFunctionStateHandler( m_handler );

    setClosed();
  }


  void
  TcClient_c::setServerStateHandler( ServerStateHandler_c& hdl ) {
    isoaglib_assert ( m_stateHandler == NULL );

    m_stateHandler = &hdl;
  }


  void
  TcClient_c::clearServerStateHandler()
  {
    isoaglib_assert( m_stateHandler != NULL );

    m_stateHandler = NULL;
  }


  void
  TcClient_c::setPdMessageHandler( PdMessageHandler_c& hdl ) {
    isoaglib_assert ( m_pdMessageHandler == NULL );

    m_pdMessageHandler = &hdl;
  }


  void
  TcClient_c::clearPdMessageHandler()
  {
    isoaglib_assert( m_pdMessageHandler != NULL );

    m_pdMessageHandler = NULL;
  }


  TcClientConnection_c*
  TcClient_c::connect( IdentItem_c& identItem, TcClientConnection_c::StateHandler_c& sh, const IsoItem_c& tcdl, DevicePool_c& pool ) {
    STL_NAMESPACE::map<const IsoItem_c*,ServerInstance_c*>::iterator server = m_server.find( &tcdl );
    isoaglib_assert( server != m_server.end() );

    identData_t* data = getDataFor( identItem );
    if( ! data ) {
      m_identdata.push_back( identData_t() );
      data = &( m_identdata.back() );
      data->ident = &identItem;
    } else {
      // check for connections between this ident and the given server
      for( STL_NAMESPACE::list<TcClientConnection_c*>::iterator c = data->connections.begin(); c != data->connections.end(); ++c ) {
        if( ( *c )->getServerName() == tcdl.isoName() ) {
          isoaglib_assert( !"Double connect between one IdentItem_c and server detected!" );
          return 0;
        }
      }
    }

    // setup connection
    TcClientConnection_c* c = new TcClientConnection_c( identItem, *this, sh, *(server->second), pool );
    data->connections.push_back( c );

    return c;
  }


  void
  TcClient_c::disconnect( IdentItem_c& identItem ) {
    STL_NAMESPACE::list<identData_t>::iterator i = m_identdata.begin();
    for( ; i != m_identdata.end(); ++i ) {
      if( i->ident == &identItem ) {
        break;
      }
    }
    isoaglib_assert( i != m_identdata.end() );

    for ( STL_NAMESPACE::list<TcClientConnection_c*>::const_iterator it = ( *i ).connections.begin();
        it != ( *i ).connections.end(); ++it ) {
      delete( *it );
    }

    m_identdata.erase( i );
  }


  void
  TcClient_c::processMsg( const CanPkg_c& data ) {
    ProcessPkg_c pkg( data, getMultitonInst() );

    if( ! pkg.isValid() || ( pkg.getMonitorItemForSA() == NULL ) )
      return;

    if (m_pdMessageHandler)
        m_pdMessageHandler->_eventPdMessageReceived(
            *pkg.getMonitorItemForSA(),
            pkg.getMonitorItemForDA(),
            pkg.men_command,
            pkg.mui16_element,
            pkg.mui16_DDI,
            pkg.mi32_pdValue);

    if( pkg.getMonitorItemForDA() != NULL )
      processMsgNonGlobal( pkg );
    else
      processMsgGlobal( pkg );
  }


  void
  TcClient_c::processMsgGlobal( const ProcessPkg_c& data ) {
    if ( data.men_command == IsoAgLib::ProcData::taskControllerStatus ) {
      processTcStatusMsg( data[4], *data.getMonitorItemForSA() );
    }
  }


  void
  TcClient_c::processMsgNonGlobal( const ProcessPkg_c& pkg ) {
    identData_t* identData = getDataFor( *pkg.getMonitorItemForDA() );

    if( ! identData ) {
      return;
    }

    for( STL_NAMESPACE::list<TcClientConnection_c*>::const_iterator it = identData->connections.begin();
         it != identData->connections.end(); ++it )
    {
      if( ( ( *it )->getServer() == NULL) || (pkg.getMonitorItemForSA() != &( *it )->getServer()->getIsoItem()) )
        continue;

      ( *it )->processProcMsg( pkg );
    }
  }


  void
  TcClient_c::reactOnIsoItemModification( ControlFunctionStateHandler_c::iIsoItemAction_e action, IsoItem_c const& isoItem ) {
    if( ( action == ControlFunctionStateHandler_c::RemoveFromMonitorList ) &&( ! isoItem.itemState( IState_c::Local ) ) ) {
      STL_NAMESPACE::map<const IsoItem_c*,ServerInstance_c*>::iterator i = m_server.find( &isoItem );
      if( i != m_server.end() ) {
        delete i->second;
        m_server.erase( i );
      }
    }
  }


  void
  TcClient_c::processTcStatusMsg( uint8_t tcStatus, const __IsoAgLib::IsoItem_c& sender ) {
    STL_NAMESPACE::map<const IsoItem_c*,ServerInstance_c*>::iterator server = m_server.find( &sender );

    if( server == m_server.end() ) {
      IsoAgLib::ProcData::RemoteType_t ecuType; 
      switch (sender.isoName().getEcuType()) {
        case IsoName_c::ecuTypeTaskControl:
          ecuType = IsoAgLib::ProcData::RemoteTypeTaskController;
          break;
        case IsoName_c::ecuTypeDataLogger:
          ecuType = IsoAgLib::ProcData::RemoteTypeDataLogger;
          break;
        default:
          return;
      }

      m_server[ &sender ] = new ServerInstance_c( sender, ecuType );
      server = m_server.find( &sender );
      if (m_stateHandler)
        m_stateHandler->_eventServerAvailable( sender, ecuType );

      // check for connections that used this server. Re add those connections to that server
      // and set to initial state
      for( STL_NAMESPACE::list<identData_t>::iterator i = m_identdata.begin(); i != m_identdata.end(); ++i ) {
        for( STL_NAMESPACE::list<TcClientConnection_c*>::iterator c = i->connections.begin(); c != i->connections.end(); ++c ) {
          if( ( *c )->getServerName() == sender.isoName() ) {
            server->second->addConnection( **c );
            (*c)->setServer( server->second );
            (*c)->setDevPoolState( TcClientConnection_c::PoolStateInit );
          }
        }
      }
    }

    server->second->processStatus( tcStatus );
  }


  void
  TcClient_c::processChangeDesignator( IdentItem_c& ident, uint16_t objID, const char* newDesig ) {
    identData_t* identData = getDataFor( ident );
    isoaglib_assert( identData );

    STL_NAMESPACE::list<TcClientConnection_c*>::const_iterator it = identData->connections.begin();
    while ( it != identData->connections.end() ) {
      if ( &ident == &( ( *it )->getIdentItem() ) )
        ( *it )->sendCommandChangeDesignator( objID, newDesig, CNAMESPACE::strlen( newDesig ) );
      ++it;
    }
  }


  TcClient_c::identData_t*
  TcClient_c::getDataFor( IsoItem_c& item ) {
    STL_NAMESPACE::list<identData_t>::iterator i = m_identdata.begin();
    for( ; i != m_identdata.end(); ++i ) {
      if( i->ident->getIsoItem() == &item ) {
        return &( *i );
      }
    }
    return 0;
  }


  void TcClient_c::sendPdMessage( const IsoItem_c& sa_item, const IsoItem_c* da_item, IsoAgLib::ProcData::CommandType_t command, uint16_t element, uint16_t ddi, int32_t value )
  {
    isoaglib_assert(command < IsoAgLib::ProcData::CommandUndefined);

    ProcessPkg_c pkg( command, element, ddi, value );

    pkg.setMonitorItemForDA( const_cast<IsoItem_c*>( da_item ));
    pkg.setMonitorItemForSA( const_cast<IsoItem_c*>( &sa_item ));

    getIsoBusInstance4Comm() << pkg;
  }

#ifdef HAL_USE_SPECIFIC_FILTERS
  void TcClient_c::receivePdMessage(const IsoItem_c& sa_item, const IsoItem_c* da_item, IsoAgLib::ProcData::CommandType_t command, uint16_t element, uint16_t ddi, int32_t value)
  {
    if (m_pdMessageHandler)
      m_pdMessageHandler->_eventPdMessageReceived(sa_item, da_item, command, element, ddi, value);
  }
#endif

} // __IsoAgLib
