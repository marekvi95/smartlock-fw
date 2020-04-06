/*
 * user.h
 *
 *  Created on: Apr 6, 2020
 *      Author: nxf46245
 */

#ifndef USER_H_
#define USER_H_

#define USERS 2
#define NAME_SIZE 10
#define UID_SIZE 4
#define KEY_SIZE 16

uint8_t getAuth(unsigned char* uid, unsigned char* authKey, char * name);

#endif /* USER_H_ */
