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



static volatile FightStateType fightState = FIGHT_STATE_IDLE;
int16_t distance;

static void FIGHT_StateMachine(void) {

switch(fightState)
{
	case FIGHT_STATE_IDLE:
		FIGHT_SetState(FIGHT_STATE_COUNTDOWN);
	break;

	case FIGHT_STATE_COUNTDOWN:
		BUZ_Beep(2000,1000);
		FRTOS1_vTaskDelay(1000/portTICK_RATE_MS);
		FIGHT_SetState(FIGHT_STATE_RUN);

	break;

	case FIGHT_STATE_RUN:
		DRV_SetSpeed(-1500,2000);
		DRV_EnableDisableSpeed(TRUE);
		distance = US_GetCentimeter();
		if(distance < 30)
		{
			FIGHT_SetState(FIGHT_STATE_BOOST);
		}
	break;

	case FIGHT_STATE_BOOST:
		DRV_SetSpeed(3000,3000);
		DRV_EnableDisableSpeed(TRUE);
		if (US_GetCentimeter() > 30)
		{
			FIGHT_SetState(FIGHT_STATE_RUN);
		}
		break;

	case FIGHT_STATE_LINEDETECTED:
		DRV_EnableDisableSpeed(TRUE);
		DRV_SetSpeed(-4000,-1000);
		FRTOS1_vTaskDelay(500/portTICK_RATE_MS);
		FIGHT_SetState(FIGHT_STATE_RUN);
		break;

}

}


static portTASK_FUNCTION(FightTask, pvParameters) {
  (void)pvParameters; /* not used */
  for(;;) {
    FIGHT_StateMachine();
    FRTOS1_vTaskDelay(10/portTICK_RATE_MS);
  }
}

static FightStateType FIGHT_GetState()
{
	return fightState;
}

void FIGHT_SetState(FightStateType fight)
{
	fightState = fight;
}

void FIGHT_Init(void)
{
	fightState = FIGHT_STATE_IDLE;
  if (FRTOS1_xTaskCreate(FightTask, "Fight", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL) != pdPASS) {
    for(;;){} /* error */
  }
}

void FIGHT_Deinit(void)
{
	//Nothing to do here
}

#endif /*PL_HAS_FIGHT_MODE*/
