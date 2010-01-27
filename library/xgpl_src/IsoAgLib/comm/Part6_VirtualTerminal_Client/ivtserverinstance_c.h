/*
  vtserverinstance_c.h - interface class for wrapping one vtserver instance

  (C) Copyright 2009 - 2010 by OSB AG and developing partners

  See the repository-log for details on the authors and file-history.
  (Repository information can be found at <http://isoaglib.com/download>)

  Use, modification and distribution are subject to the GNU General
  Public License with exceptions for ISOAgLib. (See accompanying
  file LICENSE.txt or copy at <http://isoaglib.com/download/license>)
*/
#ifndef IVT_SERVER_INSTANCE_H
#define IVT_SERVER_INSTANCE_H

// own
#include "impl/vtserverinstance_c.h"

// IsoAgLib
#include <IsoAgLib/comm/Part5_NetworkManagement/iisoitem_c.h>
#include <IsoAgLib/comm/Part5_NetworkManagement/iisoname_c.h>


namespace IsoAgLib
{

/** interface class for wrapped vtserver-instance
  */
class iVtServerInstance_c : private __IsoAgLib::VtServerInstance_c
{
public:

  bool isVtActive() { return VtServerInstance_c::isVtActive(); }

  const iIsoName_c& getIsoName() { return VtServerInstance_c::getIsoName().toConstIisoName_c(); }
  uint32_t          getVtHardwareDimension() { return VtServerInstance_c::getVtHardwareDimension(); }
  uint16_t          getVtFontSizes() { return VtServerInstance_c::getVtFontSizes(); }
  uint8_t           getVtIsoVersion() { return VtServerInstance_c::getVtIsoVersion(); }
  const vtState_s*  getVtState() { return VtServerInstance_c::getVtState(); }
  const iIsoItem_c* getIsoItem() { return (VtServerInstance_c::getIsoItem() != NULL) ? &(VtServerInstance_c::getIsoItem()->toConstIisoItem_c()) : NULL; }

private:
  /** PRIVATE constructor to forbid instantiation of this interface class.
    * it can only be static_cast'ed to this class, not constructed!
    */
  iVtServerInstance_c ();

  friend class iIsoTerminal_c;
  friend class __IsoAgLib::VtServerInstance_c;
};

} // namespace IsoAgLib
#endif