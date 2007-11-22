/***************************************************************************
              target_extension_can_A1_binary.cpp - source for the
                     PSEUDO BIOS for development and test on
                     the Opus A1 with CAN communication using
                     the Binary can drivers for /dev/wecan0
                     and /dev/wecan1

                             -------------------
    begin                : Tue Oct 2 2001
    copyright            : (C) 1999 - 2004 Dipl.-Inform. Achim Spangler
    email                : a.spangler@osb-ag:de
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
 * Copyright (C) 1999 - 2004 Dipl.-Inform. Achim Spangler                 *
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

#include "can_target_extensions.h"
#include <IsoAgLib/hal/pc/system/system.h>
#include <IsoAgLib/hal/pc/system/system_target_extensions.h>
#include <IsoAgLib/driver/can/impl/canio_c.h>
#include <cstring>
#include <cstdio>
#include <cctype>


#ifdef WIN32
  #include <Windows.h>
  #include <stdio.h>
#else
  #include <sys/socket.h>
  #include <sys/un.h>
  #include <arpa/inet.h>
  #include <netdb.h>
  #include <sys/time.h>
  #include <sys/times.h>
  #include <linux/version.h>
#endif

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>

#include <list>

#include "can_server.h"

namespace __HAL {


// globals
static int32_t i32_lastReceiveTime = 0;
static SOCKET_TYPE i32_commandSocket = 0;
static SOCKET_TYPE i32_dataSocket = 0;
#ifdef WIN32
int32_t getStartUpTime()
{
  static int32_t st_startup4Times = timeGetTime();
  return st_startup4Times;
}
#endif

int32_t getPipeHandleForCanRcvEvent()
{
  return 0;
  //return msqDataClient.i32_pipeHandle;
}


SOCKET_TYPE call_socket(char *hostname, unsigned short portnum) 
{
  SOCKET_TYPE connectSocket = 0;
#ifdef WIN32
  // Create a SOCKET for listening for 
  // incoming connection requests
  connectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (connectSocket == INVALID_SOCKET) {
    printf("Error at socket(): %ld\n", WSAGetLastError());
    WSACleanup();
    return -1;
  }
  //----------------------
  // The sockaddr_in structure specifies the address family,
  // IP address, and port for the socket that is being bound.
  sockaddr_in service;
  service.sin_family = AF_INET;
  service.sin_addr.s_addr = inet_addr(CAN_SERVER_HOST);
  service.sin_port = htons(portnum);

  //----------------------
  // Connect to server.
  if (connect(connectSocket, (SOCKADDR*) &service, sizeof(service) ) == SOCKET_ERROR) {
    printf( "Failed to connect.\n" );
    WSACleanup();
    return -1;
  }

#else

  uint32_t ui32_len;

#ifdef USE_UNIX_SOCKET
  struct sockaddr_un sa;
  memset(&sa, 0, sizeof(struct sockaddr_un));   /* clear our address */
  sa.sun_family = SOCKET_TYPE_INET_OR_UNIX;
  sprintf(sa.sun_path, "%s.%d", SOCKET_PATH, portnum);
  ui32_len = strlen(sa.sun_path) + sizeof(sa.sun_family);
#else
  struct sockaddr_in sa;
  memset(&sa, 0, sizeof(struct sockaddr_in));   /* clear our address */
  sa.sin_addr.s_addr = inet_addr(CAN_SERVER_HOST);
  sa.sin_family = AF_INET;
  sa.sin_port= htons(portnum);
  ui32_len = sizeof(struct sockaddr_in);
#endif

  if ((connectSocket = socket(SOCKET_TYPE_INET_OR_UNIX, SOCK_STREAM, 0)) < 0)   /* get socket */
    return(-1);
  if (connect(connectSocket, (struct sockaddr *)&sa, ui32_len) < 0) {                  /* connect */
    close(connectSocket);
    return(-1);
  }

#endif
  return connectSocket;
}

int read_data(SOCKET_TYPE s,     /* connected socket */
              char *buf, /* pointer to the buffer */
              int n      /* number of characters (bytes) we want */
             )
{ int bcount; /* counts bytes read */
  int br;     /* bytes read this pass */

  bcount= 0;
  br= 0;
  while (bcount < n) {             /* loop until full buffer */
    if ((br= recv(s,buf,n-bcount,0)) > 0) {
      bcount += br;                /* increment byte counter */
      buf += br;                   /* move buffer ptr for next read */
    }
    else if (br <= 0)               /* signal an error or end of communication (0) to the caller */
      return br;
  }
  return(bcount);
}


