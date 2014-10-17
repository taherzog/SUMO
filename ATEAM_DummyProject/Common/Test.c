/*
 * Test.c
 *
 *  Created on: 17.10.2014
 *      Author: pherzog
 */

#include "Trigger.h"
#include "LED.h"
#include "Buzzer.h"
#include "Test.h"


/*
 * \brief this is a test function for the Trigger Option
 */
void TEST_onButton(void)
{
	uint8_t err;
	err = BUZ_Beep(500,1000);
}
