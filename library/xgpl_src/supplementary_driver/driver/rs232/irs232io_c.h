/*
  irs232io_c.h:
    header for RS232IO_c object for serial communication (Rs232)

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
#ifndef IRS232_IO_H
#define IRS232_IO_H

/* *************************************** */
/* ********** include headers ************ */
/* *************************************** */
#include "impl/rs232io_c.h"

namespace IsoAgLib {

/**
  object for serial communication via RS232 device;
  the interface is initialized during constructor call;
  and is closed during destructor -> automatic;
  stream input and output operators ease the data communication
  @short object for serial communication via RS232 device.
  @author Dipl.-Inform. Achim Spangler
*/
class iRS232IO_c : private __IsoAgLib::RS232IO_c {
public:

  /**
    enum type for setting data bit, stop bit and parity within one parameter:
    databitParityStopbit {7,8}_{N,O,E}_{1,2}
  */
  enum t_dataMode {_7_E_1 = 0x11, _7_E_2 = 0x12, _7_O_1 = 0x31, _7_O_2 = 0x32, _8_E_1 = 0x21, _8_E_2 = 0x22,
        _8_O_1 = 0x41, _8_O_2 = 0x42, _8_N_1 = 0x51, _8_N_2 = 0x52};

  // ++++++++++++++++++++++++++++++++++++
  // ++++ RS232 managing operations ++++
  // ++++++++++++++++++++++++++++++++++++

  /**
    init function which initialises the BIOS RS232
    @param aui32_baudrate baudrate {75, 600, 1200, 2400, 4800, 9600, 19200}
    @param ren_dataMode data mode setting of {7,8}_{N,O,E}_{1,2}
    @param ab_xonXoff use XON/XOFF sw handshake (true, false)
    @param aui16_sndBuf sending buffer size
    @param aui16_recBuf recieving buffer size

    possible errors:
        * Err_c::badAlloc not enough memory for allocating the buffers
        * Err_c::range one of the configuration vals is not in allowed ranges
  */
  bool init(
      uint32_t aui32_baudrate,
      t_dataMode ren_dataMode,
      bool ab_xonXoff,
      uint16_t aui16_sndBuf,
      uint16_t aui16_recBuf,
      uint8_t aui8_channel)
  {
    return RS232IO_c::init(
        aui32_baudrate,
        RS232IO_c::t_dataMode(ren_dataMode),
        ab_xonXoff,
        aui16_sndBuf,
        aui16_recBuf,
        aui8_channel);
  }

  /** close sub-system */
  void close() { RS232IO_c::close(); }

  /**
    set the baudrate to a new value
    @param aui32_baudrate baudrate {75, 600, 1200, 2400, 4800, 9600, 19200}

    possible errors:
        * Err_c::range the wanted baudrate is not allowed
    @return true -> setting successful
  */
  bool setBaudrate(uint32_t aui32_baudrate) {return RS232IO_c::setBaudrate(aui32_baudrate);};

  /**
    deliver the actual baudrate
    @return RS232 baudrate
  */
  uint32_t baudrate() const {return RS232IO_c::baudrate();};
  /**
    deliver the decoding type
    @return RS232 type
   */
  t_dataMode dataMode()const{return t_dataMode(RS232IO_c::dataMode());};

  /**
    set send buffer size
    @param aui16_bufferSize sending buffer size

    possible errors:
        * Err_c::badAlloc not enough memory for allocating the buffer
    @return true -> allocation of buffer successful
  */
  bool setSndBufferSize(uint16_t aui16_bufferSize)
    {return RS232IO_c::setSndBufferSize(aui16_bufferSize);};

  /**
    deliver the actual send buffer size
    @return send buffer size
  */
  uint16_t sndBufferSize()const{return RS232IO_c::sndBufferSize();};
  /**
    clear the send buffer without send of actual data in buffer
  */
  void clearSndBuffer()const{RS232IO_c::clearSndBuffer();};
  /**
    set receive buffer size
    @param aui16_bufferSize receiving buffer size

    possible errors:
        * Err_c::badAlloc not enough memory for allocating the buffer
    @return true -> allocating of buffer successful
  */
  bool setRecBufferSize(uint16_t aui16_bufferSize)
    {return RS232IO_c::setRecBufferSize(aui16_bufferSize);};

  /**
    deliver the actual receive buffer size
    @return receive buffer size
  */
  uint16_t rec_bufferSize()const{return RS232IO_c::rec_bufferSize();};

  /** get the channel */
  uint8_t getChannel() const { return RS232IO_c::getChannel(); }

  /**
    clear the receive buffer without reading of actual data in buffer
  */
  void clearRecBuffer()const{RS232IO_c::clearRecBuffer();};
  /**
    check if the receive buffer is empty
    @return true -> receive buffer is empty
  */
  bool eof()const{return RS232IO_c::eof();};
  /**
    deliver the count of data uint8_t in receive buffer
    @return amount of data bytes in receive buffer
  */
  uint16_t rec_bufferCnt()const{return RS232IO_c::rec_bufferCnt();};