int32_t send_command(transferBuf_s* p_writeBuf, SOCKET_TYPE ri32_commandSocket)
{
  int16_t i16_rc;

  if ((i16_rc = send(ri32_commandSocket, (char*)p_writeBuf, sizeof(transferBuf_s), 
#ifdef WIN32
                     0
#else
                     MSG_DONTWAIT
#endif
                     ) ) == -1)
  {
    perror("send");
    return HAL_UNKNOWN_ERR;
  }

  // wait for ACK
  if ((i16_rc = read_data(ri32_commandSocket, (char*)p_writeBuf, sizeof(transferBuf_s))) == -1)
  {
    perror("read_data");
    return HAL_UNKNOWN_ERR;
  }

  if (p_writeBuf->ui16_command == COMMAND_ACKNOWLEDGE)
  {
    if ( (p_writeBuf->s_acknowledge.i32_dataContent == ACKNOWLEDGE_DATA_CONTENT_ERROR_VALUE)
      && (p_writeBuf->s_acknowledge.i32_data != 0) )
    { // error!
      printf("NACK received in send_command\n");
      return p_writeBuf->s_acknowledge.i32_data;
    }
    else
    { // either ACK with NO error OR ACK with PIPE_ID, SEND_DELAY, etc.etc. which is okay!
      return HAL_NO_ERR;
    }
  }
  else
  { // wrong answer to a COMMAND. Must be COMMAND_ACKNOWLEDGE!
    printf("no ACK nor NACK received in send_command\n");
    return HAL_UNKNOWN_ERR;
  }
}

/////////////////////////////////////////////////////////////////////////
int16_t can_startDriver()
{
  DEBUG_PRINT("can_startDriver called\n");
#ifdef SYSTEM_WITH_ENHANCED_CAN_HAL
  printf("SYSTEM_WITH_ENHANCED_CAN_HAL is defined !\n");
#else
  printf("SYSTEM_WITH_ENHANCED_CAN_HAL is NOT defined !\n");
#endif

#ifdef WIN32
  // Initialize Winsock
  WSADATA wsaData;
  int iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
  if (iResult != NO_ERROR)
    printf("Error at WSAStartup()\n");
#endif

  i32_commandSocket = call_socket(CAN_SERVER_HOST, COMMAND_TRANSFER_PORT);

  // client registration
  transferBuf_s s_transferBuf;
  i32_dataSocket = call_socket(CAN_SERVER_HOST, DATA_TRANSFER_PORT);

#ifdef WIN32
  // Set the socket I/O mode: In this case FIONBIO
  // enables or disables the blocking mode for the 
  // socket based on the numerical value of iMode.
  // If iMode = 0, blocking is enabled; 
  // If iMode != 0, non-blocking mode is enabled.
  int iMode = 1;

  // set data socket to nonblocking, because we need MSG_PEEK, but there is no MSG_DONTWAIT in WIN32
  ioctlsocket(i32_dataSocket, FIONBIO, (u_long FAR*) &iMode);
#endif

  s_transferBuf.ui16_command = COMMAND_REGISTER;
  // call getTime just to be sure that start up time< is set
  getTime();

  s_transferBuf.s_startTimeClock.t_clock = getStartUpTime();

  int32_t i32_rc = send_command(&s_transferBuf, i32_commandSocket);

  if (i32_rc == HAL_NO_ERR) {

    if (s_transferBuf.s_acknowledge.i32_dataContent != ACKNOWLEDGE_DATA_CONTENT_PIPE_ID)
    {
      if (s_transferBuf.s_acknowledge.i32_dataContent == ACKNOWLEDGE_DATA_CONTENT_ERROR_VALUE)
      {
        return s_transferBuf.s_acknowledge.i32_data; // this is the error-code!
      }
      else
        return HAL_UNKNOWN_ERR;
    }
  }

  return i32_rc;
}

int16_t can_stopDriver()
{
  transferBuf_s s_transferBuf;

  DEBUG_PRINT("can_stopDriver called\n");

  s_transferBuf.ui16_command = COMMAND_DEREGISTER;

  return send_command(&s_transferBuf, i32_commandSocket);

}

