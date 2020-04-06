/*
 * user.c
 *
 *  Created on: Apr 6, 2020
 *      Author: nxf46245
 */
#include <string.h>
#include <stdint.h>
#include "user.h"

struct User {
	char name[NAME_SIZE];
	unsigned char authKey[KEY_SIZE];
	unsigned char uid[UID_SIZE];
};

struct User arr_user[USERS] = {
		{
				"Marek",
				{0x42, 0x54, 0x69, 0x63,
				0x69, 0x6e, 0x6f, 0x43,
				0x41, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00},
				{0x45, 0x75, 0x65, 0x2a},
		},
		{
				"Petr",
				{0x42, 0x54, 0x69, 0x63,
				0x69, 0x6e, 0x6f, 0x43,
				0x41, 0x00, 0x00, 0x00,
				0x00, 0x00, 0x00, 0x00},
				{0x45, 0x75, 0x65, 0x2b},
		},
};

uint8_t getAuth(unsigned char* uid, unsigned char* authKey, char * name)
{
	for(int i=0; i<USERS; i++)
	{
		if (memcmp(arr_user[i].uid, uid, UID_SIZE) == 0)
		{
            memcpy(name, arr_user[i].name, NAME_SIZE);
            memcpy(authKey, arr_user[i].authKey, KEY_SIZE);
			return 1;
		}
	}
	return 0;
}
