/*
  connectedpdremote_c.cpp: object for managing connected remote measure

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
#include "connectedpdremote_c.h"
#include <IsoAgLib/comm/Part10_TaskController_Client/impl/pdconnection_c.h>


namespace __IsoAgLib {


  ConnectedPdRemote_c::ConnectedPdRemote_c( PdConnection_c& connection, PdRemote_c& pdRemote )
    : ConnectedPd_c( connection, pdRemote )
  {
  }


  ConnectedPdRemote_c::~ConnectedPdRemote_c()
  {
  }


  void ConnectedPdRemote_c::handleRequest()
  {
    // we're just listening to a remote (broadcasted) value,
    // so we don't accept value requests
  }


  void ConnectedPdRemote_c::handleIncoming( int32_t value, bool wasBroadcast )
  {
    ( void )wasBroadcast;
    pdRemote().getRemoteValue().processMsg( pdRemote(), value );
  }


  bool ConnectedPdRemote_c::startMeasurement( IsoAgLib::ProcData::MeasurementCommand_t, int32_t )
  {
    // we're just listening to a remote (broadcasted) value,
    // so we don't accept getting measurement commands
    return false; // NACK 'em in case...
  }


}
