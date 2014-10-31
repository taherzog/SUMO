/*
 * Application.c
 *
 *  Created on: 15.10.2014
 *      Author: pherzog
 */

#include "Platform.h"
#include "Application.h"
#include "WAIT1.h"
#include "CLS1.h"
#include "FRTOS1.h"



static uint8_t lastKeyPressed;
static uint16_t freq = 500;

static void APP_EventHandler(EVNT_Handle event) {
	uint8_t err;
  switch(event) {
    case EVNT_INIT:
      LED1_On();
      vTaskDelay(50/portTICK_RATE_MS);
      LED1_Off();
      LED2_On();
      vTaskDelay(50/portTICK_RATE_MS);
      LED2_Off();
      LED3_On();
      vTaskDelay(50/portTICK_RATE_MS);
      LED3_Off();
      break;
    case EVENT_LED_HEARTBEAT:
      LED2_Neg();
      break;
    case EVNT_SW1_PRESSED:
      lastKeyPressed = 1;
      LED1_On();
      vTaskDelay(50/portTICK_RATE_MS);
      LED1_Off();
      CLS1_SendStr("SW1",CLS1_GetStdio()->stdOut);
      break;
#if PL_IS_FRDM
    case EVNT_SW2_PRESSED:
      lastKeyPressed = 2;
      LED1_On();
      vTaskDelay(50/portTICK_RATE_MS);
      LED1_Off();
      break;
    case EVNT_SW3_PRESSED:
      lastKeyPressed = 3;
      LED1_On();
      vTaskDelay(50/portTICK_RATE_MS);
      LED1_Off();
      break;
    case EVNT_SW4_PRESSED:
      lastKeyPressed = 4;
      LED1_On();
      vTaskDelay(50/portTICK_RATE_MS);
      LED1_Off();
      break;
    case EVNT_SW5_PRESSED:
      lastKeyPressed = 5;
      LED1_On();
      vTaskDelay(50/portTICK_RATE_MS);
      LED1_Off();
      break;
    case EVNT_SW6_PRESSED:
      lastKeyPressed = 6;
      LED1_On();
      vTaskDelay(50/portTICK_RATE_MS);
      LED1_Off();
      break;
    case EVNT_SW7_PRESSED:
      lastKeyPressed = 7;
      LED1_On();
      vTaskDelay(50/portTICK_RATE_MS);
      LED1_Off();
      break;
#endif
    default:
      break;
  }
}


static void APP_Loop(void) {

#if PL_HAS_KEYS
  KEY_EnableInterrupts();
#endif



  for(;;) {
	#if PL_HAS_EVENTS
    EVNT_HandleEvent(APP_EventHandler); // handle pending events
	#endif


#if PL_HAS_KEYS
    KEY_Scan(); // scan keys
#endif
    WAIT1_Waitms(100);
  }
}

static void APPTask(void *pvParameters) {
  (void)pvParameters; /* not used */

  for(;;) {
#if PL_HAS_EVENTS
    EVNT_HandleEvent(APP_EventHandler); /* handle pending events */
#endif
#if PL_HAS_KEYS && PL_NOF_KEYS>0
    KEY_Scan(); /* scan keys */
#endif

    FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
  }
}

void APP_Start(void) {
  PL_Init(); /* platform initialization */

  EVNT_SetEvent(EVNT_INIT); /* set initial event */


  //Create application Task
  if (FRTOS1_xTaskCreate(APPTask, (signed portCHAR *)"APP_Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    for(;;){} /* error */
  }

  RTOS_Run();

  //EVNT_SetEvent(EVNT_INIT); /* set initial event */

  //APP_Loop();

  /* just in case we leave the main application loop */
  //PL_Deinit();
}
