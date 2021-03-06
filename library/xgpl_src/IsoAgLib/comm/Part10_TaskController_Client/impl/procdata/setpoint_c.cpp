/*
  setpoint_c.cpp - class for handling the Setpoint of a local PD

  (C) Copyright 2009 - 2019 by OSB AG

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
#include "setpoint_c.h"
#include <IsoAgLib/comm/Part10_TaskController_Client/impl/pdconnection_c.h>
#include <IsoAgLib/comm/Part10_TaskController_Client/impl/procdata/pdbase_c.h>


namespace __IsoAgLib {


  Setpoint_c::Setpoint_c()
    : m_value( 0 )
    , m_handler( NULL )
    , m_settable( false )
  {
  }


  Setpoint_c::Setpoint_c( SetpointHandler_c* handler, bool settable )
    : m_value( 0 )
    , m_handler( handler )
    , m_settable( settable )
  {
  }


  void
  Setpoint_c::processMsg( PdLocal_c &pd, int32_t value )
  {
    const bool b_change = ( m_value != value );
    m_value = value;

    if( m_handler )
      m_handler->_processSetpointSet( pd, value, b_change );
  }


  void
  Setpoint_c::init( SetpointHandler_c* handler, bool settable )
  {
    m_handler = handler;
    m_settable = settable;
  }

}
