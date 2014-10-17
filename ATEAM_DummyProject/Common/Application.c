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

#if PL_HAS_LED
  #include "LED.h"
#endif
#if PL_HAS_EVENTS
  #include "Event.h"
#endif
/*
#if PL_HAS_MEALY
  #include "Mealy.h"
#endif
*/
#if PL_HAS_KEYS
  #include "Keys.h"
#endif
#if PL_HAS_BUZZER
	#include "Buzzer.h"
#endif

#include "Test.h"

static uint8_t lastKeyPressed;

static void APP_EventHandler(EVNT_Handle event) {
	uint8_t err;
  //TestFunction();
  switch(event) {
    case EVNT_INIT:
      LED1_On();
      WAIT1_Waitms(50);
      LED1_Off();
      LED2_On();
      WAIT1_Waitms(50);
      LED2_Off();
      LED3_On();
      WAIT1_Waitms(50);
      LED3_Off();
      break;
    /*case EVENT_LED_HEARTBEAT:
      LED2_Neg();
      break;*/
    case EVNT_SW1_PRESSED:
      lastKeyPressed = 1;
      LED1_On();
      WAIT1_Waitms(50);
      LED1_Off();
      CLS1_SendStr("SW1 Pressed! \n\r",CLS1_GetStdio()->stdOut);
      err = BUZ_Beep(500,2);
      break;
    case EVNT_SW2_PRESSED:
      lastKeyPressed = 2;
      LED1_On();
      WAIT1_Waitms(50);
      LED1_Off();
      CLS1_SendStr("SW2 Pressed! \n\r",CLS1_GetStdio()->stdOut);
      break;
    case EVNT_SW3_PRESSED:
      lastKeyPressed = 3;
      LED1_On();
      WAIT1_Waitms(50);
      LED1_Off();
      CLS1_SendStr("SW3 Pressed! \n\r",CLS1_GetStdio()->stdOut);
      break;
    case EVNT_SW4_PRESSED:
      lastKeyPressed = 4;
      LED1_On();
      WAIT1_Waitms(50);
      LED1_Off();
      CLS1_SendStr("SW4 Pressed! \n\r",CLS1_GetStdio()->stdOut);
      break;
    case EVNT_SW5_PRESSED:
      lastKeyPressed = 5;
      LED1_On();
      WAIT1_Waitms(50);
      LED1_Off();
      CLS1_SendStr("SW5 Pressed! \n\r",CLS1_GetStdio()->stdOut);
      break;
    case EVNT_SW6_PRESSED:
      lastKeyPressed = 6;
      LED1_On();
      WAIT1_Waitms(50);
      LED1_Off();
      CLS1_SendStr("SW6 Pressed! \n\r",CLS1_GetStdio()->stdOut);
      break;
    case EVNT_SW7_PRESSED:
      lastKeyPressed = 7;
      LED1_On();
      WAIT1_Waitms(50);
      LED1_Off();
      CLS1_SendStr("SW7 Pressed! \n\r",CLS1_GetStdio()->stdOut);
      break;
    default:
      break;
  }
}


static void APP_Loop(void) {
  int i;
#if PL_HAS_KEYS
  //KEY_EnableInterrupts();
#endif

  for(;;) {
	#if PL_HAS_EVENTS
    EVNT_HandleEvent(APP_EventHandler); /* handle pending events */
	#endif

    /*
    LED1_On();
    WAIT1_Waitms(300);
    LED1_Off();
    LED2_On();
    WAIT1_Waitms(300);
    LED2_Off();
    LED3_On();
    WAIT1_Waitms(300);
    LED3_Off();
    */

#if PL_HAS_KEYS
    KEY_Scan(); // scan keys
#endif
    WAIT1_Waitms(100);
  }
}


void APP_Start(void) {
  PL_Init(); /* platform initialization */
  //TEST_Test();
  EVNT_SetEvent(EVNT_INIT); /* set initial event */

  TEST_onTrigger();

  APP_Loop();

  /* just in case we leave the main application loop */
  PL_Deinit();
}