int16_t init_can ( uint8_t bBusNumber,uint16_t wGlobMask,uint32_t dwGlobMask,uint32_t dwGlobMaskLastmsg,uint16_t wBitrate )
{
  transferBuf_s s_transferBuf;

  DEBUG_PRINT2("init_can, bus %d, bitrate %d\n", bBusNumber, wBitrate);

  if ( bBusNumber > HAL_CAN_MAX_BUS_NR ) return HAL_RANGE_ERR;

  s_transferBuf.ui16_command = COMMAND_INIT;
  s_transferBuf.s_init.ui8_bus = bBusNumber;
  s_transferBuf.s_init.ui16_wGlobMask = wGlobMask;
  s_transferBuf.s_init.ui32_dwGlobMask = dwGlobMask;
  s_transferBuf.s_init.ui32_dwGlobMaskLastmsg = dwGlobMaskLastmsg;
  s_transferBuf.s_init.ui16_wBitrate = wBitrate;

  return send_command(&s_transferBuf, i32_commandSocket);

};


int16_t changeGlobalMask( uint8_t bBusNumber,uint16_t wGlobMask,uint32_t dwGlobMask,uint32_t dwGlobMaskLastmsg )
{
  transferBuf_s s_transferBuf;

  DEBUG_PRINT1("changeGlobalMask, bus %d\n", bBusNumber);

  if ( bBusNumber > HAL_CAN_MAX_BUS_NR ) return HAL_RANGE_ERR;

  s_transferBuf.ui16_command = COMMAND_CHG_GLOBAL_MASK;
  s_transferBuf.s_init.ui8_bus = bBusNumber;
  s_transferBuf.s_init.ui16_wGlobMask = wGlobMask;
  s_transferBuf.s_init.ui32_dwGlobMask = dwGlobMask;
  s_transferBuf.s_init.ui32_dwGlobMaskLastmsg = dwGlobMaskLastmsg;

  return send_command(&s_transferBuf, i32_commandSocket);

};

int16_t closeCan ( uint8_t bBusNumber )
{
  transferBuf_s s_transferBuf;

  DEBUG_PRINT1("closeCan, bus %d\n", bBusNumber);

  if ( bBusNumber > HAL_CAN_MAX_BUS_NR ) return HAL_RANGE_ERR;

  s_transferBuf.ui16_command = COMMAND_CLOSE;
  s_transferBuf.s_init.ui8_bus = bBusNumber;

  // read/write queue is cleared by server!
  return send_command(&s_transferBuf, i32_commandSocket);

};

int16_t chgCanObjPause ( uint8_t bBusNumber, uint8_t bMsgObj, uint16_t wPause)
{
  // just to remove compiler warnings
  bBusNumber = bBusNumber; bMsgObj = bMsgObj; wPause = wPause;
  DEBUG_PRINT2("chgCanObjPause, bus %d, obj %d\n", bBusNumber, bMsgObj);
/*
  fprintf(stderr,"sende Pause auf BUS %d fuer CAN Objekt %d auf %d eingestellt\n",
  (int32_t)bBusNumber, (int32_t)bMsgObj, wPause);
  */
  return HAL_NO_ERR;
}

int16_t getCanBusStatus(uint8_t /*bBusNumber*/, tCanBusStatus* /*ptStatus*/)
{
  //DEBUG_PRINT1("getCanBusStatus, bus %d\n", bBusNumber);
  return HAL_NO_ERR;
}


int16_t configCanObj ( uint8_t bBusNumber, uint8_t bMsgObj, tCanObjConfig* ptConfig )
{
  DEBUG_PRINT2("configCanObj, bus %d, obj %d\n", bBusNumber, bMsgObj);

  transferBuf_s s_transferBuf;

  if ( ( bBusNumber > HAL_CAN_MAX_BUS_NR ) ) return HAL_RANGE_ERR;

  s_transferBuf.ui16_command = COMMAND_CONFIG;
  s_transferBuf.s_config.ui8_bus = bBusNumber;
  s_transferBuf.s_config.ui8_obj = bMsgObj;
  s_transferBuf.s_config.ui8_bXtd = ptConfig->bXtd;
  s_transferBuf.s_config.ui8_bMsgType = ptConfig->bMsgType;
  s_transferBuf.s_config.ui32_dwId = ptConfig->dwId;

  s_transferBuf.s_config.ui32_mask = ptConfig->mask;

  s_transferBuf.s_config.ui16_wNumberMsgs = ptConfig->wNumberMsgs;

  // read/write queue is cleared by server!
  return send_command(&s_transferBuf, i32_commandSocket);

};



