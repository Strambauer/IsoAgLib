/***************************************************************************
                          vtobjectauxiliaryinput_c.cpp
                             -------------------
    begin                : Mon Jun 30 14:41:54 2003
    copyright            : (C) 2003 by Martin Wodok/ Bradford Cox
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
#include "vtobjectauxiliaryinput_c.h"

#include "isoterminal_c.h"
#include "../ivtobjectfontattributes_c.h"
#include "../ivtobjectbutton_c.h"

// Begin Namespace __IsoAgLib
namespace __IsoAgLib {

// Operation : stream
//! @param destMemory:
//! @param maxBytes: don't stream out more than that or you'll overrun the internal upload-buffer
//! @param sourceOffset:
int16_t
vtObjectAuxiliaryInput_c::stream(uint8_t* destMemory, uint16_t maxBytes, objRange_t sourceOffset)
{
#define MACRO_vtObjectTypeA vtObjectAuxiliaryInput_a
#define MACRO_vtObjectTypeS iVtObjectAuxiliaryInput_s
  MACRO_streamLocalVars;
  MACRO_scaleLocalVars;
  if (sourceOffset == 0) { // dump out constant sized stuff
    destMemory [0] = vtObject_a->ID & 0xFF;
    destMemory [1] = vtObject_a->ID >> 8;
    destMemory [2] = 30; // Object Type = Auxiliary Input
    destMemory [3] = __IsoAgLib::getIsoTerminalInstance4Comm().getClientByID (s_properties.clientId).getUserClippedColor (vtObjectAuxiliaryInput_a->backgroundColour, this, IsoAgLib::BackgroundColour);
    destMemory [4] = vtObjectAuxiliaryInput_a->functionType;
    destMemory [5] = vtObjectAuxiliaryInput_a->inputId;
    destMemory [6] = vtObjectAuxiliaryInput_a->numberOfObjectsToFollow;
    sourceOffset += 7;
    curBytes += 7;
  }

  MACRO_streamObjectXYcenteredInSoftKey(7);

  return curBytes;
}


// Operation : vtObjectAuxiliaryInput_c
vtObjectAuxiliaryInput_c::vtObjectAuxiliaryInput_c() {}

// Operation : size
uint32_t
vtObjectAuxiliaryInput_c::fitTerminal() const
{
  MACRO_localVars;
  return 7+vtObjectAuxiliaryInput_a->numberOfObjectsToFollow*6;
}

bool
vtObjectAuxiliaryInput_c::moveChildLocation(IsoAgLib::iVtObject_c* apc_childObject, int8_t dx, int8_t dy, bool b_updateObject, bool b_enableReplaceOfCmd)
{
  MACRO_localVars;
  return genericChangeChildLocation (apc_childObject, dx, dy, b_updateObject, vtObjectAuxiliaryInput_a->numberOfObjectsToFollow, const_cast<IsoAgLib::repeat_iVtObject_x_y_iVtObjectFontAttributes_row_col_s *> (vtObjectAuxiliaryInput_a->objectsToFollow), MACRO_getStructOffset(get_vtObjectAuxiliaryInput_a(), objectsToFollow), sizeof(iVtObjectAuxiliaryInput_s), b_enableReplaceOfCmd);
}

bool
vtObjectAuxiliaryInput_c::setChildPosition(IsoAgLib::iVtObject_c* apc_childObject, int16_t x, int16_t y, bool b_updateObject, bool b_enableReplaceOfCmd)
{
  MACRO_localVars;
  return genericChangeChildPosition (apc_childObject, x, y, b_updateObject, vtObjectAuxiliaryInput_a->numberOfObjectsToFollow, const_cast<IsoAgLib::repeat_iVtObject_x_y_iVtObjectFontAttributes_row_col_s *> (vtObjectAuxiliaryInput_a->objectsToFollow), MACRO_getStructOffset(get_vtObjectAuxiliaryInput_a(), objectsToFollow), sizeof(iVtObjectAuxiliaryInput_s), b_enableReplaceOfCmd);
}

// Operation : setOriginSKM
//! @param b_SKM:
void
vtObjectAuxiliaryInput_c::setOriginSKM(bool /* b_SKM */)
{
  MACRO_localVars;
  for (int i=0; i<vtObjectAuxiliaryInput_a->numberOfObjectsToFollow; i++) {
    vtObjectAuxiliaryInput_a->objectsToFollow[i].vtObject->setOriginSKM (true);
  }
}

} // end of namespace __IsoAgLib