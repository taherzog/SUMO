/**
 * \file
 * \brief Drive interface.
 * \author Erich Styger, erich.styger@hslu.ch
 *
 * This module implements a simple 'drive' task which is responsible to move the robot around.
 */

#ifndef DRIVE_H_
#define DRIVE_H_

#include "Platform.h"
#if PL_HAS_DRIVE

#if PL_HAS_SHELL
#include "CLS1.h"
/*!
 * \brief Shell command line parser.
 * \param[in] cmd Pointer to command string
 * \param[out] handled If command is handled by the parser
 * \param[in] io Std I/O handler of shell
 */
uint8_t DRV_ParseCommand(const unsigned char *cmd, bool *handled, const CLS1_StdIOType *io);
#endif

/*!
 * \brief Enables or disbles the drive mode in SpeedMode.
 * \param enable TRUE to enable, FALSE otherwise.
 */
void DRV_EnableDisableSpeed(bool enable);

/*!
 * \brief Enables or disbles the drive mode in PositionMode.
 * \param enable TRUE to enable, FALSE otherwise.
 */
void DRV_EnableDisablePosition(bool enable);

/*!
 * \brief Enables or disbles the drive mode in DistanceMode.
 * \param enable TRUE to enable, FALSE otherwise.
 */
void DRV_EnableDisableDistance(bool enable);


/*!
 * \brief Sets the driving speed for left and right.
 * \param left Left wheel speed.
 * \param right Right wheel speed.
 */
void DRV_SetSpeed(int32_t left, int32_t right);

/*!
 * \brief Turn the Roboter with a angle
 * \param angle to be made (can be negative)
 */
void DRV_SetAngle(int32_t angle);

/*!
 * \brief Sets the position for left and right motor
 * \param left Left wheel position.
 * \param right Right wheel position.
 */
void DRV_SetPosition(int32_t left, int32_t right);

/*!
 * \brief Sets the distance
 * \param left Left wheel position.
 * \param right Right wheel position.
 */
void DRV_SetDistance(int32_t distance);

/*! \brief Driver initialization */
void DRV_Init(void);

/*! \brief Driver de-initialization */
void DRV_Deinit(void);

#endif /* PL_HAS_DRIVE */

#endif /* DRIVE_H_ */
