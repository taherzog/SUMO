/*
 * Remote.c
 *
 *  Created on: 28.11.2014
 *      Author: pherzog
 */

#include "Remote.h"
#include "FRTOS1.h"
#include "Accel.h"
#include "RApp.h"
//#include "AD1.h"
#include "Drive.h"

static portTASK_FUNCTION(RemoteTask, pvParameters) {
	(void) pvParameters; /* parameter not used */
	uint8_t x;
	uint8_t y;
	uint8_t z;
	Accel_Values acc_values;
	uint8_t speedR;
	uint8_t speedL;

	int8_t ADC_X;


	for (;;) {
		ACCEL_GetValues(&acc_values.x, &acc_values.y, &acc_values.z);

		//Normalize the values to
		x =  (uint8_t)(acc_values.x / 10 + 128);
		y =  (uint8_t)(acc_values.y / 10 + 128);

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


		RAPP_SendPayloadDataBlock(&speedR, sizeof(speedR), RAPP_MSG_TYPE_SPEED_R, 255, RPHY_PACKET_FLAGS_NONE);
		FRTOS1_vTaskDelay(50/portTICK_RATE_MS);
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

