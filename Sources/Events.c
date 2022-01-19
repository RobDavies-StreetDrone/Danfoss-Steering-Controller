/* ###################################################################
**     Filename    : Events.c
**     Project     : Test_S12Z
**     Processor   : MC9S12ZVCA192MLF
**     Component   : Events
**     Version     : Driver 01.04
**     Compiler    : CodeWarrior HCS12Z C Compiler
**     Date/Time   : 2017-06-30, 22:54, # CodeGen: 0
**     Abstract    :
**         This is user's event module.
**         Put your event handler code here.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file Events.c
** @version 01.04
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         
/* MODULE Events */


#include "Cpu.h"
#include "Events.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

#include "globals.h"
#include "IO_Map.h"

#pragma CODE_SEG DEFAULT

/*
** ===================================================================
**     Event       :  CAN1_OnFullRxBuffer (module Events)
**
**     Component   :  CAN1 [FreescaleCAN]
**     Description :
**         This event is called when the receive buffer is full after a
**         successful reception of a message. The event is available
**         only if Interrupt service/event is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/

/*
struct CANIDR_struct
{
	union
	{
		VUINT32	R;
		struct
		{
			VUINT16	W1;
			VUINT16	W2;
		} WORDS;
		struct
		{
			VUINT8	DUMMY	:3;
			VUINT8	IDE		:1;
			VUINT8	SRR		:1;
			VUINT16	STD_ID	:11;
			VUINT16	DUMMY2;
		} IDR_STD;
		struct
		{
			VUINT8	MID3	:3;
			VUINT8	IDE		:1;
			VUINT8	SRR		:1;
			VUINT16	TOP11	:11;
			VUINT8	RTR		:1;
			VUINT16	BOT15	:15;
		} IDR_EXT;
    } IDR;
};

volatile struct CANIDR_struct *CANRX = (struct CANIDR_struct *)(REG_BASE + 0x00000820);

#define CAN0RXIDR CANRX->IDR
*/

void CAN1_OnFullRxBuffer(void)
{
  /* Write your code here ... */
	
	static VUINT16 timestamp;
	static VUINT8 dlc,filter;
	VUINT8 i;
	
	//id = CAN0RXIDR.IDR_STD.STD_ID;
	
	filter = CAN0IDAC_IDHIT;
	dlc = CAN0RXDLR_DLC;
	timestamp = CAN0RXTSR;
	
	CANRX_timestamp[filter] = CAN0RXTSR;
	
	for (i=0;i<CAN0RXDLR_DLC;i++)
		CANRX_data[filter][i] = CAN0RXDSR_ARR[i];
		
	CAN0RFLG |= CAN0RFLG_RXF_MASK; // clear Rx flag
}

/*
** ===================================================================
**     Event       :  TI1_OnInterrupt (module Events)
**
**     Component   :  TI1 [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void TI1_OnInterrupt(void)
{
  /* Write your code here ... */
	
	extern uint16_t ms;
	extern uint16_t ms_rollovers;
	
	if(0xFFFF == ms) ms_rollovers++;
	ms++;
}

/*
** ===================================================================
**     Event       :  ADC0_OnEnd (module Events)
**
**     Component   :  ADC0 [ADC]
**     Description :
**         This event is called after the measurement (which consists
**         of <1 or more conversions>) is/are finished.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ADC0_OnEnd(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  ADC0_OnError (module Events)
**
**     Component   :  ADC0 [ADC]
**     Description :
**         This event is called when some of the error interrupts (not
**         the error returned by a given method) occur. The errors can
**         be read using <GetError> method.
**         The event is available only when the <Interrupt
**         service/event> property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ADC0_OnError(void)
{
  /* Write your code here ... */
}

/*
** ===================================================================
**     Event       :  ADC0_OnAbort (module Events)
**
**     Component   :  ADC0 [ADC]
**     Description :
**         This event is called when abort interupt occurs. The event
**         is available only when the <Interrupt service/event>
**         property is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void ADC0_OnAbort(void)
{
  /* Write your code here ... */
}

/* END Events */

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
