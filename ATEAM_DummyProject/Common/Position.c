/*
 * Position.c
 *
 *  Created on: 14.11.2014
 *      Author: pherzog
 */

#include "Position.h"

#if PL_HAS_MOTOR_QUAD
#include "Q4CLeft.h"
#include "Q4CRight.h"
#include "FRTOS1.h"


static portTASK_FUNCTION(PosTask, pvParameters) {
  (void)pvParameters; /* not used */
  for(;;) {
	  Q4CLeft_Sample();
	  Q4CRight_Sample();
	  FRTOS1_vTaskDelay(1/portTICK_RATE_MS);
  }
}

void POS_Deinit(void)
{

}

void POS_Init(void)
{
	  /*! \todo You might need to adjust priority or other task settings */
	  if (FRTOS1_xTaskCreate(PosTask, "Position", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
	    for(;;){} /* error */
	  }
}






#endif /*PL_HAS_MOTOR_QUAD*/


