/*
  devicepool_c.cpp:

  (C) Copyright 2013 by OSB AG and developing partners

  See the repository-log for details on the authors and file-history.
  (Repository information can be found at <http://isoaglib.com/download>)

  Use, modification and distribution are subject to the GNU General
  Public License with exceptions for ISOAgLib. (See accompanying
  file LICENSE.txt or copy at <http://isoaglib.com/download/license>)
*/

#include "devicepool_c.h"
#include <IsoAgLib/comm/Part10_TaskController_Client/impl/tcclient_c.h>


namespace __IsoAgLib {


  /* --- DeviceObject_c -------------------------------------------------- */

  uint16_t DeviceObject_c::m_objIdCounter = 1;

  DeviceObject_c::DeviceObject_c( const IsoAgLib::ProcData::DeviceObjectType_t type, const char* desig )
    : m_objectType( type ),
      m_objectId( ( type == IsoAgLib::ProcData::ObjectTypeDVC )? 0 : m_objIdCounter ),
      m_designator( NULL ) {

    isoaglib_assert( m_objectId != 0xFFFF );
    setDesignator( desig );
    if ( m_objectType != IsoAgLib::ProcData::ObjectTypeDVC )
      m_objIdCounter++;
  }


  void DeviceObject_c::setDesignator( const char* desig ) {
    isoaglib_assert( desig );
    isoaglib_assert( CNAMESPACE::strlen( desig ) <= 32 );
    m_designator = desig;
  }


  void DeviceObject_c::format( TcClientConnection_c::ByteStreamBuffer_c& byteStream ) const {
    static const char* deviceLabels[] = { "DVC", "DET", "DPD", "DPT", "DVP" };

    byteStream.format( ( const uint8_t* )deviceLabels[m_objectType], 3 );
    byteStream.format( m_objectId );
  }


  uint32_t DeviceObject_c::getSize() const {
    return ( sizeof( m_objectId ) + 3 /* label */ );
  }

  /* --- Dvc -------------------------------------------------------------*/
  DeviceObjectDvc_c::DeviceObjectDvc_c( const char* version, const char* desig )
    : __IsoAgLib::DeviceObject_c( IsoAgLib::ProcData::ObjectTypeDVC, desig )
    , m_version( version )
    , m_serialNumber( "" ) {
    isoaglib_assert( CNAMESPACE::strlen( version ) <= 32 );
    std::memset( ( void* )&m_localization, 0, sizeof( m_localization ) );
    m_localization.reserved = 0xff; // Reserved field
  }


  void DeviceObjectDvc_c::setLocalSettings( const localSettings_s& currentSettings ) {
    Localization_s localSettings;

    localSettings.language[0] = currentSettings.languageCode >> 8;
    localSettings.language[1] = currentSettings.languageCode & 0xff;

    localSettings.dateFormat = currentSettings.dFormat;

    localSettings.numberFormat =  ( ( currentSettings.nDecimalPoint & 3 ) << 6 );
    localSettings.numberFormat |= ( ( currentSettings.nTimeFormat & 3 ) << 4 );

    localSettings.unitsFormatLow  = ( ( currentSettings.uDistance & 3 ) << 6 );
    localSettings.unitsFormatLow |= ( ( currentSettings.uArea     & 3 ) << 4 );
    localSettings.unitsFormatLow |= ( ( currentSettings.uVolume   & 3 ) << 2 );
    localSettings.unitsFormatLow |= ( ( currentSettings.uMass     & 3 ) );

    localSettings.unitsFormatHigh  = ( ( currentSettings.uTemperature & 3 ) << 6 );
    localSettings.unitsFormatHigh |= ( ( currentSettings.uPressure & 3 )    << 4 );
    localSettings.unitsFormatHigh |= ( ( currentSettings.uForce & 3 )       << 2 );
    localSettings.unitsFormatHigh |= ( ( currentSettings.uUnitsSystem & 3 ) );

    localSettings.reserved = 0xff;

    setLocalization( localSettings );
  }


  void DeviceObjectDvc_c::setLocalization( const Localization_s& local ) {
    //if (std::memcmp((void*)&local, (void*)&m_Localization, sizeof(Localization_s)) != 0)
    // setDirty(true);
    m_localization = local;
  }


  void DeviceObjectDvc_c::setStructureLabel( const uint8_t* label ) {
    m_structLabel.Byte1 = label[0];
    m_structLabel.Byte2 = label[1];
    m_structLabel.Byte3 = label[2];
    m_structLabel.Byte4 = label[3];
    m_structLabel.Byte5 = label[4];
    m_structLabel.Byte6 = label[5];
    m_structLabel.Byte7 = label[6];
  }


  void DeviceObjectDvc_c::setStructureLabel( const char* label ) {
    if( CNAMESPACE::strlen( label ) > 6 ) {
      setStructureLabel( ( const uint8_t* ) label );
    } else {
      uint8_t tmpBuf[7] = {0, 0, 0, 0, 0, 0, 0};
      for( unsigned int i = 0; i < CNAMESPACE::strlen( label ); i++ ) {
        tmpBuf[i] = label[i];
      }
      setStructureLabel( tmpBuf );
    }
  }


