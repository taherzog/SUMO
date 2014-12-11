/*
 * Fight.h
 *
 *  Created on: 05.12.2014
 *      Author: pherzog
 */
#ifndef FIGHT_H_
#define FIGHT_H_

#include "Platform.h"

#if PL_HAS_FIGHT_MODE

typedef enum {
  FIGHT_STATE_IDLE,
  FIGHT_STATE_COUNTDOWN,
  FIGHT_STATE_RUN,
  FIGHT_STATE_BOOST,
  FIGHT_STATE_LINEDETECTED,
  FIGHT_STATE_UPSIDEDOWN
} FightStateType;

static void FIGHT_StateMachine(void);

/*!
 * \brief Driver Deinitialization.
 */
void FIGHT_Deinit(void);

/*!
 * \brief Driver Initialization.
 */
void FIGHT_Init(void);

void FIGHT_SetState(FightStateType fight);

static FightStateType FIGHT_GetState();

#endif /*PL_HAS_FIGHT_MODE*/

#endif /* FIGHT_H_ */