int16_t closeCanObj ( uint8_t bBusNumber,uint8_t bMsgObj )
{
  transferBuf_s s_transferBuf;

  DEBUG_PRINT2("closeCanObj, bus %d, obj %d\n", bBusNumber, bMsgObj);

  if ( ( bBusNumber > HAL_CAN_MAX_BUS_NR ) ) return HAL_RANGE_ERR;

  s_transferBuf.ui16_command = COMMAND_CLOSEOBJ;
  s_transferBuf.s_config.ui8_bus = bBusNumber;
  s_transferBuf.s_config.ui8_obj = bMsgObj;

  // read / write queue is cleared by server!
  return send_command(&s_transferBuf, i32_commandSocket);

};

int16_t chgCanObjId ( uint8_t bBusNumber, uint8_t bMsgObj, uint32_t dwId, uint32_t mask, uint8_t bXtd )
{

  DEBUG_PRINT2("chgCanObjId, bus %d, obj %d\n", bBusNumber, bMsgObj);
  if ( ( bBusNumber > HAL_CAN_MAX_BUS_NR ) ) return HAL_RANGE_ERR;

  transferBuf_s s_transferBuf;

  s_transferBuf.ui16_command = COMMAND_CHG_CONFIG;
  s_transferBuf.s_config.ui8_bus = bBusNumber;
  s_transferBuf.s_config.ui8_obj = bMsgObj;
  s_transferBuf.s_config.ui8_bXtd = bXtd;
  s_transferBuf.s_config.ui32_dwId = dwId;

  s_transferBuf.s_config.ui32_mask = mask;

  return send_command(&s_transferBuf, i32_commandSocket);

}
/**
       lock a MsgObj to avoid further placement of messages into buffer.
  @param rui8_busNr number of the BUS to config
  @param rui8_msgobjNr number of the MsgObj to config
       @param rb_doLock true==lock(default); false==unlock
  @return HAL_NO_ERR == no error;
          HAL_CONFIG_ERR == BUS not initialised or ident can't be changed
          HAL_RANGE_ERR == wrong BUS or MsgObj number
       */
int16_t lockCanObj( uint8_t rui8_busNr, uint8_t rui8_msgobjNr, bool rb_doLock )
{

  transferBuf_s s_transferBuf;

  DEBUG_PRINT3("lockCanObj, bus %d, obj %d, lock %d\n", rui8_busNr, rui8_msgobjNr, rb_doLock);

  if ( ( rui8_busNr > HAL_CAN_MAX_BUS_NR ) ) return HAL_RANGE_ERR;

  if (rb_doLock)
    s_transferBuf.ui16_command = COMMAND_LOCK;
  else
    s_transferBuf.ui16_command = COMMAND_UNLOCK;

  s_transferBuf.s_config.ui8_bus = rui8_busNr;
  s_transferBuf.s_config.ui8_obj = rui8_msgobjNr;

  return send_command(&s_transferBuf, i32_commandSocket);

}

/**
       check if MsgObj is currently locked
  @param rui8_busNr number of the BUS to check
  @param rui8_msgobjNr number of the MsgObj to check
       @return true -> MsgObj is currently locked
*/
bool getCanMsgObjLocked( uint8_t rui8_busNr, uint8_t rui8_msgobjNr )
{

  int16_t i16_rc;
  transferBuf_s s_transferBuf;

  DEBUG_PRINT2("getCanMsgObjLocked, bus %d, obj %d\n", rui8_busNr, rui8_msgobjNr);

  if ( ( rui8_busNr > HAL_CAN_MAX_BUS_NR ) ) return true;
  else {

    s_transferBuf.ui16_command = COMMAND_QUERYLOCK;
    s_transferBuf.s_config.ui8_bus = rui8_busNr;
    s_transferBuf.s_config.ui8_obj = rui8_msgobjNr;

    i16_rc = send_command(&s_transferBuf, i32_commandSocket);

    if (!i16_rc)
    {
      if (s_transferBuf.s_acknowledge.i32_dataContent != ACKNOWLEDGE_DATA_CONTENT_QUERY_LOCK)
        return false;
      else
        return s_transferBuf.s_acknowledge.i32_data;
    }
    else
      return false;
  }

}


int16_t clearCanObjBuf(uint8_t bBusNumber, uint8_t bMsgObj)
{

  DEBUG_PRINT2("clearCanObjBuf, bus %d, obj %d\n", bBusNumber, bMsgObj);

  if ( ( bBusNumber > HAL_CAN_MAX_BUS_NR ) ) return HAL_RANGE_ERR;

  //  clearReadQueue(bBusNumber, bMsgObj, msqDataClient.i32_rdHandle, msqDataClient.i32_pid);
  //clearWriteQueue(bBusNumber, bMsgObj, msqDataClient.i32_wrHandle, msqDataClient.i32_pid);

  return HAL_NO_ERR;
}


