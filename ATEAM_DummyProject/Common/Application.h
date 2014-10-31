/*
 * Application.h
 *
 *  Created on: 15.10.2014
 *      Author: pherzog
 */
#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "Platform.h"

#if PL_HAS_LED
  #include "LED.h"
#endif
#if PL_HAS_EVENTS
  #include "Event.h"
#endif

#if PL_HAS_KEYS
  #include "Keys.h"
#endif
#if PL_HAS_BUZZER
	#include "Buzzer.h"
#endif
#if PL_HAS_RTOS
	#include "RTOS.h"
#endif


/*
 * \brief Here start the main application.
 */
void APP_Start(void);


#endif /* APPLICATION_H_ */
