/*
 * Platform.h
 *
 *  Created on: 25.09.2014
 *      Author: reto
 */

#ifndef PLATFORM_H_
#define PLATFORM_H_

#include "PE_Types.h"		//Necessary if we want to use types as "bool"
#include "PE_Error.h"		//List of global Error Constants
#include <stddef.h>			//If we want to use NULL

/* List of supported platforms. The PL_BOARD_IS_xxx is defined in the compiler command line settings.  */
#define PL_IS_FRDM   (defined(PL_BOARD_IS_FRDM))
  /*!< Macro is defined through compiler option for the FRDM board */
#define PL_IS_ROBO  (defined(PL_BOARD_IS_ROBO))
  /*!< Macro is defined through compiler option for the Robot board */

#define PL_HAS_LED 					(1) 	//0 = no LED's on platform, 1 = LED's on Platform
#define PL_HAS_EVENTS				(1) 	//Enable Events on Platform
#define PL_HAS_TIMER				(1)		//Board has Timers
#define PL_HAS_KEYS					(1)		//Board has Keys
#define PL_HAS_KBI					(1)		//Key button support
#define PL_HAS_RESET_KEY			(1 && PL_IS_FRDM && PL_HAS_KEYS)		// Use Reset Button on Board
#define PL_HAS_JOYSTICK				(1 && PL_IS_FRDM && PL_HAS_KEYS)		// Joystick Shield is attached
#define PL_HAS_DEBOUNCE				(1 && PL_HAS_KEYS)
#define PL_HAS_TRIGGER				(1 && PL_HAS_TIMER)
#define PL_HAS_BUZZER				(1 && PL_HAS_TRIGGER && PL_IS_ROBO)
#define PL_HAS_RTOS					(1)		//Has a RTOS
#define PL_HAS_SHELL				(1)		//Has a Shell
#define PL_HAS_BLUETOOTH			(1 && PL_IS_ROBO)		//Has Bluetooth
#define PL_HAS_USB_CDC				(1)		//Has CDC - communications device class
#define PL_HAS_SHELL_QUEUE			(1)		//Use a queue to send datas over the shell resource
#define PL_HAS_SEMAPHORE			(1)		//Use Semaphores on the platformw
#define PL_HAS_LINE_SENSOR			(1)		//Has a Line-Sensor
#define PL_HAS_MOTOR				(1)		//Has a Motor
#define PL_HAS_QUAD_CALIBRATION		(0)		//Quad Calibration
#define PL_HAS_MCP4728				(1)		//Has a Motor controller
#define PL_IS_INTRO_ZUMO_K22_V2		(1)		//Uses the I2C Adresse 0x61 instead of 0x60
#define PL_HAS_MOTOR_QUAD			(1)		//Use Counters for the Quadrature Encoders
#define PL_HAS_MOTOR_TACHO			(1)		//Use a Tacho to measure the Speed
#define PL_HAS_PID					(1)		//Use the PID Controller
#define PL_HAS_DRIVE				(1)		//Use the Drive Component

/* additional hardware configuration */

/* if keys are using interrupts or are polled */
#if PL_IS_FRDM
  #define PL_KEY_POLLED_KEY1    (0)
  #define PL_KEY_POLLED_KEY2    (0)
  #define PL_KEY_POLLED_KEY3    (0)
  #define PL_KEY_POLLED_KEY4    (0)
  #define PL_KEY_POLLED_KEY5    (1)
  #define PL_KEY_POLLED_KEY6    (1)
  #define PL_KEY_POLLED_KEY7    (0)
#elif PL_IS_ROBO
  #define PL_KEY_POLLED_KEY1    (0)
#endif


#if PL_IS_FRDM
  #if PL_HAS_JOYSTICK
    #define PL_NOF_LEDS       (2)
      /*!< FRDM board has 2 LEDs (red is used by joystick shield) */
    #define PL_NOF_KEYS       (7)
       /*!< FRDM board has no keys without joystick shield */
  #else
    #define PL_NOF_LEDS       (3)
       /*!< FRDM board has up to 3 LEDs (RGB) */
#if PL_HAS_RESET_KEY
    #define PL_NOF_KEYS       (1)
       /*!< FRDM board with using the reset button */
#else
    #define PL_NOF_KEYS       (0)
       /*!< FRDM board has no keys without joystick shield */
#endif
  #endif
#elif PL_IS_ROBO
  #define PL_NOF_LEDS       (1)
     /*!< We have up to 2 LED's on the robo board */
  #define PL_NOF_KEYS       (1)
     /*!< We have up to 1 push button */
#else
  #error "unknown configuration?"
#endif

//Initalize Platform
void PL_Init(void);

//Deinitialize Platform
void PL_Deinit(void);

#endif /* PLATFORM_H_ */
