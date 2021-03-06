/*
  tractorgroundbasedc.cpp: 

  (C) Copyright 2016 - 2019 by OSB AG

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

#include "tractorgroundbased_c.h"
#include <IsoAgLib/comm/impl/isobus_c.h>


namespace __IsoAgLib {

  TractorGroundBased_c &getTractorGroundBasedInstance( unsigned instance )
  { // if > 1 singleton instance is used, no static reference can be used
    MACRO_MULTITON_GET_INSTANCE_BODY(TractorGroundBased_c, PRT_INSTANCE_CNT, instance);
  }


  void
  TractorGroundBased_c::resetValues()
  {
    mui16_speed = NO_VAL_16;
    mui32_distance = NO_VAL_32;

    mt_direction = IsoAgLib::IsoNotAvailableDirection;
  };


  void
  TractorGroundBased_c::setValues( const CanPkgExt_c& pkg )
  {
    mui16_speed    = pkg.getUint16Data( 0 );
    mui32_distance = pkg.getUint32Data( 2 );

    mt_direction = IsoAgLib::IsoDirectionFlag_t( pkg.getUint8Data(7) & 0x3 );
  }


} // __IsoAglib
