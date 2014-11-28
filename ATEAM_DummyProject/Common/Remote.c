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
#include "AD1.h"
#include "Drive.h"

static portTASK_FUNCTION(RemoteTask, pvParameters) {
	(void) pvParameters; /* parameter not used */
	int16_t x;
	int16_t y;
	int16_t z;
	int8_t ADC_X;


	for (;;) {
		ACCEL_GetValues(&x, &y, &z);
		x =  x / 5;
		y =  y / 5;
		z =  z / 5;

		RAPP_SendPayloadDataBlock(&x, sizeof(x), RAPP_MSG_TYPE_ACCEL, 255, RPHY_PACKET_FLAGS_NONE);
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

