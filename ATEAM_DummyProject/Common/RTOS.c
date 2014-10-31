/**
 * \file
 * \brief Real Time Operating System (RTOS) main program.
 * \author Erich Styger, erich.styger@hslu.ch
 */

#include "Platform.h"
#if PL_HAS_RTOS
#include "RTOS.h"
#include "FRTOS1.h"
#include "Application.h"
#include "LED.h"
#include "Event.h"
#include "CLS1.h"
#include "Keys.h"


static portTASK_FUNCTION(HeartBeat, pvParameters) {
  for(;;) {
    LED1_Neg();
    vTaskDelay(500/portTICK_RATE_MS);
  }
}


void RTOS_Run(void) {
  FRTOS1_vTaskStartScheduler();
}

void RTOS_Init(void) {
  /*! \todo Add tasks here */
  if (FRTOS1_xTaskCreate(HeartBeat, (signed portCHAR *)"HeartBeat", configMINIMAL_STACK_SIZE, NULL, 1, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}

void RTOS_Deinit(void) {
}

#endif /* PL_HAS_RTOS */
