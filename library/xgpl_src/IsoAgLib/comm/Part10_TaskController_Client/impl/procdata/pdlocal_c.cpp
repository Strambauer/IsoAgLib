/*
  pdlocal_c.cpp: Class for providing Process Data (without DDOP)

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
#include "pdlocal_c.h"
#include "measureprog_c.h"

#if defined(_MSC_VER)
#pragma warning( disable : 4355 )
#endif


namespace __IsoAgLib {

  PdLocal_c::PdLocal_c()
    : PdBase_c()
    , m_setpoint()
    , m_measurement()
    , m_triggerMethod( 0xDA ) // invalid, needs to be init()
  {
  }

  PdLocal_c::PdLocal_c( uint16_t _ddi, uint16_t _element, uint8_t _triggerMethod, bool _settable, bool _controlSource, SetpointHandler_c *_handler )
    : PdBase_c( _ddi, _element )
    , m_setpoint( _handler, _settable )
    , m_measurement()
    , m_triggerMethod( _triggerMethod )
    , m_controlSource( _controlSource )
  {
  }

  void
  PdLocal_c::init( uint16_t _ddi, uint16_t _element, uint8_t triggerMethod, bool _settable, bool _controlSource, SetpointHandler_c *_handler )
  {
    PdBase_c::init( _ddi, _element );
    m_setpoint.init( _handler, _settable );
    m_triggerMethod = triggerMethod;
    m_controlSource = _controlSource;
  }

  ConnectedPd_c &
  PdLocal_c::createConnectedPd( PdConnection_c &connection )
  {
    return *new MeasureProg_c( connection, *this );
  }

}