/** get last timestamp of CAN receive */
int32_t can_lastReceiveTime()
{
  DEBUG_PRINT("can_lastReceiveTime\n");
  return i32_lastReceiveTime;
}

int16_t getCanMsgBufCount(uint8_t bBusNumber,uint8_t bMsgObj)
{
  int32_t i32_rc;
  transferBuf_s s_transferBuf;

  memset(&s_transferBuf, 0, sizeof(transferBuf_s));
  if ((i32_rc = recv(i32_dataSocket, (char*)&s_transferBuf, sizeof(transferBuf_s), 
#ifdef WIN32
                     0
#else
                     MSG_DONTWAIT
#endif
                     | MSG_PEEK)) > 0)
  {
    if (((bMsgObj == s_transferBuf.s_data.ui8_obj) || (bMsgObj == COMMON_MSGOBJ_IN_QUEUE)) && (bBusNumber == s_transferBuf.s_data.ui8_bus))
    {
      return 1;
    }
  }

  return 0;

};

bool waitUntilCanReceiveOrTimeout( uint16_t rui16_timeoutInterval )
{
  int16_t i16_rc;
  fd_set rfds;
  struct timeval s_timeout;
  static uint8_t ui8_buf[16];

  FD_ZERO(&rfds);
  FD_SET(i32_dataSocket, &rfds);

  s_timeout.tv_sec = 0;
  s_timeout.tv_usec = rui16_timeoutInterval * 1000;

  i16_rc = select(FD_SETSIZE, &rfds, NULL, NULL, &s_timeout);

  // return true, when the timeout was NOT the trigger for coming back from select
  return ( i16_rc > 0 )?true:false;
};

// MDS NOTE: This is code is highly inefficient and needs to be optimized!
//  The receive structure should be changed so that it does not need to be copied from
//  one structure to another 3 or 4 times before sending it to the higher levels.
//  This should be done at most once!
//  There are several different CAN msg receive structures defined, and that should be
//  changed to only one through this file, and the one defined externally.
int16_t getCanMsg ( uint8_t bBusNumber,uint8_t bMsgObj, tReceive * ptReceive )
{

  int32_t i32_rc;
  transferBuf_s s_transferBuf;

  //DEBUG_PRINT2("getCanMsg, bus %d, obj %d\n", bBusNumber, bMsgObj);

  if ( ( bBusNumber > HAL_CAN_MAX_BUS_NR ) ) return HAL_RANGE_ERR;

  const uint8_t cui8_useMsgObj = bMsgObj;

  memset(&s_transferBuf, 0, sizeof(transferBuf_s));
  if ((i32_rc = recv(i32_dataSocket, (char*)&s_transferBuf, sizeof(transferBuf_s), 
#ifdef WIN32
                     0
#else
                     MSG_DONTWAIT
#endif
                     | MSG_PEEK)) > 0)
  {
    if ( ((bMsgObj == s_transferBuf.s_data.ui8_obj) || (bMsgObj == COMMON_MSGOBJ_IN_QUEUE)) && (bBusNumber == s_transferBuf.s_data.ui8_bus))
    {
      ; // message fits
    }
    else
      return HAL_UNKNOWN_ERR;
  }
  else
    return HAL_UNKNOWN_ERR;

  // we assemble the mtype with FALSE here, as we do NOT have sendPriorities in this direction!
  if ((i32_rc = read_data(i32_dataSocket, (char*)&s_transferBuf, sizeof(transferBuf_s))) == -1)
  {
    // bus filter ????
    return HAL_UNKNOWN_ERR;
  }

  i32_lastReceiveTime = getTime();

  // copy data
  ptReceive->dwId = s_transferBuf.s_data.s_canMsg.ui32_id;
  ptReceive->bMsgObj = s_transferBuf.s_data.ui8_obj;
  ptReceive->bDlc = s_transferBuf.s_data.s_canMsg.i32_len;
  // prevent timestamp which is in the future! (because of 10ms clock jitter)
  ptReceive->tReceiveTime.l1ms = (i32_lastReceiveTime > s_transferBuf.s_data.i32_sendTimeStamp) ? s_transferBuf.s_data.i32_sendTimeStamp : i32_lastReceiveTime;
  ptReceive->bXtd = s_transferBuf.s_data.s_canMsg.i32_msgType;
  memcpy(ptReceive->abData, s_transferBuf.s_data.s_canMsg.ui8_data, s_transferBuf.s_data.s_canMsg.i32_len);

#ifdef DEBUG_CAN
  printf("Empfang: %x  %hx %hx %hx %hx %hx %hx %hx %hx\n", ptReceive->dwId,
         ptReceive->abData[0], ptReceive->abData[1], ptReceive->abData[2],
         ptReceive->abData[3], ptReceive->abData[4], ptReceive->abData[5],
         ptReceive->abData[6], ptReceive->abData[7]);
#endif

  return HAL_NO_ERR;

};



