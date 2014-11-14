/*
 * Position.h
 *
 *  Created on: 14.11.2014
 *      Author: pherzog
 */
#ifndef POSITION_H_
#define POSITION_H_

#include "Platform.h"

#if PL_HAS_MOTOR_QUAD

/*!
 * \brief Driver Deinitialization.
 */
void POS_Deinit(void);

/*!
 * \brief Driver Initialization.
 */
void POS_Init(void);

#endif /*PL_HAS_MOTOR_QUAD*/

#endif /* POSITION_H_ */
