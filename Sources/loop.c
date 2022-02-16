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
uint16_t Compute_CRC16(byte bytes[6]);

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
		CRCVar = Compute_CRC16(&data.bytes[0]);
		data.bytes[7] = (uint8_t)((CRCVar&0xFF00) >> 8);
		data.bytes[6] = (uint8_t)(CRCVar&0x00FF);
		err = CAN1_SendFrame(1,0xCEF13FC|CAN_EXTENDED_FRAME_ID, DATA_FRAME, 8, &data.bytes[0]);
		// set up MMI S message
		
		data.bytes[0]=2; //MMI_XID for safety controller 
		CRCVar = Compute_CRC16(&data.bytes[0]);
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
				CRCVar = Compute_CRC16(&data.bytes[0]);
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
uint16_t crctable16[]={0,51308,22708,37080,45416,30980,59868,8624,43708,25296,61960,14948,7124,
		54200,17248,35596,40212,21880,50592,3532,11388,58384,29896,48292,14248,65476,28444,
		42864,34496,20140,56948,5656,62020,14888,43760,25244,17196,35648,7064,54260,22776,
		37012,76,51232,59792,8700,45348,31048,28496,42812,14308,65416,56888,5716,34444,20192,
		50668,3456,40280,21812,29828,48360,11312,58460,11492,58504,29776,48188,40332,21984,50488,
		3412,34392,20020,57068,5760,14128,65372,28548,42984,45552,31132,59716,8488,152,51444,
		22572,36928,6988,54048,17400,35732,43556,25160,62096,15100,56992,5836,34324,20088,28616,
		42916,14204,65296,29724,48240,11432,58564,50548,3352,40384,21932,17332,35800,6912,54124,
		62172,15024,43624,25092,59656,8548,45500,31184,22624,36876,212,51384,22984,37284,380,51472,
		59552,8396,45076,30840,62324,15128,43968,25516,16924,35440,6824,53956,50396,3248,40040,
		21508,30132,48600,11520,58732,28256,42508,14036,65208,57096,5988,34748,20432,43916,25568,
		62264,15188,6884,53896,16976,35388,304,51548,22916,37352,45144,30772,59628,8320,13976,65268,
		28204,42560,34800,20380,57156,5928,39972,21576,50320,3324,11596,58656,30200,48532,29996,
		48448,11672,58868,50244,3112,40176,21660,57232,6140,34596,20296,28408,42644,13900,65056,
		59448,8276,45196,30944,22864,37180,484,51592,17028,35560,6704,53852,62444,15232,43864,
		25396,34664,20228,57308,6064,13824,65132,28340,42712,11732,58808,30048,48396,40124,21712,
		50184,3172,6780,53776,17096,35492,43796,25464,62368,15308,45248,30892,59508,8216,424,
		51652,22812,37232};

uint16_t Compute_CRC16(byte bytes[6])
{
	
    uint16_t crc = 0;
  byte pos;
  byte b;
  int bytecount;
    //foreach (byte b in bytes)
    for (bytecount=0;bytecount<=sizeof(bytes)*2-1;bytecount++)
    {
    	b=bytes[bytecount];
        /* XOR-in next input byte into MSB of crc, that's our new intermediate divident */
        pos = (byte)( (crc >> 8) ^ b); /* equal: ((crc ^ (b << 8)) >> 8) */
        /* Shift out the MSB used for division per lookuptable and XOR with the remainder */
        crc = (uint16_t)((crc << 8) ^ (uint16_t)(crctable16[pos]));

    }

    return crc;
}