  void
  DeviceObjectDvc_c::formatBytestream( TcClientConnection_c::ByteStreamBuffer_c& byteStream ) const {
    DeviceObject_c::format( byteStream );

    byteStream.format( m_designator );
    byteStream.format( m_version );
    byteStream.format( m_wsmName.outputString(), 8 );
    byteStream.format( m_serialNumber );

    byteStream.format( ( uint8_t* )&m_structLabel, 7 );
    byteStream.format( ( uint8_t* )&m_localization, 7 );
  }


  uint32_t DeviceObjectDvc_c::getSize() const {
    uint32_t size = DeviceObject_c::getSize();
    size += sizeof( uint8_t ) + CNAMESPACE::strlen( getDesignator() );
    size += sizeof( uint8_t ) + CNAMESPACE::strlen( getVersion() );
    size += 8; // m_wsmName;
    size += sizeof( uint8_t ) + CNAMESPACE::strlen( getSerialNumber() );
    size += 14; /*  m_structLabel + m_localization */
    return size;
  }

  /* --- Det -------------------------------------------------------------*/

  DeviceObjectDet_c::DeviceObjectDet_c( uint16_t pid, uint16_t element, uint8_t type, const char* desig )
    : DeviceObject_c( IsoAgLib::ProcData::ObjectTypeDET, desig )
    , m_type( type )
    , m_elementNumber( element )
    , m_parentId( pid )
  {}


  void DeviceObjectDet_c::formatBytestream( TcClientConnection_c::ByteStreamBuffer_c& byteStream ) const {
    DeviceObject_c::format( byteStream );

    byteStream.format( uint8_t( m_type ) );
    byteStream.format( m_designator );
    byteStream.format( m_elementNumber );
    byteStream.format( m_parentId );
    byteStream.format( ( uint16_t )m_childList.size() );

    std::vector<uint16_t>::const_iterator it;
    for ( it = m_childList.begin(); it != m_childList.end(); it++ )
      byteStream.format( *it );
  }


  bool DeviceObjectDet_c::addChild( uint16_t childId ) {
    std::vector<uint16_t>::iterator it;
    for ( it = m_childList.begin(); it != m_childList.end(); it++ ) {
      if ( *it == childId )
        return true;
    }

    const size_t oldSize = m_childList.size();
    m_childList.push_back( childId );
    return m_childList.size() > oldSize;
  }


  uint32_t DeviceObjectDet_c::getSize() const {
    uint32_t size = DeviceObject_c::getSize();
    size += sizeof( m_type );
    size += sizeof( uint8_t ) + CNAMESPACE::strlen( getDesignator() );
    size += sizeof( m_elementNumber ) + sizeof( m_parentId );
    size += sizeof( uint16_t ); /* m_childList.size() */
    size += sizeof( uint16_t ) * m_childList.size();
    return size;
  }


  /* --- Dpd -------------------------------------------------------------*/

  DeviceObjectDpd_c::DeviceObjectDpd_c( uint16_t ddi, const IsoAgLib::ProcData::Properties_t& bitmaskProps,
                                        const IsoAgLib::ProcData::Methods_t& bitmaskMethods, const char* desig, const DeviceObjectDvp_c* dvp )
    : DeviceObject_c( IsoAgLib::ProcData::ObjectTypeDPD, desig )
    , m_ddi( ddi )
    , m_properties( bitmaskProps.getByte( 0 ) )
    , m_method( bitmaskMethods.getByte( 0 ) )
    , m_dvpObjectId( ( dvp ) ? dvp->getObjectId() : 0xFFFF ) {}


  void DeviceObjectDpd_c::formatBytestream( TcClientConnection_c::ByteStreamBuffer_c& byteStream ) const {
    DeviceObject_c::format( byteStream );

    byteStream.format( m_ddi );
    byteStream.format( m_properties );
    byteStream.format( m_method );
    byteStream.format( m_designator );
    byteStream.format( m_dvpObjectId );
  }


  uint32_t DeviceObjectDpd_c::getSize() const {
    return ( DeviceObject_c::getSize() + sizeof( m_ddi ) + sizeof( m_properties ) + sizeof( m_method )
             + sizeof( uint8_t ) + CNAMESPACE::strlen( getDesignator() )
             + sizeof( m_dvpObjectId ) );
  }


  /* --- Dpt -------------------------------------------------------------*/

  DeviceObjectDpt_c::DeviceObjectDpt_c( uint16_t ddi, int32_t value, const char* desig, const DeviceObjectDvp_c* dvpRef )
    : DeviceObject_c( IsoAgLib::ProcData::ObjectTypeDPT, desig )
    , m_ddi( ddi )
    , m_value( value )
    , m_dvpObjectId( ( dvpRef ) ? dvpRef->getObjectId() : 0xFFFF )
  {}


  void DeviceObjectDpt_c::formatBytestream( TcClientConnection_c::ByteStreamBuffer_c& byteStream ) const {
    DeviceObject_c::format( byteStream );

    byteStream.format( m_ddi );
    byteStream.format( m_value );
    byteStream.format( m_designator );
    byteStream.format( m_dvpObjectId );
  }

