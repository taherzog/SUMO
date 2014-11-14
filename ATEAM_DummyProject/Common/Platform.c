/*
 * Platform.c
 *
 *  Created on: 25.09.2014
 *      Author: reto
 */

#include "Platform.h"

#if PL_HAS_LED
  #include "LED.h"
#endif
#if PL_HAS_EVENTS
  #include "Event.h"
#endif
#if PL_HAS_TIMER
  #include "Timer.h"
#endif
#if PL_HAS_KEYS
  #include "Keys.h"
#endif
#if PL_HAS_MEALY
  #include "Mealy.h"
#endif
#if PL_HAS_TRIGGER
  #include "Trigger.h"
#endif
#if PL_HAS_BUZZER
  #include "Buzzer.h"
#endif
#if PL_HAS_DEBOUNCE
  #include "Debounce.h"
  #include "KeyDebounce.h"
#endif
#if PL_HAS_RTOS
  #include "RTOS.h"
#endif
#if PL_HAS_SHELL
#include "Shell.h"
#endif
#if PL_HAS_BLUETOOTH
//Nothing to Include for Bluetooth
#endif
#if PL_HAS_SHELL_QUEUE
	#include "ShellQueue.h"
#endif
#if PL_HAS_SEMAPHORE
	#include "Sem.h"
#endif
#if PL_HAS_LINE_SENSOR
	#include "Reflectance.h"
#endif
#if PL_HAS_MOTOR
	#include "Motor.h"
#endif

void PL_Init(void){
#if PL_HAS_LED
  LED_Init();
#endif
#if PL_HAS_TIMER
  TMR_Init();
#endif
#if PL_HAS_EVENTS
  EVNT_Init();
#endif
#if PL_HAS_KEYS
  KEY_Init();
#endif
#if PL_HAS_MEALY
  MEALY_Init();
#endif
#if PL_HAS_TRIGGER
  TRG_Init();
#endif
#if PL_HAS_BUZZER
  BUZ_Init();
#endif
#if PL_HAS_DEBOUNCE
  DBNC_Init();
  KEYDBNC_Init();
#endif
#if PL_HAS_RTOS
  RTOS_Init();
#endif
#if PL_HAS_SHELL
  SHELL_Init();
#endif
#if PL_HAS_BLUETOOTH
  BT1_Init();
#endif
#if PL_HAS_SHELL_QUEUE
	SQUEUE_Init();
#endif
#if PL_HAS_SEMAPHORE
	SEM_Init();
#endif
#if PL_HAS_LINE_SENSOR
	REF_Init();
#endif
#if PL_HAS_MOTOR
	MOT_Init();
#endif
}

void PL_Deinit(void){
#if PL_HAS_RTOS
  RTOS_Deinit();
#endif
#if PL_HAS_BUZZER
  BUZ_Deinit();
#endif
#if PL_HAS_DEBOUNCE
  KEYDBNC_Deinit();
  DBNC_Deinit();
#endif
#if PL_HAS_TRIGGER
  TRG_Deinit();
#endif
#if PL_HAS_MEALY
  MEALY_Deinit();
#endif
#if PL_HAS_KEYS
  KEY_Deinit();
#endif
#if PL_HAS_EVENTS
  EVNT_Deinit();
#endif
#if PL_HAS_TIMER
  TMR_Deinit();
#endif
#if PL_HAS_LED
  LED_Deinit();
#endif
#if PL_HAS_RTOS
  RTOS_Deinit();
#endif
#if PL_HAS_SHELL
  SHELL_Deinit();
#endif
#if PL_HAS_BLUETOOTH
  BT1_Deinit();
#endif
#if PL_HAS_SHELL_QUEUE
  SQUEUE_Deinit();
#endif
#if PL_HAS_SEMAPHORE
	SEM_Deinit();
#endif
#if PL_HAS_LINE_SENSOR
	REF_Deinit();
#endif
#if PL_HAS_MOTOR
	MOT_Deinit();
#endif
}

