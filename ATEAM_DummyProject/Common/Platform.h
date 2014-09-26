/*
 * Platform.h
 *
 *  Created on: 25.09.2014
 *      Author: reto
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_


#ifdef PL_BOARD_IS_FRDM
#define PL_NOF_LEDS 	(3)
#elif defined(PL_BOARD_IS_ROBO)
#define PL_NOF_LEDS 	(2)

#else
	#error „Unknown board?“
#endif

#define PL_HAS_LED (1) //0 = no LED's on platform, 1 = LED's on Platform





#endif /* PLATFORM_H_ */
