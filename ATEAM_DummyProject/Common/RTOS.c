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

static uint8_t lastKeyPressed;

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

static portTASK_FUNCTION(HeartBeat, pvParameters) {
  for(;;) {
    LED2_Neg();
    vTaskDelay(5000/portTICK_RATE_MS);
  }
}

static portTASK_FUNCTION(APP_LOOP, pvParameters) {
  for(;;) {
    //LED1_Neg();
#if PL_HAS_EVENTS
    EVNT_HandleEvent(APP_EventHandler); // handle pending events
#endif

#if PL_HAS_KEYS
    KEY_Scan(); // scan keys
#endif
    vTaskDelay(100/portTICK_RATE_MS);
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

  if (FRTOS1_xTaskCreate(APP_LOOP, (signed portCHAR *)"APP_LOOP", configMINIMAL_STACK_SIZE, NULL, 1, NULL) != pdPASS) {
      for(;;){}
    }
}

void RTOS_Deinit(void) {
}

#endif /* PL_HAS_RTOS */
