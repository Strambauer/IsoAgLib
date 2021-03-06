/*
  idevicepool_c.cpp - Implementation of a device description object pool using modifiable
    C++ objects. The pool is represented of a collection of objects
    derived from a common base class. The device pool synchronization
    with the Task Controller is accomplished by uploading a partial pool
    when objects change.

  (C) Copyright 2013 - 2019 by OSB AG

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

#include <IsoAgLib/comm/Part10_TaskController_Client/idevicepool_c.h>
#include <IsoAgLib/comm/Part10_TaskController_Client/iprocdata_c.h>

namespace IsoAgLib {

  void iDevicePool_c::add( iProcData_c& pd ) {
    __IsoAgLib::DevicePool_c::add( pd );
  }

}
