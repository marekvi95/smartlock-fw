/*
 * app_config.h
 *
 *  Created on: 7 May 2019
 *      Author: Marek Vitula
 */

#ifndef APP_CONFIG_H_
#define APP_CONFIG_H_

/* Set to 1 for the first time flash initialization
 *  DB of users will be initialized and saved to flash
 */
#define INIT_FLASH 1

/* Set to 1 if you want to use sleep modes  */
#define SLEEP_MODE 0

/* Select RCZ standard. Use:
 * - "sfNetStandardETSI" for RCZ1 or
 * - "sfNetStandardFCC_USA" for RCZ2 */
#define SF_STANDARD                 sfNetStandardETSI

/* Type of XTAL. Click modules (Innocomm SN10-1x modules) use 27.6MHz TCXO. */
#define SF_XTAL                     sfXtal276

/* Runtime of the motor while locking/unlocking in milliseconds. */
#define SF_MOTOR_RUNTIME_MS         1000

/* Sigfox message size in bytes
 * without added padding */
#define SF_MSG_SIZE 5

/* User database settings */
/* Number of users in DB */
#define USERS 32

/* Size of the Mifare authentication Key, 6 bytes for Mifare Classic */
#define MIFARE_SIZE 6

/* Size of the UID (NUID) NFC tag identification number, could be 4 or 7 bytes */
#define UID_SIZE 4

/* Authentication key (password) size */
#define KEY_SIZE 16

/* Block number where are the keys stored 
 * Sector number is block/4 */
#define BLK_NB_MFC 4

#endif /* APP_CONFIG_H_ */
