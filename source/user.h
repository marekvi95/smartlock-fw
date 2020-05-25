/*
 * user.h
 *
 *  Created on: Apr 6, 2020
 *      Author: Marek Vitula
 */

#ifndef USER_H_
#define USER_H_

void initDB();
void printDB();
uint8_t insertUser(const unsigned char * uid);
uint8_t deleteUser(const unsigned char * uid);
uint8_t getAuth(unsigned char* uid, unsigned char* authKey, unsigned char* mifareKey);
status_t initFlash();
void copyFlash();
status_t eraseFlash();
status_t writeFlash();

#endif /* USER_H_ */
