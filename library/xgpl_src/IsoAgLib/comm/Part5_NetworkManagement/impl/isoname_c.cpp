/*
  isoname_c.cpp: handles the ISO 64bit NAME field

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

#include <IsoAgLib/isoaglib_config.h>
#include <cstring>
#include "isoname_c.h"
// necessary for convert operators
#include "../iisoname_c.h"

namespace __IsoAgLib {


const IsoName_c&
IsoName_c::IsoNameUnspecified()
{
  static IsoName_c sc_isoNameUnspecified;
  return sc_isoNameUnspecified;
}


void
IsoName_c::set(
  bool ab_selfConf,
  uint8_t aui8_indGroup,
  uint8_t aui8_devClass,
  uint8_t aui8_devClassInst,
  uint8_t ab_func,
  uint16_t aui16_manufCode,
  uint32_t aui32_serNo,
  uint8_t ab_funcInst,
  uint8_t ab_ecuInst)
{
  setSelfConf (ab_selfConf);
  setIndGroup (aui8_indGroup);
  setDevClass (aui8_devClass);
  setDevClassInst (aui8_devClassInst);
  setFunc (ab_func);
  setManufCode (aui16_manufCode);
  setSerNo (aui32_serNo);
  setFuncInst (ab_funcInst);
  setEcuInst (ab_ecuInst);

  setSpecified();
}


IsoName_c::ecuType_t
IsoName_c::getEcuType() const
{
  const uint8_t cui8_func = func();
  switch (cui8_func)
  {
    case 23: return ecuTypeNavigation;
    case 29: return ecuTypeVirtualTerminal;
    case 61: return ecuTypeFileServerOrPrinter;
    default:
      if (cui8_func >= 128)
      {
        if (indGroup() == 2) // Agricultural & Forestry
        {
          if (devClass() == 0) // Non-specific systems
          {
            switch (cui8_func)
            {
              case 130: return ecuTypeTaskControl;
              case 134: return ecuTypeTractorECU;
              case 139: return ecuTypeDataLogger;
              default:  break;
            }
          }
        }
      }
      break;
  }
  return ecuTypeANYOTHER;
}


bool
IsoName_c::isEqualRegardingNonInstFields (const IsoName_c& acrc_isoName) const
{
  // NOTE: We're not considering specified/unspecified here!
  return ( (devClass()  == acrc_isoName.devClass() )
        && (indGroup()  == acrc_isoName.indGroup() )
        && (func()      == acrc_isoName.func()     )
        && (serNo()     == acrc_isoName.serNo()    )
        && (selfConf()  == acrc_isoName.selfConf() )
        && (manufCode() == acrc_isoName.manufCode())
         );
}


bool
IsoName_c::isFunctionallyIdentical (const IsoName_c& other) const
{
  // NOTE: We're not considering specified/unspecified here!
  return ( (devClass()     == other.devClass()    )
        && (devClassInst() == other.devClassInst())
        && (indGroup()     == other.indGroup()    )
        && (func()         == other.func()        )
        && (funcInst()     == other.funcInst()    )
        && (ecuInst()      == other.ecuInst()     )
        && (manufCode()    == other.manufCode()   )
         );
}

void
IsoName_c::setOsbSpecialName(uint8_t a_SA)
{
  set(false,
      2 /*aui8_indGroup*/,
      0 /*aui8_devClass*/,
      0 /*aui8_devClassInst*/,
      a_SA /*ab_func*/,
      900 /*aui16_manufCode*/,
      0 /*aui32_serNo*/,
      0 /*ab_funcInst = 0*/,
      0 /*ab_ecuInst = 0*/);

  setReservedBit(1);
}

bool
IsoName_c::isOsbSpecialName() const
{
  return (selfConf()      == false
       && indGroup()      == 2
       && devClass()      == 0
       && devClassInst()  == 0
       && reservedBit()   == 1
       && manufCode()     == 900
       && serNo()         == 0
       && funcInst()      == 0
       && ecuInst()       == 0);
}

uint8_t
IsoName_c::getOsbSpecialSA() const
{
  return func();
}




IsoAgLib::iIsoName_c&
IsoName_c::toIisoName_c()
{
  return static_cast<IsoAgLib::iIsoName_c&>(*this);
  //return static_cast<IsoAgLib::iIsoName_c&>(*static_cast<IsoAgLib::iIsoName_c*>((void *)(this)));
  // doing it the ugly way, as some compiler do a recursive call of this operator at the "correct"
  // "return static_cast<IsoAgLib::iIsoName_c&>(*this);" statement - some do not.
  // with the above way we can get absolutely sure that there are no recursive uses of this operator
  // as those would overflow the stack and hence cause a system-crash
}


const
IsoAgLib::iIsoName_c& IsoName_c::toConstIisoName_c() const
{
  return static_cast<const IsoAgLib::iIsoName_c&>(*this);
//  return static_cast<const IsoAgLib::iIsoName_c&>(*static_cast<const IsoAgLib::iIsoName_c*>((void *)(this)));
  // doing it the ugly way, as some compiler do a recursive call of this operator at the "correct"
  // "return static_cast<const IsoAgLib::iIsoName_c&>(*this);" statement - some do not.
  // with the above way we can get absolutely sure that there are no recursive uses of this operator
  // as those would overflow the stack and hence cause a system-crash
}

} // namespace __IsoAgLib
