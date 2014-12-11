/*
 * Remote.c
 *
 *  Created on: 28.11.2014
 *      Author: pherzog
 */

#include "Platform.h"

#if PL_HAS_REMOTE
#include "Remote.h"
#include "FRTOS1.h"
#include "Accel.h"
#include "RApp.h"
#include "Drive.h"
#if PL_HAS_RE_JOY
#include "AD1.h"
#endif


static portTASK_FUNCTION(RemoteTask, pvParameters) {
	(void) pvParameters; /* parameter not used */
	uint8_t x;
	uint8_t y;
	uint8_t z;
	Accel_Values acc_values;
	uint8_t speedR;
	uint8_t speedL;

	uint16_t ADC_X;
	uint16_t ADC_Y;

#if PL_HAS_RE_JOY

#endif

	for (;;) {

#if PL_HAS_RE_ACCEL
		ACCEL_GetValues(&acc_values.x, &acc_values.y, &acc_values.z);

		//Normalize the values to
		x =  (uint8_t)(acc_values.x / 10 + 128);
		y =  (uint8_t)(acc_values.y / 10 + 128);

		//Calculate offset for
		if (y > 128)
		{
			speedR = y - (x-128)/2;
			speedL = y + (x-128)/2;
		}
		else
		{
			speedR = y + (x-128)/2;
			speedL = y - (x-128)/2;
		}
#endif /* PL_HAS_ACCEL*/

#if PL_HAS_RE_JOY
		AD1_Measure(TRUE);
		AD1_GetChanValue16(0,&ADC_X);
		AD1_GetChanValue16(1,&ADC_Y);

		//Normalize Values, so 32000 is about 128, which means no Speed.
		ADC_X = ADC_X / 255;
		ADC_Y = ADC_Y / 255;

		//Y-Axis is the speed for both

		speedR = ADC_Y - (ADC_X-128)/2;
		speedL = ADC_Y + (ADC_X-128)/2;

#endif



		RAPP_SendPayloadDataBlock(&speedR, sizeof(speedR), RAPP_MSG_TYPE_SPEED_R, 255, RPHY_PACKET_FLAGS_NONE);
		RAPP_SendPayloadDataBlock(&speedL, sizeof(speedL), RAPP_MSG_TYPE_SPEED_L, 255, RPHY_PACKET_FLAGS_NONE);
		//AD1_Measure(TRUE);
		//AD1_GetChanValue8(0,&ADC_X);

		FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
	} /* for */
}


void RE_Init(void) {

  if (FRTOS1_xTaskCreate(
  			RemoteTask, /* pointer to the task */
  			"RemoteTask", /* task name for kernel awareness debugging */
  			configMINIMAL_STACK_SIZE, /* task stack size */
  			(void*)NULL, /* optional task startup argument */
  			tskIDLE_PRIORITY, /* initial priority */
  			(xTaskHandle*)NULL /* optional task handle to create */
  	) != pdPASS) {
  		/*lint -e527 */
  		for (;;) {
  		} /* error! probably out of memory */
  		/*lint +e527 */
  	}
}

void RE_Deinit(void) {

}

#endif
