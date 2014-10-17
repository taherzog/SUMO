/*
 * Test.c
 *
 *  Created on: 17.10.2014
 *      Author: pherzog
 */

#include "Trigger.h"
#include "LED.h"


/*
 * \brief this is a test function for the Trigger Option
 */
void TEST_onTrigger(void)
{
	uint8_t err;
	LED1_Neg();
	err = TRG_SetTrigger(TRG_LED_BLINK, (TRG_TriggerTime)100, (TRG_Callback)TEST_onTrigger, NULL);

}