int16_t sendCanMsg ( uint8_t bBusNumber,uint8_t bMsgObj, tSend* ptSend )
{
  int32_t i32_rc;

  DEBUG_PRINT2("sendCanMsg, bus %d, obj %d\n", bBusNumber, bMsgObj);
  transferBuf_s s_transferBuf;

#ifdef DEBUG_CAN
  printf("Senden: %x  %hx %hx %hx %hx %hx %hx %hx %hx\n", ptSend->dwId,
         ptSend->abData[0], ptSend->abData[1], ptSend->abData[2],
         ptSend->abData[3], ptSend->abData[4], ptSend->abData[5],
         ptSend->abData[6], ptSend->abData[7]);
#endif

  memset(&s_transferBuf, 0, sizeof(transferBuf_s));

  s_transferBuf.ui16_command = COMMAND_DATA;
  s_transferBuf.s_data.ui8_bus = bBusNumber;
  s_transferBuf.s_data.ui8_obj = bMsgObj;
  s_transferBuf.s_data.s_canMsg.ui32_id = ptSend->dwId;
  s_transferBuf.s_data.s_canMsg.i32_len = ptSend->bDlc;
  s_transferBuf.s_data.s_canMsg.i32_msgType = ptSend->bXtd;
  s_transferBuf.s_data.i32_sendTimeStamp = getTime();
  memcpy(s_transferBuf.s_data.s_canMsg.ui8_data, ptSend->abData, 8);

  if ((i32_rc = send(i32_dataSocket, (char*)&s_transferBuf, sizeof(transferBuf_s), 
#ifdef WIN32
        0
#else
        MSG_DONTWAIT
#endif
     )) == -1)
  {
    perror("send");
    return HAL_UNKNOWN_ERR;
  }

  if (s_transferBuf.ui16_command == COMMAND_ACKNOWLEDGE )
  {
    if (s_transferBuf.s_acknowledge.i32_dataContent == ACKNOWLEDGE_DATA_CONTENT_ERROR_VALUE)
    {
#ifdef DEBUG
      if ((s_transferBuf.s_acknowledge.i32_data != HAL_NO_ERR) && (s_transferBuf.s_acknowledge.i32_data != HAL_NEW_SEND_DELAY)) // == i32_error
      {
        printf("acknowledge-error received in sendCanMsg\n");
      }
#endif
      return s_transferBuf.s_acknowledge.i32_data;
    }
  }
  // other unexpected answer - shouldn't occur!
  return HAL_UNKNOWN_ERR;

};

/** @todo maybe make return code the error code and pass the ref to the value as parameter?
 * for now, simply no error code is generated! */
int32_t getMaxSendDelay(uint8_t rui8_busNr)
{
#if 0
  transferBuf_s s_transferBuf;

  DEBUG_PRINT1("getMaxSendDelay called, bus %d\n", rui8_busNr);

/*  if ( bBusNumber > HAL_CAN_MAX_BUS_NR ) return HAL_RANGE_ERR; */

  s_transferBuf.i32_mtypePid = msqDataClient.i32_pid;
  s_transferBuf.ui16_command = COMMAND_SEND_DELAY;
  s_transferBuf.s_config.ui8_bus = rui8_busNr;
  // the other fields of the s_config struct are NOT of interest here!

  int i16_rc = send_command(&s_transferBuf, i32_commandSocket);
  if (i16_rc == HAL_NO_ERR)
  { // we got an answer - see if it was ACKNOWLEDGE_DATA_CONTENT_SEND_DELAY
    if (s_transferBuf.s_acknowledge.i32_dataContent == ACKNOWLEDGE_DATA_CONTENT_SEND_DELAY)
    { // yihaa, we got what we wanted!
      return s_transferBuf.s_acknowledge.i32_data;
    }
  }

  perror("msgsnd");
#endif
  return 0; // we don't have no error code, we can just return some error-maxDelay instead
}

}; // end namespace __HAL