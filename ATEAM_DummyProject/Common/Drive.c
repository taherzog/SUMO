/**
 * \file
 * \brief Drive interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a simple 'drive' task which is responsible to move the robot around.
 */
#include "Platform.h"
#if PL_HAS_DRIVE
#include "Drive.h"
#include "FRTOS1.h"
#include "Pid.h"
#include "Tacho.h"
#include "Motor.h"
#if PL_HAS_RTOS_TRACE
	#include "RTOSTRC1.h"
#endif
#if PL_HAS_ULTRASONIC
	#include "Ultrasonic.h"
#endif

static volatile bool DRV_SpeedOn = FALSE;
static volatile bool DRV_PosOn = FALSE;
static volatile bool DRV_DisOn = FALSE;

static int32_t DRV_SpeedLeft, DRV_SpeedRight;
static int32_t DRV_PosLeft, DRV_PosRight;
static int32_t DRV_Dis;

void DRV_EnableDisableSpeed(bool enable) {
	DRV_SpeedOn = enable;
}

void DRV_EnableDisablePosition(bool enable) {
	DRV_PosOn = enable;
}

void DRV_EnableDisableDistance(bool enable) {
	DRV_DisOn = enable;
}

void DRV_SetSpeed(int32_t left, int32_t right) {
	DRV_SpeedLeft = left;
	DRV_SpeedRight = right;
}

void DRV_SetPosition(int32_t left, int32_t right) {
	DRV_PosLeft = left;
	DRV_PosRight = right;
}

void DRV_SetDistance(int32_t distance) {
	DRV_Dis = distance;
}

static portTASK_FUNCTION(DriveTask, pvParameters) {
	(void) pvParameters; /* parameter not used */
	bool prevSpeedOn;
	bool prevPositionOn;
	bool prevDistanceOn;
	//traceLabel usrEvent;

	prevSpeedOn = DRV_SpeedOn;
	prevPositionOn = DRV_PosOn;
	prevDistanceOn = DRV_Dis;

#if PL_HAS_RTOS_TRACE
	//usrEvent = xTraceOpenLabel("drive");
#endif
	for (;;) {
#if PL_HAS_RTOS_TRACE
		//RTOSTRC1_vTraceUserEvent(usrEvent);
#endif
		/*! \todo extend this for your own needs and with a position PID */
		TACHO_CalcSpeed();

		if (prevSpeedOn && !DRV_SpeedOn) { /* turned off */
			MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
			MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
			PID_Start(); /* reset values */
		} else if (DRV_SpeedOn) {
			PID_Speed(TACHO_GetSpeed(TRUE), DRV_SpeedLeft, TRUE); /* left */
			PID_Speed(TACHO_GetSpeed(FALSE), DRV_SpeedRight, FALSE); /* right */
		}
		prevSpeedOn = DRV_SpeedOn;

		if (prevPositionOn && !DRV_PosOn) { //Position Controller turned off
			MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
			MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
			PID_Start(); // Reset the Values
		} else if (DRV_PosOn) {
			PID_Pos(Q4CLeft_GetPos(), DRV_PosLeft, TRUE);
			PID_Pos(Q4CRight_GetPos(), DRV_PosRight, FALSE);
		}
		prevPositionOn = DRV_PosOn;

		if (prevDistanceOn && !DRV_DisOn) { //Position Controller turned off
					MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_LEFT), 0);
					MOT_SetSpeedPercent(MOT_GetMotorHandle(MOT_MOTOR_RIGHT), 0);
					PID_Start(); // Reset the Values
				} else if (DRV_DisOn) {

					PID_Dis(US_GetLastCentimeterValue(), DRV_Dis);
				}
				prevDistanceOn = DRV_Dis;

		FRTOS1_vTaskDelay(2/portTICK_RATE_MS);
	} /* for */
}

