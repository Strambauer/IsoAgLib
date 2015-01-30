/*
  pdlocal_c.cpp: Class for providing Process Data (without DDOP)

  (C) Copyright 2014 - 2014 by OSB AG and developing partners

  See the repository-log for details on the authors and file-history.
  (Repository information can be found at <http://isoaglib.com/download>)

  Use, modification and distribution are subject to the GNU General
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

  PdLocal_c::PdLocal_c( uint16_t ddi, uint16_t element, uint8_t triggerMethod, bool settable, SetpointHandler_c *handler )
    : PdBase_c( ddi, element )
    , m_setpoint( handler, settable )
    , m_measurement()
    , m_triggerMethod( triggerMethod )
  {
  }

  void
  PdLocal_c::init( uint16_t ddi, uint16_t element, uint8_t triggerMethod, bool settable, SetpointHandler_c *handler )
  {
    PdBase_c::init( ddi, element );
    m_setpoint.init( handler, settable );
    m_triggerMethod = triggerMethod;
  }

  ConnectedPd_c &
  PdLocal_c::createConnectedPd( PdConnection_c &connection )
  {
    return *new MeasureProg_c( connection, *this );
  }

}