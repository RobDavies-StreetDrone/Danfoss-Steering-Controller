/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : CAN1.h
**     Project     : S12Z_CAN_DBW
**     Processor   : MC9S12ZVCA192MLF
**     Component   : FreescaleCAN
**     Version     : Component 02.366, Driver 01.31, CPU db: 3.00.000
**     Compiler    : CodeWarrior HCS12Z C Compiler
**     Date/Time   : 2022-01-04, 11:40, # CodeGen: 4
**     Abstract    :
**         This component "FreescaleCAN" implements a CAN serial channel.
**     Settings    :
**         CAN channel                                     : MSCAN0
**
**           Interrupt service/event                       : Enabled
**             Output interrupt
**               Vector name                               : Vcan0tx
**               Priority                                  : 4
**             Input interrupt
**               Vector name                               : Vcan0rx
**               Priority                                  : 4
**             Error interrupt
**               Vector name                               : Vcan0err
**               Priority                                  : 4
**             Wakeup interrupt
**               Vector name                               : Vcan0wkup
**               Priority                                  : 4
**
**          Settings                                       : 
**                Rx pin                                   : CANPHY0_RXD_to_MSCAN0_RXD
**                Rx pin signal                            : 
**                Tx pin                                   : MSCAN0_TXD_to_CANPHY0_TXD
**                Tx pin Signal                            : 
**
**
**            Recieve accept. code                         : 0x20202040
**            Recieve accept. mask                         : 0x00
**            Loop Mode                                    : no
**            Bus-Off Recovery                             : Auto
**            Listen Only Mode                             : no
**            Wakeup                                       : Disabled
**
**         Protocol
**             Time segment 1                              : 10
**             Time segment 2                              : 3
**             RSJ                                         : 3
**             Samples per bit                             : One sample
**             Time quanta per bit                         : 16
**             Init baud rate                              : 250 kbit/s
**
**         Initialization
**             Enabled in init. code                       : yes
**             Events enabled in init.                     : yes
**
**         CPU clock/speed selection
**             High speed mode                             : This component enabled
**             Low speed mode                              : This component disabled
**             Slow speed mode                             : This component disabled
**
**     Contents    :
**         SendFrame - byte CAN1_SendFrame(byte BufferNum, dword MessageID, byte FrameType, byte...
**         ReadFrame - byte CAN1_ReadFrame(dword *MessageID, byte *FrameType, byte *FrameFormat,...
**
**     Copyright : 1997 - 2014 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file CAN1.h
** @version 01.31
** @brief
**         This component "FreescaleCAN" implements a CAN serial channel.
*/         
/*!
**  @addtogroup CAN1_module CAN1 module documentation
**  @{
*/         

#ifndef __CAN1
#define __CAN1

#include "Cpu.h"

/*Include shared modules, which are used for whole project*/
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"

/* MODULE CAN1. */

#ifndef __BWUserType_CAN1_TError
#define __BWUserType_CAN1_TError
/*lint -save  -esym(960,18.4) Disable MISRA rule (18.4) checking. */
  typedef union {
    word err;
    struct {
      /*lint -save  -e46 Disable MISRA rule (6.4) checking. */
      bool OverRun : 1;                /* Overrun error flag */
      bool RxBufOvf : 1;               /* Rx buffer full error flag */
      bool Idle : 1;                   /* Idle character detect */
      bool BusOff : 1;                 /* Bus-off state */
      bool TxPassive : 1;              /* Transmitter error passive */
      bool RxPassive : 1;              /* Reciver error passive */
      bool TxWarning : 1;              /* Transmitter warning */
      bool RxWarning : 1;              /* Receiver warning */
      bool Ack : 1;                    /* Acknowledge error */
      bool Crc : 1;                    /* CRC error */
      bool Form : 1;                   /* Form error */
      bool Stuff : 1;                  /* Stuff bit error */
      bool Bit0 : 1;                   /* Bit 0 error */
      bool Bit1 : 1;                   /* Bit 1 error */
      /*lint -restore Enable MISRA rule (6.4) checking. */
    }errName;
  } CAN1_TError;                       /* Error flags. For languages which don't support bit access is byte access only to error flags possible. */
/*lint -restore  +esym(960,18.4) Enable MISRA rule (18.4) checking. */
#endif

#pragma DATA_SEG CAN1_DATA             /* Select data segment "CAN1_DATA" */
#pragma CODE_SEG CAN1_CODE

/* User constants */

/* Message filterring */
#define TWO_32_FILTERS                  0x00U
#define FOUR_16_FILTERS                 0x01U
#define EIGHT_8_FILTERS                 0x02U
#define FILTER_CLOSED                   0x03U

/* Frame formats */
#define STANDARD_FORMAT                 0x00U
#define EXTENDED_FORMAT                 0x01U

/* Frame types   */
#define DATA_FRAME                      0x00U
#define REMOTE_FRAME                    0x01U

/* Extended message ID identifier.  This constant can be used to specify an extended message ID
 * anywhere the message ID is required.
 */
#define CAN_EXTENDED_FRAME_ID           0x80000000UL       /* Extended message ID identifier */

/* Global variables */

byte CAN1_SendFrame(byte BufferNum,dword MessageID,byte FrameType,byte Length,const byte *Data);
/*
** ===================================================================
**     Method      :  CAN1_SendFrame (component FreescaleCAN)
**     Description :
**         Sends the frame via the CAN device. Using this method the
**         user can send own message to the CAN bus. This method allows
**         to specify CAN buffer number, message ID, data to be sent
**         and frame type (DATA_FRAME/REMOTE_FRAME).
**     Parameters  :
**         NAME            - DESCRIPTION
**         BufferNum       - Number of the buffer.
**         MessageID       - Identification of the message
**                           - ID. Message ID can be specified in the
**                           STANDARD format (default) or the EXTENDED
**                           format. The most significant bit in the ID
**                           is set to specify EXTENDED format.
**                           Predefined macro CAN_EXTENDED_FRAME_ID can
**                           be used (ID "bitwise or"
**                           CAN_EXTENDED_FRAME_ID) to mark ID as
**                           extended. If the most significant bit of ID
**                           is clear, STANDARD format is used.
**         FrameType       - Type of frame
**                           DATA_FRAME - data frame
**                           REMOTE_FRAME - remote frame
**         Length          - The length of the frame in bytes (0..
**                           8)
**       * Data            - Pointer to data
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - This component is disabled
**                           by user
**                           ERR_VALUE - Some parameter is out of
**                           possible range
**                           ERR_TXFULL - Transmition buffer is full.
** ===================================================================
*/

byte CAN1_ReadFrame(dword *MessageID, byte *FrameType, byte *FrameFormat, byte *Length, byte *Data);
/*
** ===================================================================
**     Method      :  CAN1_ReadFrame (component FreescaleCAN)
**     Description :
**         Reads a frame from the CAN device. The user is informed
**         about CAN reception through OnFullRxBuffer event or
**         GetStateRX method.
**     Parameters  :
**         NAME            - DESCRIPTION
**       * MessageID       - Pointer to a message
**                           indentification
**       * FrameType       - Pointer to a frame type
**                           DATA_FRAME - data frame
**                           REMOTE_FRAME - remote frame
**       * FrameFormat     - Pointer to a frame format
**                           STANDARD_FORMAT - standard frame 11-bits
**                           EXTENDED_FORMAT - extended frame 29-bits.
**                           Note: This parameter is obsolete and will
**                           be removed in future releases.
**       * Length          - Pointer to a length of the frame
**       * Data            - The buffer for received data
**     Returns     :
**         ---             - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - This component is disabled
**                           by user
**                           ERR_RXEMPTY - The receive buffer is empty
**                           ERR_OVERRUN - The previous (unread) message
**                           in the receive buffer was overwriten by a
**                           new message. Returns only if Interrupt
**                           service is enabled.
** ===================================================================
*/

void CAN1_Init(void);
/*
** ===================================================================
**     Method      :  CAN1_Init (component FreescaleCAN)
**
**     Description :
**         Initializes the associated peripheral(s) and the components 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void CAN1_InterruptRx(void);
#pragma CODE_SEG CAN1_CODE
/*
** ===================================================================
**     Method      :  CAN1_InterruptRx (component FreescaleCAN)
**
**     Description :
**         The method services the receive interrupt of the selected 
**         peripheral(s) and eventually invokes the components event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/

#pragma CODE_SEG __NEAR_SEG NON_BANKED
__interrupt void CAN1_InterruptError(void);
#pragma CODE_SEG CAN1_CODE
/*
** ===================================================================
**     Method      :  CAN1_InterruptError (component FreescaleCAN)
**
**     Description :
**         The method services the error interrupt of the selected 
**         peripheral(s) and eventually invokes the components event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/



#pragma DATA_SEG DEFAULT               /* Select data segment "DEFAULT" */
#pragma CODE_SEG DEFAULT

/* END CAN1. */

#endif /* ifndef __CAN1 */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.3 [05.09]
**     for the Freescale HCS12Z series of microcontrollers.
**
** ###################################################################
*/