#include "globals.h"
#include "Can1.h"
#include "PWM1.h"
#include "PWM2.h"
#include "ADC0.h"
#include "SW1.h"
#include "SW2.h"
#include "lookup.h"


void loop();


// Ranges for ADC inputs.
// Steer 		3784	32376	63672    approx values left,centre, right
// trigger	42368	4032		approx values trigger not touched, trigger full


uint16_t ADCs[6] = {0,0,0,0,0,0};	
uint8_t count_VSP = 0, count_MMI = 0, CRC = 0;


typedef union CAN_msg_t
{
	uint8_t bytes[8];
	uint16_t words[4];
} CAN_msg_t;

static uint8_t CRC_calc(CAN_msg_t* msg);
uint8_t timestamp;

uint16_t Compute_CRC16_Simple(byte bytes[]);

void loop()
{
	CAN_msg_t data;
uint16_t ADVals[6];
	uint8_t err;
	uint16_t CRCVar;
	int i;
	int shifterInt;
	err = ADC0_GetValue16(ADCs);
	for (i=0;i<6;i++){
			ADVals[i]=ADCs[i];
	}
	
	// pack the CAN packets
	
	if(0 == (ms % 100))
	{	
		if (0 == (ms % 500)){
		// MMI Message
		data.bytes[0] = 0x00;  //	propriatery A			lookup_u16_s16(ADCs[4], Torque_X, Torque_Y, 5);
		data.bytes[1] = 0x11;	// off road non reaction
		data.bytes[2] = 0x5F;     // GPS1 receiver , AUX steering not allowed
		data.bytes[3] = 0x30;	// AUX program 1 (no idea what that is)
		data.bytes[4] = 0xFF;	// reserved
		data.bytes[5] = count_MMI; 
		CRCVar = Compute_CRC16_Simple(&data.bytes[0]);
		data.bytes[7] = (uint8_t)((CRCVar&0xFF00) >> 8);
		data.bytes[6] = (uint8_t)(CRCVar&0x00FF);
		err = CAN1_SendFrame(1,0xCEF13FC|CAN_EXTENDED_FRAME_ID, DATA_FRAME, 8, &data.bytes[0]);
		// set up MMI S message
		
		data.bytes[0]=2; //MMI_XID for safety controller
		CRCVar = Compute_CRC16_Simple(&data.bytes[0]);
		data.bytes[7] = (uint8_t)((CRCVar&0xFF00) >> 8);
		data.bytes[6] = (uint8_t)(CRCVar&0x00FF);
		do{
			err = CAN1_SendFrame(1,0xCEF5AFC|CAN_EXTENDED_FRAME_ID, DATA_FRAME, 8, &data.bytes[0]);
			} while (err!=0);
		
		count_MMI++;
		if (count_MMI>15) {
			count_MMI = 0;
				}
		}
		// VSP Message
				data.bytes[0] = 0xFF;  //	Reserved
				data.bytes[1] = 0x3F;	// forward direction
				data.bytes[2] = 0xFF;     // 255 lsb = 1kph
				data.bytes[3] = 0x00;	// msb speed = 0
				data.bytes[4] = 0xFF;	// reserved
				data.bytes[5] = 0xF0+count_VSP; 
				CRCVar = Compute_CRC16_Simple(&data.bytes[0]);
				data.bytes[7] = (uint8_t)((CRCVar&0xFF00) >> 8);
				data.bytes[6] = (uint8_t)(CRCVar&0x00FF);
				do{
				err = CAN1_SendFrame(1,0xCFF40FB|CAN_EXTENDED_FRAME_ID, DATA_FRAME, 8, &data.bytes[0]);
				} while (err!=0);
				do{
				err = CAN1_SendFrame(1,0xCFF41FB|CAN_EXTENDED_FRAME_ID, DATA_FRAME, 8, &data.bytes[0]);
				} while (err!=0);
				count_VSP++;
				if (count_VSP>15) {
					count_VSP = 0;
				}	
				
		// steering command messag
				
				shifterInt = ADVals[5]-32376;  // make it +- around zero
				shifterInt = shifterInt/40; 	// shrink the range
				ADVals[5]=shifterInt+32128;	// put it back to unsigned integer 16 32128 =0 from datasheet
				
				data.bytes[1] = (uint8_t)((ADVals[5]&0xFF00) >> 8);
				data.bytes[0] = (uint8_t)(ADVals[5]&0x00FF);
				
				if (ADVals[4]>20000){ //if trigger not touched
					data.bytes[2] = 0xFC;  // command not intended for steering
					}else {
					data.bytes[2] = 0xFD;   // command intended for steering
					}
				
				//data.bytes[2] = 0xFC;	// command not intended for steering
				data.bytes[3] = 0xFF;     // reserved
				data.bytes[4] = 0xFF;     // reserved
				data.bytes[5] = 0xFF;		//reserved
				data.bytes[6] = 0xFF;     // reserved
				data.bytes[7] = 0xFF;     // reserved
					
				do{
					err = CAN1_SendFrame(1,0xCAD131C|CAN_EXTENDED_FRAME_ID, DATA_FRAME, 8, &data.bytes[0]);
					} while (err!=0);

				
				
// SASA message
		
	/*	data.bytes[0] = 0xF1;  //	steering angle 0
		data.bytes[1] = 0x06;	// off road non reaction
		data.bytes[2] = 0x00;     // steering velocity
		data.bytes[3] = 0x50;	// 0
		data.bytes[4] = 0xFF;	// reserved
		data.bytes[5] = 0xF0+count; 
		CRCVar = Compute_CRC16_Simple(&data.bytes[0]);
		data.bytes[7] = (uint8_t)((CRCVar&0xFF00) >> 8);
		data.bytes[6] = (uint8_t)(CRCVar&0x00FF);
		
		do{
		err = CAN1_SendFrame(1,0xCFF104D|CAN_EXTENDED_FRAME_ID, DATA_FRAME, 8, &data.bytes[0]);
		} while (err!=0);
		do{
		err = CAN1_SendFrame(1,0xCFF114D|CAN_EXTENDED_FRAME_ID, DATA_FRAME, 8, &data.bytes[0]);
		} while (err!=0); */
				
		
		//data.words[0] = ADCs[0];
		//data.words[1] = ADCs[1];
		//data.words[2] = ADCs[2];
		//data.words[3] = ADCs[3];
		
		//err = CAN1_SendFrame(1, 0x200, DATA_FRAME, 8, &data.bytes[0]);
		
		//data.words[0] = ADCs[4];
		//data.words[1] = ADCs[5];
		//if(SW1_GetVal()) { data.words[2] = 0xFFFF; } else { data.words[2] = 0; }
		//if(SW2_GetVal()) { data.words[3] = 0xFFFF; } else { data.words[3] = 0; }
		
		//err = CAN1_SendFrame(2, 0x201, DATA_FRAME, 8, &data.bytes[0]);
		
	}

}


uint16_t Compute_CRC16_Simple(byte bytes[6])
{
    const uint16_t generator = 0xC86C; /* divisor is 16bit */
    uint16_t crc = 0; /* CRC value is 16bit */
    byte b;
    int bytecount;
    int i;
int test;
    for (bytecount=0;bytecount<=sizeof(bytes)*2-1;bytecount++)
   // foreach (byte b in bytes)
 
    {   
    	test = sizeof(bytes);
    	b=bytes[bytecount];
        crc ^= (uint16_t)(b << 8); /* move byte into MSB of 16bit CRC */

        for (i = 0; i < 8; i++)
        {
            if ((crc & 0x8000) != 0) /* test for MSB = bit 15 */
            {
                crc = (uint16_t)((crc << 1) ^ generator);
            }
            else
            {
                crc <<= 1;
            }
        }
    }

    return crc;
}