  /* ******************************** */
  /* iostream related output operator */
  /* ********    sending     ******** */
  /* ******************************** */

  /**
    send data uint8_t string with given length on RS232

    possible errors:
        * Err_c::rs232_overflow send buffer buffer overflow during send
    @param rpData pointer to data string
    @param aui8_len length of data string
  */
  void send(const uint8_t* rpData, uint8_t aui8_len) {RS232IO_c::send(rpData, aui8_len);};

  /**
    send NULL terminated string on RS232 (terminating NULL isn't sent)

    possible errors:
        * Err_c::rs232_overflow send buffer buffer overflow during send
    @param apc_data pointer to NULL terminated string to send
    @return refernce to RS232IO_c for cmd like "rs232 << data1 << data2;"
  */
  iRS232IO_c& operator<<(const char *const apc_data)
    {return static_cast<iRS232IO_c&>(RS232IO_c::operator<<(apc_data));};
  /**
    send single uint8_t on RS232

    possible errors:
        * Err_c::rs232_overflow send buffer buffer overflow during send
    @param ab_data sent data byte
    @return refernce to RS232IO_c for cmd like "rs232 << data1 << data2;"
  */
  iRS232IO_c& operator<<(uint8_t ab_data)
    {return static_cast<iRS232IO_c&>(RS232IO_c::operator<<(ab_data));};
  /**
    send single int8_t on RS232

    possible errors:
        * Err_c::rs232_overflow send buffer buffer overflow during send
    @param ac_data sent data char
    @return refernce to RS232IO_c for cmd like "rs232 << data1 << data2;"
  */
  iRS232IO_c& operator<<(int8_t ac_data)
    {return static_cast<iRS232IO_c&>(RS232IO_c::operator<<(ac_data));};

  /**
    send uint16_t (2byte unsigned) value as text on RS232

    possible errors:
        * Err_c::rs232_overflow send buffer buffer overflow during send
    @param aui16_data sent data byte
    @return refernce to RS232IO_c for cmd like "rs232 << data1 << data2;"
  */
  iRS232IO_c& operator<<(uint16_t aui16_data)
    {return static_cast<iRS232IO_c&>(RS232IO_c::operator<<(aui16_data));};

  /**
    send int16_t (2 uint8_t unsigned) value as text on RS232

    possible errors:
        * Err_c::rs232_overflow send buffer buffer overflow during send
    @param ai16_data sent data byte
    @return refernce to RS232IO_c for cmd like "rs232 << data1 << data2;"
  */
  iRS232IO_c& operator<<(int16_t ai16_data)
    {return static_cast<iRS232IO_c&>(RS232IO_c::operator<<(ai16_data));};
  /**
    send uint32_t (4 uint8_t unsigned) value as text on RS232

    possible errors:
        * Err_c::rs232_overflow send buffer buffer overflow during send
    @param aui32_data sent data byte
    @return refernce to RS232IO_c for cmd like "rs232 << data1 << data2;"
  */
  iRS232IO_c& operator<<(uint32_t aui32_data)
    {return static_cast<iRS232IO_c&>(RS232IO_c::operator<<(aui32_data));};
  /**
    send int32_t (4 uint8_t signed) value as text on RS232

    possible errors:
        * Err_c::rs232_overflow send buffer buffer overflow during send
    @param ai32_data sent data byte
    @return refernce to RS232IO_c for cmd like "rs232 << data1 << data2;"
  */
  iRS232IO_c& operator<<(int32_t ai32_data)
    {return static_cast<iRS232IO_c&>(RS232IO_c::operator<<(ai32_data));};

  /**
    send float value as text on RS232

    possible errors:
        * Err_c::rs232_overflow send buffer buffer overflow during send
    @param af_data sent data byte
    @return refernce to RS232IO_c for cmd like "rs232 << data1 << data2;"
  */
  iRS232IO_c& operator<<(float af_data)
    {return static_cast<iRS232IO_c&>(RS232IO_c::operator<<(af_data));};

  /* ******************************** */
  /* iostream related output operator */
  /* ********    receiving     ******** */
  /* ******************************** */

  /**
    receive data uint8_t string with given length on RS232

    possible errors:
        * Err_c::rs232_underflow receive buffer underflow during receive
    @param pData pointer to data string
    @param aui16_len length of data string
  */
  void receive(uint8_t* pData, uint16_t aui16_len) {RS232IO_c::receive(pData, aui16_len);};
  /** read a line to the next apperance of '\n'.
      read nothing if the delimiter isn't found.
    @param pui8_data    pointer to buffer for writing the data
    @param ui8_lastChar terminating char for read ( default '\n' )
    @return HAL_NOACT_ERR -> nothing copied as delimiter not found;
            HAL_NO_ERR -> delimiter found; text before delimiter copied; delimiter removed
  */
  int16_t getLine( uint8_t* pui8_data, uint8_t ui8_lastChar = '\n' )
    { return RS232IO_c::getLine( pui8_data, ui8_lastChar );};