#if PL_HAS_SHELL
static void DRV_PrintStatus(const CLS1_StdIOType *io) {
	uint8_t buf[32];

	CLS1_SendStatusStr((unsigned char*) "drive", (unsigned char*) "\r\n",io->stdOut);
	CLS1_SendStatusStr((unsigned char*) "  speed",DRV_SpeedOn ? (unsigned char*) "on\r\n" : (unsigned char*) "off\r\n", io->stdOut);
	buf[0] = '\0';
	UTIL1_strcatNum32s(buf, sizeof(buf), DRV_SpeedLeft);
	UTIL1_strcat(buf, sizeof(buf), (unsigned char*) "\r\n");
	CLS1_SendStatusStr((unsigned char*) "  speed L", buf, io->stdOut);
	buf[0] = '\0';
	UTIL1_strcatNum32s(buf, sizeof(buf), DRV_SpeedRight);
	UTIL1_strcat(buf, sizeof(buf), (unsigned char*) "\r\n");
	CLS1_SendStatusStr((unsigned char*) "  speed R", buf, io->stdOut);
	buf[0] = '\0';

	CLS1_SendStatusStr((unsigned char*) "  position", DRV_PosOn ? (unsigned char*) "on\r\n" : (unsigned char*) "off\r\n", io->stdOut);
	UTIL1_strcatNum32s(buf, sizeof(buf), DRV_PosLeft);
	UTIL1_strcat(buf, sizeof(buf), (unsigned char*) "\r\n");
	CLS1_SendStatusStr((unsigned char*) "  position L", buf, io->stdOut);
	buf[0] = '\0';
	UTIL1_strcatNum32s(buf, sizeof(buf), DRV_PosRight);
	UTIL1_strcat(buf, sizeof(buf), (unsigned char*) "\r\n");
	CLS1_SendStatusStr((unsigned char*) "  position R", buf, io->stdOut);
	buf[0] = '\0';

	CLS1_SendStatusStr((unsigned char*) "  distance", DRV_DisOn ? (unsigned char*) "on\r\n" : (unsigned char*) "off\r\n", io->stdOut);
	UTIL1_strcatNum32s(buf, sizeof(buf), DRV_Dis);
	UTIL1_strcat(buf, sizeof(buf), (unsigned char*) "\r\n");
	CLS1_SendStatusStr((unsigned char*) "  distance", buf, io->stdOut);
	buf[0] = '\0';
}

static void DRV_PrintHelp(const CLS1_StdIOType *io) {
	CLS1_SendHelpStr((unsigned char*) "drive",
			(unsigned char*) "Group of drive commands\r\n", io->stdOut);
	CLS1_SendHelpStr((unsigned char*) "  help|status",
			(unsigned char*) "Shows help or status\r\n", io->stdOut);
	CLS1_SendHelpStr((unsigned char*) "  speed (on|off)",
			(unsigned char*) "Turns speed pid on or ff\r\n", io->stdOut);
	CLS1_SendHelpStr((unsigned char*) "  speed (L|R) <value>",
			(unsigned char*) "Sets speed value\r\n", io->stdOut);
	CLS1_SendHelpStr((unsigned char*) "  position (on|off)",
			(unsigned char*) "Turns position pid on or ff\r\n", io->stdOut);
	CLS1_SendHelpStr((unsigned char*) "  position (L|R) <value>",
			(unsigned char*) "Sets position value\r\n", io->stdOut);
	CLS1_SendHelpStr((unsigned char*) "  distance (on|off)",
				(unsigned char*) "Regulate the distance on or ff\r\n", io->stdOut);
	CLS1_SendHelpStr((unsigned char*) "  distance LR <value>",
				(unsigned char*) "Sets distance from ultrasonic in cm value\r\n", io->stdOut);

}

