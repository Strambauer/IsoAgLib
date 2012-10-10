/*
  canio_c.h: master object for CAN communication; owns array of
    FilterBox_c and MsgObj_c instances

  (C) Copyright 2009 - 2012 by OSB AG and developing partners

  See the repository-log for details on the authors and file-history.
  (Repository information can be found at <http://isoaglib.com/download>)

  Use, modification and distribution are subject to the GNU General
  Public License with exceptions for ISOAgLib. (See accompanying
  file LICENSE.txt or copy at <http://isoaglib.com/download/license>)
*/
#ifndef CAN_IO_H
#define CAN_IO_H

#include <IsoAgLib/isoaglib_config.h>
#include <IsoAgLib/util/iliberr_c.h>
#include <IsoAgLib/util/impl/util_funcs.h>
#include <IsoAgLib/util/impl/singleton.h>
#include <IsoAgLib/hal/hal_can.h>
#include <IsoAgLib/hal/hal_system.h>
#include "ident_c.h"
#include "filterbox_c.h"

#include <list>

namespace __IsoAgLib {

  class CanIo_c : public Subsystem_c {
      MACRO_MULTITON_CONTRIBUTION();
    protected:
      typedef STL_NAMESPACE::list<FilterBox_c> ArrFilterBox;

    public:

      bool init( uint8_t bus, uint16_t bitrate );

      /** every subsystem of IsoAgLib has explicit function for controlled shutdown */
      void close( void );

      ~CanIo_c() {}

      /** provide BUS number */
      uint8_t getBusNumber( void ) const {
        return mui8_busNumber;
      }

#ifdef USE_CAN_MEASURE_BUSLOAD
      /** deliver actual BUS load in baud */
      uint32_t getProcessedThroughput() const;
#endif

      /** wait until specified timeout or until next CAN message receive
       *  @return true -> there are CAN messages waiting for process. else: return due to timeout
       */
      static bool waitUntilCanReceiveOrTimeout( uint16_t aui16_timeoutInterval ) {
        return HAL::canRxWait( aui16_timeoutInterval );
      }

      /** deliver the numbers which can be placed at the moment in the send buffer
        @return number of msgs which fit into send buffer
      */
      int sendCanFreecnt() {
        return HAL::canTxQueueFree( mui8_busNumber );
      }

      /** test if a FilterBox_c definition already exist
        (version expecial for extended ident, chosen at compile time)
        @param ar_customer reference to the processing class ( the same filter setting can be registered by different consuming classes )
        @param arc_filterpair filter mask type set
        @param apc_iter optional pointer Iterator to result FilterBox
        @return true -> same FilterBox_c already exist
      */
      bool existFilter( const __IsoAgLib::CanCustomer_c& ar_customer,
                        const IsoAgLib::iMaskFilterType_c& arc_filterpair,
                        ArrFilterBox::iterator* apc_iter = NULL );

      /** create a Filter Box with specified aui32_mask/aui32_filter
        on ui8_busNr of object; reconfig HW CAN MsgObj_c only if
        ab_reconfigImmediate == true -> useful for
        avoiding unneeded reconfiguration during
        sequence of FilterBox_c insertions;
        by ar_customer CanIo_c (FilterBox_c) can start direct processing
        of received data in dedicated customer object (no search);
        uses BIOS functions

        possible errors:
            * Err_c::badAlloc on not enough memory for new FilterBox
            instance or for new configured MsgObj_c's
        @see __IsoAgLib::CANCustomer
        @param ar_customer reference to __IsoAgLib::CanCustomer_c  which needs
             filtered messages (-> on received msg call ar_customer.processMsg())
        @param arc_filterpair mask filter combination
        @return != NULL -> if inserting and wanted reconfiguration are performed without errors,
          a reference to the created FilterBox is returned
       @exception badAlloc
      */

      FilterBox_c* insertFilter( __IsoAgLib::CanCustomer_c& ar_customer,
                                 const IsoAgLib::iMaskFilterType_c& arc_filterpair,
                                 int ai_dlcForce );

      /** helper function to search all FilterBoxes for matching
        instance which maps to received CAN messages
        ( needed if the coordinated FilterBoxes don't match,
          especially important to process messages from global
          CAN MsgObj which doesn't have explicit connected FilterBox
          instances )
        @param aui32_ident Ident of received CAN message
        @return is another filterbox found?
      */
      bool canMsg2FilterBox( uint32_t aui32_ident, Ident_c::identType_t at_type, ArrFilterBox::iterator& ar_arrFilterBoxIter, bool ab_start );

      /** delete a FilerBox definition
        @param ar_customer reference to the processing class ( the same filter setting can be registered by different consuming classes )
        @param arc_filterpair filter mask combination
        @return true -> FilterBox_c found and deleted
      */
      bool deleteFilter( const __IsoAgLib::CanCustomer_c& ar_customer, const IsoAgLib::iMaskFilterType_c& arc_filterpair );

      bool deleteAllFiltersForCustomer ( const __IsoAgLib::CanCustomer_c& ar_customer );


      /** initiate processing of all received msg */
      void processMsg( bool b_break );

      /** function for sending data out of CanPkg_c */
      CanIo_c& operator<<( CanPkg_c& acrc_src );

      /** return time stamp of the last can package that has been received and processed successfully */
      int32_t getLastProcessedCanPkgTime() const {
        return mi32_lastProcessedCanPkgTime;
      }

    protected:
      /** evaluate common bits of all defined filterBox
         instances and set it in mask -> build up global mask
       */
      void getCommonFilterMask();

    private:
      CanIo_c( void );

      /** search for a FilterBox with given mask and filter
          @param arc_filterpair filter mask combination
          @return located FilterBox or NULL if not exist
        */
      FilterBox_c* getFilterBox( const IsoAgLib::iMaskFilterType_c& arc_maskFilter ) const;

      /** Vector of configured filter boxes */
      ArrFilterBox m_arrFilterBox;
      /** temp filer box to avoid new/delete for each insert of a filterBox */
      FilterBox_c mc_tempFilterBox;

      /** maximum send delay - value of < 0 indicates that no send-delay check is requested*/
      int32_t mi32_maxSendDelay;

      /**  timestamp of last received and and processed CAN package  */
      int32_t mi32_lastProcessedCanPkgTime;

      /** configured bitrate */
      uint16_t mui16_bitrate;

      /** global mask with standard 11bit type */
      Ident_c mc_maskStd;
      /** global mask with extended 29bit type */
      Ident_c mc_maskExt;

      uint8_t mui8_busNumber;

      /** flag to avoid loop of CAN message processing, when timeEvent() is called during previous
       *  timeEvent triggered CAN processing -> when this flag is true, no further processing is performed
       */
      bool mb_runningCanProcess;

      friend CanIo_c &getCanInstance( uint8_t aui8_instance );
  };


  /** C-style function, to get access to the unique CanIo_c singleton instance
    * if more than one CAN BUS is used for IsoAgLib, an index must be given to select the wanted BUS
    */
  CanIo_c &getCanInstance( uint8_t aui8_instance = 0 );

}

#endif
