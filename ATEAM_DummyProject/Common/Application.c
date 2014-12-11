/*
 * Application.c
 *
 *  Created on: 15.10.2014
 *      Author: pherzog
 */

#include "Platform.h"
#include "Application.h"
#include "CLS1.h"
#if PL_HAS_RTOS
	#include "FRTOS1.h"
#endif
#if PL_HAS_BUZZER
	#include "Buzzer.h"
#endif
#if PL_HAS_EVENTS
	#include "Event.h"
#endif
#if PL_HAS_ACCEL
	#include "Accel.h"
#endif
#if PL_HAS_FIGHT_MODE
	#include "Fight.h"
#endif

void APP_DebugPrint(unsigned char *str) {
#if PL_HAS_SHELL
  CLS1_SendStr(str, CLS1_GetStdio()->stdOut);
#endif
}


static uint8_t lastKeyPressed;
static uint16_t freq = 500;

/*! \brief Handles the Events */
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
      //EVNT_SetEvent(EVNT_REF_START_STOP_CALIBRATION);
#if PL_HAS_FIGHT_MODE
      FIGHT_SetState(FIGHT_STATE_COUNTDOWN);
      break;
#endif

#if PL_HAS_LINE_SENSOR
    case EVNT_REF_START_STOP_CALIBRATION: //Create event again, because the event is handled in the "Reflectance.c" directly.
    	if(!EVNT_EventIsSet(EVNT_REF_START_STOP_CALIBRATION))
    	{
    		EVNT_SetEvent(EVNT_REF_START_STOP_CALIBRATION);
    	}

      break;
#endif

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


/*
 *
 */

static void APP_Loop(void) {

	// Not needed anymore because RTOS is used.
	/*
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
  }*/
}

/*
 * Task for Handling the Events and the KeyScan.
 */
static void APPTask(void *pvParameters) {
  (void)pvParameters; /* not used */

#if PL_HAS_ACCEL //Initialize Accelometer in a task because it used interrupts, which are disabled when the RTOS is not running.
  ACCEL_LowLevelInit();
#endif

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

/*! \brief Function for starting the Application. Inits and Start the RTOS */
void APP_Start(void) {
  PL_Init(); 				/* platform initialization */

  EVNT_SetEvent(EVNT_INIT); /* set initial event */

  //Create application Task
  if (FRTOS1_xTaskCreate(APPTask, (signed portCHAR *)"APP_Task", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    for(;;){} /* error */
  }

  RTOS_Run();
}
