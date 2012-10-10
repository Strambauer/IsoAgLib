/*
  filterbox_c.cpp: FilterBox_c permits free definition of mask/filter
    for receiving CAN telegrams by a CANCustomer (or derived) object

  (C) Copyright 2009 - 2012 by OSB AG and developing partners

  See the repository-log for details on the authors and file-history.
  (Repository information can be found at <http://isoaglib.com/download>)

  Use, modification and distribution are subject to the GNU General
  Public License with exceptions for ISOAgLib. (See accompanying
  file LICENSE.txt or copy at <http://isoaglib.com/download/license>)
*/

#include "filterbox_c.h"
#include "canio_c.h"
#include <IsoAgLib/driver/can/impl/cancustomer_c.h>
#include <IsoAgLib/util/iassert.h>

namespace __IsoAgLib {

FilterBox_c* FilterBox_c::mspc_currentlyProcessedFilterBox = NULL;
int FilterBox_c::msi_processMsgLoopIndex = -1; // not used if "mspc_currentlyProcessedFilterBox==NULL" though.
int FilterBox_c::msi_processMsgLoopSize = -1; // not used if "mspc_currentlyProcessedFilterBox==NULL" though.

FilterBox_c::FilterBox_c()
  : mc_maskFilterPair()
  , mvec_customer()
{}

/**
  copy constructor which uses data of another FilterBox_c instance

  @param acrc_src reference to the source FilterBox_c instance for copying
   @exception badAlloc
*/
FilterBox_c::FilterBox_c(const FilterBox_c& acrc_src)
  : mc_maskFilterPair(acrc_src.mc_maskFilterPair)
  , mvec_customer(acrc_src.mvec_customer)
{}

/**
  copy values of acrc_src FilterBox_c object to this instance

  possible errors:
      * badAlloc on not enough memory for copying buffed CAN msg from source

  @param acrc_src FilterBox_c instance with data to assign to this instance
  @return reference to this instance for chains like "box_1 = box_2 = ... = box_n;"
*/

FilterBox_c& FilterBox_c::operator=(const FilterBox_c& acrc_src){
  if ( this != &acrc_src)
  {
    mc_maskFilterPair = acrc_src.mc_maskFilterPair;
    mvec_customer = acrc_src.mvec_customer;
  }
  return *this;
}


/** clear the data of this instance */
void FilterBox_c::clearData()
{
  mvec_customer.clear();
  mc_maskFilterPair.setEmpty();
}

/* *************************************** */
/* ******* filter/mask managing ********** */
/* *************************************** */

/**
  set the mask (t_mask) and filter (t_filter) of this FilterBox
 @param acrc_mask mask for this Filer_Box (MASK_TYPE defined in isoaglib_config.h)
  @param arc_maskFilterPair mask filter combination
  @param apc_customer pointer to the CanCustomer_c instance, which creates this FilterBox_c instance
  @param ai8_dlcForce force the DLC to be exactly this long (0 to 8 bytes). use -1 for NO FORCING and accepting any length can-pkg
*/
void FilterBox_c::set (const IsoAgLib::iMaskFilterType_c& arc_maskFilterPair,
                       CanCustomer_c* apc_customer,
                       int8_t ai8_dlcForce)
{
  // actually "apc_customer" should've rather been a reference!
  isoaglib_assert (apc_customer);

  mc_maskFilterPair = arc_maskFilterPair;

  STL_NAMESPACE::vector<CustomerLen_s>::iterator pc_iter = mvec_customer.begin();
  for (; pc_iter != mvec_customer.end(); ++pc_iter)
  {
    if (apc_customer == pc_iter->pc_customer)
    { // overwrite the DLC of the one found!
      pc_iter->i8_dlcForce = ai8_dlcForce;
      break;
    }
  }
  if (pc_iter == mvec_customer.end())
  { // push back new
    mvec_customer.push_back (CustomerLen_s (apc_customer, ai8_dlcForce));
    /// Currently "msi_processMsgLoopIndex" is not being adapted,
    /// because if a Message triggers Customer A and B, and Customer A
    /// inserts a filter for that same message for Customer C,
    /// we do NOT want Customer C to be called immediately.
  }
};

bool FilterBox_c::equalCustomer( const __IsoAgLib::CanCustomer_c& ar_customer ) const

{
  STL_NAMESPACE::vector<CustomerLen_s>::const_iterator pc_iter;
  for(pc_iter = mvec_customer.begin(); pc_iter != mvec_customer.end(); ++pc_iter)
    if( &ar_customer == pc_iter->pc_customer)
      return true;

  return false;
}

/** delete CanCustomer_c  instance from array or set FilterBox_c to idle
    if CanCustomer_c  is the only customer for this FilterBox_c instance
    @param  ar_customer  CANCustomer to delete
    @return                true -> no more cancustomers exist, whole filterbox can be deleted
  */
bool
FilterBox_c::deleteFilter( const __IsoAgLib::CanCustomer_c& ar_customer)
{
  int deleteIndex = 0;
  for (STL_NAMESPACE::vector<CustomerLen_s>::iterator pc_iter = mvec_customer.begin();
       pc_iter != mvec_customer.end();)
  {
    if (&ar_customer == pc_iter->pc_customer)
    { // the to-be-deleted customer is found and now pointed by pc_iter
      mvec_customer.erase(pc_iter);
      // in case we're currently in the processing loop for this FilterBox
      if (mspc_currentlyProcessedFilterBox == this)
      { // we need to adapt the LoopSize and maybe LoopIndex
        if (deleteIndex <= msi_processMsgLoopIndex)
          --msi_processMsgLoopIndex;
        --msi_processMsgLoopSize;
      }
      break;
    }
    ++deleteIndex;
    ++pc_iter;
  }

  if ( mvec_customer.empty() )
  { // the last customer has been removed
    clearData();
    return true;
  }
  else
  { // there is at least one other can customer -> this FilterBox_c is still in use
    return false;
  }
}

/* ************************************************** */
/* ***** insert/get/process buffered CanPkg_c ******** */
/* ************************************************** */

/**
  control the processing of a received message
  (MsgObj_c::processMsg inserted data directly in CANCustomer
   -> FilterBox_c::processMsg() initiates conversion of CAN string
      to data flags and starts processing in CanCustomer_c )

  possible errors:
      * precondition no valid CanCustomer_c  (or derived) is registered
  @return true -> FilterBox_c was able to inform registered CANCustomer
*/
bool FilterBox_c::processMsg( CanPkg_c& pkg )
{
  bool b_result = false;

  //! We need to FIRST get the number of entries and then DON'T USE iterators,
  //! because the number may increase and the iterators may get invalid in case
  //! a Filter is inserted IN THIS filterbox (pushed back!)
  mspc_currentlyProcessedFilterBox = this;
  msi_processMsgLoopSize = mvec_customer.size();
  for ( msi_processMsgLoopIndex = 0;
        msi_processMsgLoopIndex < msi_processMsgLoopSize;
        ++msi_processMsgLoopIndex )
  {
    const int8_t ci8_vecCustomerDlcForce = mvec_customer[msi_processMsgLoopIndex].i8_dlcForce;
    CanCustomer_c* pc_customer = mvec_customer[msi_processMsgLoopIndex].pc_customer;
    isoaglib_assert( pc_customer );

    /// Check DataLengthCode (DLC) if required
    if (( ci8_vecCustomerDlcForce < 0 ) || ( ci8_vecCustomerDlcForce == pkg.getLen() ) )
    {
      // either no dlc-check requested or dlc matches the check!
      b_result |= pc_customer->processMsg( pkg );
    }
  }

  mspc_currentlyProcessedFilterBox = NULL; // indicate that we're not anymore in the loop!
  return b_result;
}

} // End namespace __IsoAgLib