  /**
    receive '\n' (or buffer end) terminated string on RS232
    @param pb_data pointer to string to receive
    @return refernce to RS232IO_c for cmd like "rs232 >> data1 >> data2;"
  */
  iRS232IO_c& operator>>(uint8_t* pb_data)
    {return static_cast<iRS232IO_c&>(RS232IO_c::operator>>(pb_data));};
  /**
    receive single uint8_t on RS232 (ignore white spaces)

    possible errors:
        * Err_c::rs232_underflow receive buffer underflow during receive
    @param b_data received data byte
    @return refernce to RS232IO_c for cmd like "rs232 >> data1 >> data2;"
  */
  iRS232IO_c& operator>>(uint8_t& b_data)
    {return static_cast<iRS232IO_c&>(RS232IO_c::operator>>(b_data));};
  /**
    receive single int8_t on RS232 (ignore white spaces)

    possible errors:
        * Err_c::rs232_underflow receive buffer underflow during receive
    @param c_data received data char
    @return refernce to RS232IO_c for cmd like "rs232 >> data1 >> data2;"
  */
  iRS232IO_c& operator>>(int8_t& c_data)
    {return static_cast<iRS232IO_c&>(RS232IO_c::operator>>(c_data));};
  /**
    receive uint16_t (2byte unsigned) value as text on RS232
    (ignore white spaces)

    possible errors:
        * Err_c::rs232_underflow receive buffer underflow during receive
    @param ui16_data received data byte
    @return refernce to RS232IO_c for cmd like "rs232 >> data1 >> data2;"
  */
  iRS232IO_c& operator>>(uint16_t& ui16_data)
    {return static_cast<iRS232IO_c&>(RS232IO_c::operator>>(ui16_data));};
  /**
    receive int16_t (2 uint8_t unsigned) value as text on RS232
    (ignore white spaces)

    possible errors:
        * Err_c::rs232_underflow receive buffer underflow during receive
    @param i16_data received data byte
    @return refernce to RS232IO_c for cmd like "rs232 >> data1 >> data2;"
  */
  iRS232IO_c& operator>>(int16_t& i16_data)
    {return static_cast<iRS232IO_c&>(RS232IO_c::operator>>(i16_data));};
  /**
    receive uint32_t (4 uint8_t unsigned) value as text on RS232
    (ignore white spaces)

    possible errors:
        * Err_c::rs232_underflow receive buffer underflow during receive
    @param ui32_data received data byte
    @return refernce to RS232IO_c for cmd like "rs232 >> data1 >> data2;"
  */
  iRS232IO_c& operator>>(uint32_t& ui32_data)
    {return static_cast<iRS232IO_c&>(RS232IO_c::operator>>(ui32_data));};
  /**
    receive int32_t (4 uint8_t signed) value as text on RS232
    (ignore white spaces)

    possible errors:
        * Err_c::rs232_underflow receive buffer underflow during receive
    @param i32_data received data byte
    @return refernce to RS232IO_c for cmd like "rs232 >> data1 >> data2;"
  */
  iRS232IO_c& operator>>(int32_t& i32_data)
    {return static_cast<iRS232IO_c&>(RS232IO_c::operator>>(i32_data));};

  /**
    receive float value as text on RS232
    (ignore white spaces)

    possible errors:
        * Err_c::rs232_underflow receive buffer underflow during receive
    @param f_data received data byte
    @return refernce to RS232IO_c for cmd like "rs232 >> data1 >> data2;"
  */
  iRS232IO_c& operator>>(float& f_data)
    {return static_cast<iRS232IO_c&>(RS232IO_c::operator>>(f_data));};

private: //Private methods
  #if defined( RS232_INSTANCE_CNT ) && ( RS232_INSTANCE_CNT > 1 )
  /** allow getIrs232Instance() access to shielded base class.
      otherwise __IsoAgLib::getRs232Instance() wouldn't be accepted by compiler
    */
  friend iRS232IO_c& getIrs232Instance( uint8_t aui8_instance );
  #else
  /** allow getIrs232Instance() access to shielded base class.
      otherwise __IsoAgLib::getRs232Instance() wouldn't be accepted by compiler
    */
  friend iRS232IO_c& getIrs232Instance( void );
  #endif

  /** private constructor which prevents direct instantiation in user application
    * NEVER define instance of iRS232IO_c within application
    */
  iRS232IO_c( void ) : RS232IO_c() { };

};
#if defined( RS232_INSTANCE_CNT ) && ( RS232_INSTANCE_CNT > 1 )
  /** C-style function, to get access to the unique iRS232IO_c singleton instance
    * if more than one RS232 BUS is used for IsoAgLib, an index must be given to select the wanted BUS
    */
  inline iRS232IO_c& getIrs232Instance( uint8_t aui8_instance = 0 )
  { return static_cast<iRS232IO_c&>(__IsoAgLib::getRs232Instance(aui8_instance));};
#else
  /** C-style function, to get access to the unique iRS232IO_c singleton instance */
  inline iRS232IO_c& getIrs232Instance( void )
  { return static_cast<iRS232IO_c&>(__IsoAgLib::getRs232Instance());};
#endif
}

#endif
