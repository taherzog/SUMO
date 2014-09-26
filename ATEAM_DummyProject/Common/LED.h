/*
 * LED.h
 *
 *  Created on: 26.09.2014
 *      Author: reto
 */

#ifndef LED_H_
#define LED_H_

//#include "LedBit1.h"
//
//#define LED1_On()		LedBit1_ClrVal()
//#define LED1_Off()		LedBit1_SetVal()
//#define LED1_Neg()		LedBit1_NegVal()
//#define LED1_Get()		LedBit1_GetVal()
//#define LED1_Put(val)	LedBit1_PutVal(val)
//#define LED1_Init()
//#define LED1_Deinit()

#if PL_NOF_LEDS >= 1
#include "LedBit1.h"

#define LED1_On()		LedBit1_ClrVal()
#define LED1_Off()		LedBit1_SetVal()
#define LED1_Neg()		LedBit1_NegVal()
#define LED1_Get()		LedBit1_GetVal()
#define LED1_Put(val)	LedBit1_PutVal(val)
#define LED1_Init()
#define LED1_Deinit()

#else

#define LED1_On()
#define LED1_Off()
#define LED1_Neg()
#define LED1_Get()		0
#define LED1_Put(val)
#define LED1_Init()
#define LED1_Deinit()

#endif

#if PL_NOF_LEDS >=2
#include "LedBit2.h"

#define LED2_On()		LedBit2_ClrVal()
#define LED2_Off()		LedBit2_SetVal()
#define LED2_Neg()		LedBit2_NegVal()
#define LED2_Get()		LedBit2_GetVal()
#define LED2_Put(val)	LedBit2_PutVal(val)
#define LED2_Init()
#define LED2_Deinit()

#else

#define LED2_On()
#define LED2_Off()
#define LED2_Neg()
#define LED2_Get()		0
#define LED2_Put(val)
#define LED2_Init()
#define LED2_Deinit()

#endif

#if PL_NOF_LEDS >=3
#include "LedBit3.h"

#define LED3_On()		LedBit3_ClrVal()
#define LED3_Off()		LedBit3_SetVal()
#define LED3_Neg()		LedBit3_NegVal()
#define LED3_Get()		LedBit3_GetVal()
#define LED3_Put(val)	LedBit3_PutVal(val)
#define LED3_Init()
#define LED3_Deinit()

#else

#define LED3_On()
#define LED3_Off()
#define LED3_Neg()
#define LED3_Get()		0
#define LED3_Put(val)
#define LED3_Init()
#define LED3_Deinit()

#endif


//Function declaration

void LED_Test(void);

void LED_Init(void);

void LED_Deinit(void);


#endif /* LED_H_ */
