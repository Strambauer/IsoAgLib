/***************************************************************************
                          isoterminalstringmss_c.h
                             -------------------
    begin                : Don Sep 4 2003
    copyright            : (C) 2003 by Martin Wodok
    email                : m.wodok@osb-ag:de
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 * This file is part of the "IsoAgLib", an object oriented program library *
 * to serve as a software layer between application specific program and   *
 * communication protocol details. By providing simple function calls for  *
 * jobs like starting a measuring program for a process data value on a    *
 * remote ECU, the main program has not to deal with single CAN telegram   *
 * formatting. This way communication problems between ECU's which use     *
 * this library should be prevented.                                       *
 * Everybody and every company is invited to use this library to make a    *
 * working plug and play standard out of the printed protocol standard.    *
 *                                                                         *
 * Copyright (C) 2000 - 2004 Dipl.-Inform. Achim Spangler                  *
 *                                                                         *
 * The IsoAgLib is free software; you can redistribute it and/or modify it *
 * under the terms of the GNU General Public License as published          *
 * by the Free Software Foundation; either version 2 of the License, or    *
 * (at your option) any later version.                                     *
 *                                                                         *
 * This library is distributed in the hope that it will be useful, but     *
 * WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU       *
 * General Public License for more details.                                *
 *                                                                         *
 * You should have received a copy of the GNU General Public License       *
 * along with IsoAgLib; if not, write to the Free Software Foundation,     *
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA           *
 *                                                                         *
 * As a special exception, if other files instantiate templates or use     *
 * macros or inline functions from this file, or you compile this file and *
 * link it with other works to produce a work based on this file, this file*
 * does not by itself cause the resulting work to be covered by the GNU    *
 * General Public License. However the source code for this file must still*
 * be made available in accordance with section (3) of the                 *
 * GNU General Public License.                                             *
 *                                                                         *
 * This exception does not invalidate any other reasons why a work based on*
 * this file might be covered by the GNU General Public License.           *
 *                                                                         *
 * Alternative licenses for IsoAgLib may be arranged by contacting         *
 * the main author Achim Spangler by a.spangler@osb-ag:de                  *
 ***************************************************************************/

 /**************************************************************************
 *                                                                         *
 *     ###    !!!    ---    ===    IMPORTANT    ===    ---    !!!    ###   *
 * Each software module, which accesses directly elements of this file,    *
 * is considered to be an extension of IsoAgLib and is thus covered by the *
 * GPL license. Applications must use only the interface definition out-   *
 * side :impl: subdirectories. Never access direct elements of __IsoAgLib  *
 * and __HAL namespaces from applications which shouldnt be affected by    *
 * the license. Only access their interface counterparts in the IsoAgLib   *
 * and HAL namespaces. Contact a.spangler@osb-ag:de in case your applicat- *
 * ion really needs access to a part of an internal namespace, so that the *
 * interface might be extended if your request is accepted.                *
 *                                                                         *
 * Definition of direct access:                                            *
 * - Instantiation of a variable with a datatype from internal namespace   *
 * - Call of a (member-) function                                          *
 * Allowed is:                                                             *
 * - Instatiation of a variable with a datatype from interface namespace,  *
 *   even if this is derived from a base class inside an internal namespace*
 * - Call of member functions which are defined in the interface class     *
 *   definition ( header )                                                 *
 *                                                                         *
 * Pairing of internal and interface classes:                              *
 * - Internal implementation in an :impl: subdirectory                     *
 * - Interface in the parent directory of the corresponding internal class *
 * - Interface class name IsoAgLib::iFoo_c maps to the internal class      *
 *   __IsoAgLib::Foo_c                                                     *
 *                                                                         *
 * AS A RULE: Use only classes with names beginning with small letter :i:  *
 ***************************************************************************/
#ifndef VTOBJECTSTRING_C_H
#define VTOBJECTSTRING_C_H

#include <IsoAgLib/comm/Part3_DataLink/imultisendstreamer_c.h>
#include "vtobject_c.h"

namespace __IsoAgLib {
class MultiSendPkg_c;

/** helper class to avoid multiple inheritance by vtObjectString_c */
class vtObjectStringStreamer_c : public IsoAgLib::iMultiSendStreamer_c
{
 public:
  //  Operation: setDataNextStreamPart
  //! @param mspData:
  //! @param bytes:
  void setDataNextStreamPart(MultiSendPkg_c* mspData,
                             uint8_t bytes);

  //  Operation: resetDataNextStreamPart
  void resetDataNextStreamPart();

  //  Operation: saveDataNextStreamPart
  void saveDataNextStreamPart();

  //  Operation: restoreDataNextStreamPart
  void restoreDataNextStreamPart();

  //  Operation: getStreamSize
  uint32_t getStreamSize();

  uint8_t getFirstByte () { return 179; /* Command: "Command" --- Parameter: "Change String Value"; */ }

  const char* getStringToStream() { return mpc_stringToStream; }

  void set5ByteCommandHeader(uint8_t* destinBuffer);

  void setStringToStream( const char* apc_stringToStream ) { mpc_stringToStream = apc_stringToStream;}
  void setStrLenToSend( uint16_t aui16_strLenToSend ) { mui16_strLenToSend = aui16_strLenToSend;}

  //  Operation: getID
  uint16_t getID() { return mui16_vtObjectAId; }
  //  Operation: setID
  void setID( uint16_t aui16_id ) { mui16_vtObjectAId = aui16_id; }

private:
  // ID from the connected __IsoAgLib::vtObject_c
  uint16_t mui16_vtObjectAId;
  // those both will be set before multisending is getting started.
  const char* mpc_stringToStream;
  uint16_t mui16_strLenToSend;

  //  Attribute: mui32_streamPosition
  uint32_t mui32_streamPosition;

  //  Attribute: marr_uploadBuffer [7+1]
  uint8_t marr_uploadBuffer [7+1]; /* "+1" for safety only */

  //  Attribute: mui32_streamPositionStored
  uint32_t mui32_streamPositionStored;
};

class vtObjectString_c : public vtObject_c
{
 public:
  vtObjectString_c();
  ~vtObjectString_c();
  vtObjectStringStreamer_c* getStreamer( void ) { return &mc_streamer;};
 protected:

  // those both will be set before multisending is getting started.
  void setStringToStream( const char* apc_stringToStream );
  void setStrLenToSend( uint16_t aui16_strLenToSend );

 private:
  // streaming helper class which is called by the sending class
  vtObjectStringStreamer_c mc_streamer;
};

} // end namespace __IsoAgLib

#endif