/*
  connectedpd_c.cpp: object for connection-associated Pd-instance

  (C) Copyright 2014 - 2019 by OSB AG

  See the repository-log for details on the authors and file-history.
  (Repository information can be found at <http://isoaglib.com/download>)

  Usage under Commercial License:
  Licensees with a valid commercial license may use this file
  according to their commercial license agreement. (To obtain a
  commercial license contact OSB AG via <http://isoaglib.com/en/contact>)

  Usage under GNU General Public License with exceptions for ISOAgLib:
  Alternatively (if not holding a valid commercial license)
  use, modification and distribution are subject to the GNU General
  Public License with exceptions for ISOAgLib. (See accompanying
  file LICENSE.txt or copy at <http://isoaglib.com/download/license>)
*/
#include "connectedpd_c.h"
#include <IsoAgLib/comm/Part10_TaskController_Client/impl/pdconnection_c.h>
#include <IsoAgLib/comm/Part10_TaskController_Client/impl/procdata/pdbase_c.h>
#include <IsoAgLib/comm/Part10_TaskController_Client/impl/procdata/measurement_c.h>


namespace __IsoAgLib {

  ConnectedPd_c::ConnectedPd_c( PdConnection_c& connection, PdBase_c& pdBase )
    : m_connection( connection )
    , m_pdBase( pdBase )
  {
    m_pdBase.addConnected( *this );
  }


  ConnectedPd_c::~ConnectedPd_c()
  {
    m_pdBase.removeConnected( *this );
  }


  void
  ConnectedPd_c::sendMsg( IsoAgLib::ProcData::CommandType_t cmd, int32_t value )
  {
    connection().sendProcMsg(
      cmd,
      pdBase().DDI(),
      pdBase().element(),
      value );
  }

}
