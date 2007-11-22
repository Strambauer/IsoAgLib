/***************************************************************************
                              isofiltermanager_c.h
                             -------------------
    begin                : Tue Oct 10 2006
    copyright            : (C) 2006 by Dipl.-Inf. Martin Wodok
    email                : m.wodok@osb-ag:de
    type                 : Header
    $LastChangedDate:  $
    $LastChangedRevision:  $
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
#ifndef ISO_FILTER_MANAGER_C_H
#define ISO_FILTER_MANAGER_C_H

/* *************************************** */
/* ********** include headers ************ */
/* *************************************** */
#include <IsoAgLib/typedef.h>
#include <IsoAgLib/util/config.h>

#include <IsoAgLib/util/impl/singleton.h>
#include <IsoAgLib/comm/Part5_NetworkManagement//impl/isomonitor_c.h>

#include "isofilterbox_c.h"

#include <cstdlib>	// Include before vector or else CNAMESPACE stuff is screwed up for Tasking
#include <vector>

// Begin Namespace __IsoAgLib
namespace __IsoAgLib {

// forward declaration

class IsoFilterManager_c;
typedef SINGLETON_DERIVED(IsoFilterManager_c, Scheduler_Task_c) SingletonIsoFilterManager_c;
/** this object manages ISO-Filters - those may contain references
    to ISOName's and are initelligent self-adapting can-filters
    @short Manager for handling of inserting/adapting FilterBox_c-instances
    @see __IsoAgLib::SaClaimHandler_c
    @author Dipl.-Inf. Martin Wodok */
class IsoFilterManager_c : public SingletonIsoFilterManager_c
{
public:
  typedef STL_NAMESPACE::vector<IsoFilterBox_c> IsoFilterBox_vec;
  typedef STL_NAMESPACE::vector<IsoFilterBox_c>::iterator IsoFilterBox_it;

  /** initialisation for IsoFilterManager_c */
  void init();

  /** default destructor which has nothing to do */
  ~IsoFilterManager_c ();

  bool existIsoFilter (const IsoFilter_s& rrefcs_isoFilter);

  void insertIsoFilter (const IsoFilter_s& rrefcs_isoFilter, bool ab_immReconfigure=true);

  bool removeIsoFilter (const IsoFilter_s& rrefcs_isoFilter);

  /** constructor for IsoFilterManager_c */
  IsoFilterManager_c (void);

  virtual bool timeEvent( void );
  virtual void close( void );
  virtual const char* getTaskName() const;


private: // Private methods

  /** initialize directly after the singleton instance is created.
      this is called from singleton.h and should NOT be called from the user again.
      users please use init(...) instead. */
  void singletonInit ();


  /** this function is called by IsoMonitor_c when a new CLAIMED IsoItem_c is registered.
   * @param rc_isoName const reference to the item which IsoItem_c state is changed
   * @param apc_newItem pointer to the currently corresponding IsoItem_c
   */
  void reactOnMonitorListAdd (const IsoName_c& rc_isoName, const IsoItem_c* apc_newItem);
   /** this function is called by IsoMonitor_c when a device looses its IsoItem_c.
   * @param rc_isoName const reference to the item which IsoItem_c state is changed
   * @param aui8_oldSa previously used SA which is NOW LOST -> clients which were connected to this item can react explicitly
    */
  void reactOnMonitorListRemove (const IsoName_c& rc_isoName, uint8_t aui8_oldSa);

private: // Private attributes
  /// holds all

  IsoFilterBox_vec mvec_isoFilterBox;

  friend class SINGLETON_DERIVED (IsoFilterManager_c,Scheduler_Task_c);

  bool mb_alreadyInitialized;
};

#if defined( PRT_INSTANCE_CNT ) && ( PRT_INSTANCE_CNT > 1 )
  /** C-style function, to get access to the unique IsoFilterManager_c singleton instance
      if more than one CAN BUS is used for IsoAgLib, an index must be given to select the wanted BUS */
  IsoFilterManager_c& getIsoFilterManagerInstance (uint8_t aui8_instance = 0);
#else
  /** C-style function, to get access to the unique IsoFilterManager_c singleton instance */
  IsoFilterManager_c& getIsoFilterManagerInstance (void);
#endif

}
#endif