uint8_t DRV_ParseCommand(const unsigned char *cmd, bool *handled,
		const CLS1_StdIOType *io) {
	uint8_t res = ERR_OK;
	const uint8_t *p;
	int32_t val32;

	if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_HELP) == 0
			|| UTIL1_strcmp((char*)cmd, (char*)"drive help") == 0) {
		DRV_PrintHelp(io);
		*handled = TRUE;
	} else if (UTIL1_strcmp((char*)cmd, (char*)CLS1_CMD_STATUS) == 0
			|| UTIL1_strcmp((char*)cmd, (char*)"drive status") == 0) {
		DRV_PrintStatus(io);
		*handled = TRUE;
	} else if (UTIL1_strncmp((char* )cmd, (char* )"drive speed L",
			sizeof("drive speed L") - 1) == 0) {
		p = cmd + sizeof("drive speed L");
		if (UTIL1_ScanDecimal32sNumber(&p, &val32) == ERR_OK) {
			DRV_SpeedLeft = val32;
			*handled = TRUE;
		} else {
			res = ERR_FAILED;
		}
	} else if (UTIL1_strncmp((char* )cmd, (char* )"drive speed R",
			sizeof("drive speed R") - 1) == 0) {
		p = cmd + sizeof("drive speed R");
		if (UTIL1_ScanDecimal32sNumber(&p, &val32) == ERR_OK) {
			DRV_SpeedRight = val32;
			*handled = TRUE;
		} else {
			res = ERR_FAILED;
		}
	} else if (UTIL1_strncmp((char* )cmd, (char* )"drive position L",
			sizeof("drive position L") - 1) == 0) {
		p = cmd + sizeof("drive position L");
		if (UTIL1_ScanDecimal32sNumber(&p, &val32) == ERR_OK) {
			DRV_PosLeft = val32;
			*handled = TRUE;
		} else {
			res = ERR_FAILED;
		}
	} else if (UTIL1_strncmp((char* )cmd, (char* )"drive position R",
			sizeof("drive position R") - 1) == 0) {
		p = cmd + sizeof("drive position R");
		if (UTIL1_ScanDecimal32sNumber(&p, &val32) == ERR_OK) {
			DRV_PosRight = val32;
			*handled = TRUE;
		} else {
			res = ERR_FAILED;
		}
	} else if (UTIL1_strncmp((char* )cmd, (char* )"drive distance LR",
				sizeof("drive distance LR") - 1) == 0) {
			p = cmd + sizeof("drive distance LR");
			if (UTIL1_ScanDecimal32sNumber(&p, &val32) == ERR_OK) {
				DRV_Dis = val32;
				*handled = TRUE;
			} else {
				res = ERR_FAILED;
			}
	} else if (UTIL1_strcmp((char*)cmd, (char*)"drive speed on") == 0) {
		DRV_EnableDisableSpeed(TRUE);
		DRV_EnableDisablePosition(FALSE);
		*handled = TRUE;
	} else if (UTIL1_strcmp((char*)cmd, (char*)"drive speed off") == 0) {
		DRV_EnableDisableSpeed(FALSE);
		DRV_EnableDisablePosition(FALSE);
		*handled = TRUE;
	} else if (UTIL1_strcmp((char*)cmd, (char*)"drive position on") == 0) {
		DRV_EnableDisablePosition(TRUE);
		DRV_EnableDisableSpeed(FALSE);
		*handled = TRUE;
	} else if (UTIL1_strcmp((char*)cmd, (char*)"drive position off") == 0) {
		DRV_EnableDisablePosition(FALSE);
		DRV_EnableDisableSpeed(FALSE);
		*handled = TRUE;
	} else if (UTIL1_strcmp((char*)cmd, (char*)"drive distance on") == 0) {
		DRV_EnableDisableDistance(TRUE);
		*handled = TRUE;
	} else if (UTIL1_strcmp((char*)cmd, (char*)"drive distance off") == 0) {
		DRV_EnableDisableDistance(FALSE);
		*handled = TRUE;
	}

	return res;
}
#endif /* PL_HAS_SHELL */

void DRV_Deinit(void) {
	/* nothing needed */
}

void DRV_Init(void) {
	DRV_EnableDisableSpeed(FALSE);
	DRV_EnableDisablePosition(FALSE);
	DRV_SpeedLeft = 0;
	DRV_SpeedRight = 0;
	DRV_PosLeft = 0;
	DRV_PosRight = 0;

	if (FRTOS1_xTaskCreate(
			DriveTask, /* pointer to the task */
			"Drive", /* task name for kernel awareness debugging */
			configMINIMAL_STACK_SIZE, /* task stack size */
			(void*)NULL, /* optional task startup argument */
			tskIDLE_PRIORITY+1, /* initial priority */
			(xTaskHandle*)NULL /* optional task handle to create */
	) != pdPASS) {
		/*lint -e527 */
		for (;;) {
		} /* error! probably out of memory */
		/*lint +e527 */
	}
}

#endif /* PL_HAS_DRIVE */
