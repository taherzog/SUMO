/*
 * Fight.c
 *
 *  Created on: 05.12.2014
 *      Author: pherzog
 */

#include "Platform.h"

#if PL_HAS_FIGHT_MODE
#include "Fight.h"
#include "FRTOS1.h"
#include "Buzzer.h"
#include "BUZ1.h"
#include "Ultrasonic.h"
#include "Accel.h"



static volatile FightStateType fightState = FIGHT_STATE_IDLE;
int16_t distance;
static int16_t x,y,z;

static void FIGHT_StateMachine(void) {

switch(fightState)
{
	case FIGHT_STATE_IDLE:
		FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
	break;

	case FIGHT_STATE_COUNTDOWN:
		for(int i = 2; i < 50; i ++)
		{
			BUZ_Beep((i)*20,50);
			FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
		}
		FIGHT_SetState(FIGHT_STATE_RUN);
		DRV_SetSpeed(2000,2000);
		DRV_EnableDisableSpeed(TRUE);
		FRTOS1_vTaskDelay(500/portTICK_RATE_MS);
	break;

	case FIGHT_STATE_RUN:
		DRV_SetSpeed(-2000,2000);
		DRV_EnableDisableSpeed(TRUE);
		distance = US_GetLastCentimeterValue();
		if(distance < 60 && distance != 0)
		{
			FIGHT_SetState(FIGHT_STATE_BOOST);
		}
	break;

	case FIGHT_STATE_BOOST:
		DRV_SetSpeed(6000,6000);
		DRV_EnableDisableSpeed(TRUE);
		distance = US_GetLastCentimeterValue();
		if (distance > 50)
		{
			FIGHT_SetState(FIGHT_STATE_RUN);
		}

		break;

	case FIGHT_STATE_LINEDETECTED:
		DRV_EnableDisableSpeed(TRUE);
		DRV_SetSpeed(-4000,-4000);
		FRTOS1_vTaskDelay(500/portTICK_RATE_MS);
		DRV_SetSpeed(-4000,4000);
		FRTOS1_vTaskDelay(300/portTICK_RATE_MS);
		FIGHT_SetState(FIGHT_STATE_RUN);
		break;

	case FIGHT_STATE_UPSIDEDOWN:
		DRV_EnableDisableSpeed(FALSE);
		DRV_SetSpeed(0,0);
		if(z > 500)
		{
			FIGHT_SetState(FIGHT_STATE_RUN);
		}
		break;

}



}

void CheckAccel(void)
{
	ACCEL_GetValues(&x, &y, &z);
	if (z < -200)
	{
		FIGHT_SetState(FIGHT_STATE_UPSIDEDOWN);
	}
}

static portTASK_FUNCTION(FightTask, pvParameters) {
  (void)pvParameters; /* not used */
  BUZ_Beep(500,1000);
  FRTOS1_vTaskDelay(100/portTICK_RATE_MS);
  for(;;) {
    FIGHT_StateMachine();
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  }
}

static portTASK_FUNCTION(AccelTask, pvParameters) {
  (void)pvParameters; /* not used */
  for(;;) {
    CheckAccel();
    FRTOS1_vTaskDelay(500/portTICK_RATE_MS);
  }
}

static FightStateType FIGHT_GetState()
{
	return fightState;
}

void FIGHT_SetState(FightStateType fight)
{
	if(fightState != FIGHT_STATE_IDLE || fight == FIGHT_STATE_COUNTDOWN)
	{
		fightState = fight;
	}

}

void FIGHT_Init(void)
{
	fightState = FIGHT_STATE_IDLE;
  if (FRTOS1_xTaskCreate(FightTask, "Fight", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    for(;;){} /* error */
  }
  if (FRTOS1_xTaskCreate(AccelTask, "Accel", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
      for(;;){} /* error */
    }
}

void FIGHT_Deinit(void)
{
	//Nothing to do here
}

#endif /*PL_HAS_FIGHT_MODE*/
