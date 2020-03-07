/*
 * app_config.h
 *
 *  Created on: 7 May 2019
 *      Author: nxf05489
 */

#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

/* Select RCZ standard. Use:
 * - "sfNetStandardETSI" for RCZ1 or
 * - "sfNetStandardFCC_USA" for RCZ2 */
#define SF_STANDARD                 sfNetStandardETSI

/* Type of XTAL. Click modules (Innocomm SN10-1x modules) use 27.6MHz TCXO. */
#define SF_XTAL                     sfXtal276

/* Runtime of the motor while locking/unlocking in milliseconds. */
#define SF_MOTOR_RUNTIME_MS         25

/* Duty cycle of H-Bridge PWM (0-100). */
#define SF_MOTOR_DUTY               90

#endif /* APP_CONFIG_H_ */
