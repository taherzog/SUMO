/*
 * Remote.h
 *
 *  Created on: 28.11.2014
 *      Author: pherzog
 */
#ifndef REMOTE_H_
#define REMOTE_H_
#include "Platform.h"
#if PL_HAS_RADIO


//Send Messages
#if PL_IS_FRDM

// Initialize the Remote Controller
void RE_Init(void);

void RE_Deinit(void);


#endif /* PL_IS_FRDM */
#endif /* PL_HAS_RADIO */
#endif /* REMOTE_H_ */
