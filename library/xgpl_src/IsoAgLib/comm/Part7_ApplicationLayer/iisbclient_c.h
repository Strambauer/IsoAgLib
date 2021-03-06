/*
  iisbclient_c.h: central ISB client management
                  (Stop all implement operations)

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
#ifndef IISBCLIENT_C_H
#define IISBCLIENT_C_H

#include "impl/isbclient_c.h"


namespace IsoAgLib {

class iIdentItem_c;
class iIsbStateHandler_c;


class iIsbClient_c : private __IsoAgLib::IsbClient_c
{
public:
  void registerStateHandler( iIdentItem_c& identItem , IsoAgLib::iIsbStateHandler_c& handler )
  { __IsoAgLib::IsbClient_c::registerStateHandler( static_cast<__IsoAgLib::IdentItem_c&>( identItem ), handler ); }

  void deregisterStateHandler( iIdentItem_c& identItem, IsoAgLib::iIsbStateHandler_c& handler )
  { __IsoAgLib::IsbClient_c::deregisterStateHandler( static_cast<__IsoAgLib::IdentItem_c&>( identItem ), handler ); }

private:
#if ( PRT_INSTANCE_CNT == 1 )
  friend iIsbClient_c& getIisbClientInstance();
#endif
  friend iIsbClient_c& getIisbClientInstance( unsigned instance );
};

#if ( PRT_INSTANCE_CNT == 1 )
  inline iIsbClient_c& getIisbClientInstance()
  { return static_cast<iIsbClient_c&>( __IsoAgLib::getIsbClientInstance( 0 ) ); }
#endif
  inline iIsbClient_c& getIisbClientInstance( unsigned instance )
  { return static_cast<iIsbClient_c&>( __IsoAgLib::getIsbClientInstance( instance ) ); }

}

#endif