  uint32_t DeviceObjectDpt_c::getSize() const {
    return ( DeviceObject_c::getSize() + sizeof( m_ddi ) + sizeof( m_value )
             + sizeof( uint8_t ) + CNAMESPACE::strlen( m_designator )
             + sizeof( m_dvpObjectId ) );
  }


  /* --- Dvp -------------------------------------------------------------*/

  DeviceObjectDvp_c::DeviceObjectDvp_c( float scale, int32_t offset, uint8_t decimals, const char* desig )
    : DeviceObject_c( IsoAgLib::ProcData::ObjectTypeDVP, desig )
    , m_offset( offset )
    , m_scale( scale )
    , m_decimals( decimals )
    , m_isDirty( false )
  {}


  void DeviceObjectDvp_c::formatBytestream( TcClientConnection_c::ByteStreamBuffer_c& byteStream ) const {
    DeviceObject_c::format( byteStream );

    byteStream.format( m_offset );
    byteStream.format( m_scale );
    byteStream.format( m_decimals );
    byteStream.format( m_designator );
  }


  uint32_t DeviceObjectDvp_c::getSize() const {
    return ( DeviceObject_c::getSize() + sizeof( m_offset ) + sizeof( m_scale ) + sizeof( m_decimals ) + sizeof( uint8_t ) + CNAMESPACE::strlen( getDesignator() ) ) ;
  }

  /* --- DevicePool_c --------------------------------------------------- */

  DevicePool_c::DevicePool_c() : m_identItem( 0 ) {
    m_devicePool.clear();
  }


  void DevicePool_c::init( IdentItem_c& ident ) {
    getDvcObject()->init( ident );
    m_identItem = &ident;
  }


  DeviceObjectDvc_c* DevicePool_c::getDvcObject() const {
    return static_cast<DeviceObjectDvc_c*>( getObject( 0, IsoAgLib::ProcData::ObjectTypeDVC ) );
  }


  DeviceObject_c* DevicePool_c::getObject( const uint16_t objId, const IsoAgLib::ProcData::DeviceObjectType_t objectType ) const {
    deviceMap_t::const_iterator it = m_devicePool.find( objId );
    if( ( it != m_devicePool.end() ) && ( it->second && it->second->getObjectType() == objectType ) ) {
      return it->second;
    }
    return NULL;
  }


  bool DevicePool_c::add( DeviceObject_c& devObj ) {
    return( ! m_devicePool.insert( STL_NAMESPACE::pair<uint16_t, DeviceObject_c*>( devObj.getObjectId(), &devObj ) ).second );
  }


  bool DevicePool_c::add( ProcData_c& pd ) {
    isoaglib_assert(pd.getDpd());
    const bool foundDpd = m_devicePool.find( pd.getDpd()->getObjectId() ) != m_devicePool.end();
    isoaglib_assert( foundDpd );
    const bool foundDet = m_devicePool.find( pd.getDet()->getObjectId() ) != m_devicePool.end();
    isoaglib_assert( foundDet );

    const bool foundObj = foundDet && foundDpd;

    if( foundObj ) {
      m_procDatas.push_back( &pd );
    }
    return foundObj;
  }

  void DevicePool_c::changeDesignator( DeviceObject_c& obj, const char* str ) {
    obj.setDesignator( str );
    getTcClientInstance( m_identItem->getMultitonInst() ).processChangeDesignator( *m_identItem, obj.getObjectId(), str );
  }


  void DevicePool_c::setLocalSettings( const localSettings_s& l ) {
    getDvcObject()->setLocalSettings( l );
    // @todo: call TcClient_c function (partial Pool-Upload will be triggered)
  }


  void DevicePool_c::updateLocale() {
#if 0
    deviceMap_t::iterator it;
    for ( it = m_devicePool.begin(); it != m_devicePool.end(); it++ ) {
      if ( it->second && it->second->getObjectType() == IsoAgLib::ProcData::ObjectTypeDVP )
        static_cast<IsoAgLib::iDeviceObjectDvp_c*>( it->second )->setDirty( true );
    }
#endif
  }


  TcClientConnection_c::ByteStreamBuffer_c DevicePool_c::getBytestream( uint8_t cmd ) {
    const uint32_t size = getBytestreamSize() + 1; // one extra byte for command
    TcClientConnection_c::ByteStreamBuffer_c buffer;
    buffer.setBuffer( allocByteStreamBuffer( size ) );
    buffer.setSize( size );
    buffer.format( cmd );

    for ( deviceMap_t::iterator it = m_devicePool.begin(); it != m_devicePool.end(); it++ ) {
      DeviceObject_c* devObject = it->second;
      devObject->formatBytestream( buffer );
    }

    return buffer;
  }


  uint32_t DevicePool_c::getBytestreamSize() const {
    uint32_t size = 0;
    for ( deviceMap_t::const_iterator it = m_devicePool.begin(); it != m_devicePool.end(); it++ ) {
      DeviceObject_c* devObject = it->second;
      size += devObject->getSize();
    }
    return size;
  }
}