/*
  procdata_c.h: Class for handling Process Data

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
#ifndef PROCDATA_C_H
#define PROCDATA_C_H

#include <IsoAgLib/comm/Part10_TaskController_Client/impl/procdata/pdlocal_c.h>


namespace __IsoAgLib {

  class DeviceObjectDpd_c;
  class DeviceObjectDet_c;

  class ProcData_c : public PdLocal_c
  {
  public:
    ProcData_c();

    void init( const DeviceObjectDpd_c& dpd, const DeviceObjectDet_c& det, SetpointHandler_c* setpointhandler = NULL );
    void close();

#ifndef NDEBUG
    inline const DeviceObjectDpd_c* getDpd() const { return m_dpd; }
    inline const DeviceObjectDet_c* getDet() const { return m_det; }

  private:
    const DeviceObjectDpd_c* m_dpd;
    const DeviceObjectDet_c* m_det;
#endif
  };

}

#endif
