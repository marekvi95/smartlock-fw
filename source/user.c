/*
 * user.c
 *
 *  Created on: May 14, 2020
 *      Author: Marek Vitula
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "app_config.h"
#include "fsl_flash.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define SECTOR_INDEX_FROM_END 1U

#define print_buf(x,y,z)  {int loop; printf(x); for(loop=0;loop<z;loop++) printf("%.2x ", y[loop]); printf("\n");}

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Flash driver Structure */
static flash_config_t s_flashDriver;
/*! @brief Flash cache driver Structure */
static ftfx_cache_config_t s_cacheDriver;

static uint32_t destAdrss; /* Address of the target location */
static uint32_t pflashBlockBase  = 0;
static uint32_t pflashTotalSize  = 0;
static uint32_t pflashSectorSize = 0;

typedef struct {
	unsigned char mifareKey[MIFARE_SIZE];
	unsigned char authKey[KEY_SIZE];
	unsigned char uid[UID_SIZE];
} user_t;

static user_t arr_user[USERS];
static uint8_t i;
static user_t (*user_array_ptr)[];

static const unsigned char default_mifare[MIFARE_SIZE] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
static const unsigned char default_uid[UID_SIZE] = {0x00, 0x00, 0x00, 0x00};

static const unsigned char master_mifare[MIFARE_SIZE] = {0x02, 0x12, 0x09, 0x19, 0x75, 0x91};
static const unsigned char master_uid[UID_SIZE] = {0x45, 0x75, 0x65, 0x2a};
static const unsigned char master_key[KEY_SIZE] = {
		0x42, 0x54, 0x69, 0x63,
		0x69, 0x6e, 0x6f, 0x43,
		0x41, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00};

/** Array with pre-generated random keys (passwords) */
static const unsigned char default_keys[USERS][KEY_SIZE] = {
		{0x3e, 0x83, 0x7a, 0xee, 0x93, 0x14, 0xdf, 0xb, 0x12, 0xe, 0xd4, 0x12, 0x56, 0xcf, 0x9a, 0x51},
		{0x43, 0x58, 0x69, 0x4d, 0xe6, 0x97, 0x21, 0xbb, 0xd2, 0x78, 0x83, 0xf4, 0x98, 0xc3, 0xfa, 0xc9},
		{0xd9, 0xce, 0x18, 0x3a, 0x94, 0xf3, 0x25, 0xe5, 0xec, 0xfd, 0x2a, 0x70, 0xc5, 0xe8, 0x5d, 0x9f},
		{0xd3, 0x4, 0xec, 0x5a, 0xde, 0xc4, 0xb7, 0x36, 0xd, 0xa9, 0xc3, 0x69, 0x97, 0x53, 0x58, 0x14},
		{0x3e, 0x83, 0x7a, 0xee, 0x93, 0x14, 0xdf, 0xb, 0x12, 0xe, 0xd4, 0x12, 0x56, 0xcf, 0x9a, 0x51},
		{0x43, 0x58, 0x69, 0x4d, 0xe6, 0x97, 0x21, 0xbb, 0xd2, 0x78, 0x83, 0xf4, 0x98, 0xc3, 0xfa, 0xc9},
		{0xd9, 0xce, 0x18, 0x3a, 0x94, 0xf3, 0x25, 0xe5, 0xec, 0xfd, 0x2a, 0x70, 0xc5, 0xe8, 0x5d, 0x9f},
		{0xd3, 0x4, 0xec, 0x5a, 0xde, 0xc4, 0xb7, 0x36, 0xd, 0xa9, 0xc3, 0x69, 0x97, 0x53, 0x58, 0x14},
		{0x3e, 0x83, 0x7a, 0xee, 0x93, 0x14, 0xdf, 0xb, 0x12, 0xe, 0xd4, 0x12, 0x56, 0xcf, 0x9a, 0x51},
		{0x43, 0x58, 0x69, 0x4d, 0xe6, 0x97, 0x21, 0xbb, 0xd2, 0x78, 0x83, 0xf4, 0x98, 0xc3, 0xfa, 0xc9},
		{0xd9, 0xce, 0x18, 0x3a, 0x94, 0xf3, 0x25, 0xe5, 0xec, 0xfd, 0x2a, 0x70, 0xc5, 0xe8, 0x5d, 0x9f},
		{0xd3, 0x4, 0xec, 0x5a, 0xde, 0xc4, 0xb7, 0x36, 0xd, 0xa9, 0xc3, 0x69, 0x97, 0x53, 0x58, 0x14},
		{0x3e, 0x83, 0x7a, 0xee, 0x93, 0x14, 0xdf, 0xb, 0x12, 0xe, 0xd4, 0x12, 0x56, 0xcf, 0x9a, 0x51},
		{0x43, 0x58, 0x69, 0x4d, 0xe6, 0x97, 0x21, 0xbb, 0xd2, 0x78, 0x83, 0xf4, 0x98, 0xc3, 0xfa, 0xc9},
		{0xd9, 0xce, 0x18, 0x3a, 0x94, 0xf3, 0x25, 0xe5, 0xec, 0xfd, 0x2a, 0x70, 0xc5, 0xe8, 0x5d, 0x9f},
		{0xd3, 0x4, 0xec, 0x5a, 0xde, 0xc4, 0xb7, 0x36, 0xd, 0xa9, 0xc3, 0x69, 0x97, 0x53, 0x58, 0x14},
		{0x3e, 0x83, 0x7a, 0xee, 0x93, 0x14, 0xdf, 0xb, 0x12, 0xe, 0xd4, 0x12, 0x56, 0xcf, 0x9a, 0x51},
		{0x43, 0x58, 0x69, 0x4d, 0xe6, 0x97, 0x21, 0xbb, 0xd2, 0x78, 0x83, 0xf4, 0x98, 0xc3, 0xfa, 0xc9},
		{0xd9, 0xce, 0x18, 0x3a, 0x94, 0xf3, 0x25, 0xe5, 0xec, 0xfd, 0x2a, 0x70, 0xc5, 0xe8, 0x5d, 0x9f},
		{0xd3, 0x4, 0xec, 0x5a, 0xde, 0xc4, 0xb7, 0x36, 0xd, 0xa9, 0xc3, 0x69, 0x97, 0x53, 0x58, 0x14},
		{0x3e, 0x83, 0x7a, 0xee, 0x93, 0x14, 0xdf, 0xb, 0x12, 0xe, 0xd4, 0x12, 0x56, 0xcf, 0x9a, 0x51},
		{0x43, 0x58, 0x69, 0x4d, 0xe6, 0x97, 0x21, 0xbb, 0xd2, 0x78, 0x83, 0xf4, 0x98, 0xc3, 0xfa, 0xc9},
		{0xd9, 0xce, 0x18, 0x3a, 0x94, 0xf3, 0x25, 0xe5, 0xec, 0xfd, 0x2a, 0x70, 0xc5, 0xe8, 0x5d, 0x9f},
		{0xd3, 0x4, 0xec, 0x5a, 0xde, 0xc4, 0xb7, 0x36, 0xd, 0xa9, 0xc3, 0x69, 0x97, 0x53, 0x58, 0x14},
		{0x3e, 0x83, 0x7a, 0xee, 0x93, 0x14, 0xdf, 0xb, 0x12, 0xe, 0xd4, 0x12, 0x56, 0xcf, 0x9a, 0x51},
		{0x43, 0x58, 0x69, 0x4d, 0xe6, 0x97, 0x21, 0xbb, 0xd2, 0x78, 0x83, 0xf4, 0x98, 0xc3, 0xfa, 0xc9},
		{0xd9, 0xce, 0x18, 0x3a, 0x94, 0xf3, 0x25, 0xe5, 0xec, 0xfd, 0x2a, 0x70, 0xc5, 0xe8, 0x5d, 0x9f},
		{0xd3, 0x4, 0xec, 0x5a, 0xde, 0xc4, 0xb7, 0x36, 0xd, 0xa9, 0xc3, 0x69, 0x97, 0x53, 0x58, 0x14},
		{0x3e, 0x83, 0x7a, 0xee, 0x93, 0x14, 0xdf, 0xb, 0x12, 0xe, 0xd4, 0x12, 0x56, 0xcf, 0x9a, 0x51},
		{0x43, 0x58, 0x69, 0x4d, 0xe6, 0x97, 0x21, 0xbb, 0xd2, 0x78, 0x83, 0xf4, 0x98, 0xc3, 0xfa, 0xc9},
		{0xd9, 0xce, 0x18, 0x3a, 0x94, 0xf3, 0x25, 0xe5, 0xec, 0xfd, 0x2a, 0x70, 0xc5, 0xe8, 0x5d, 0x9f},
		{0xd3, 0x4, 0xec, 0x5a, 0xde, 0xc4, 0xb7, 0x36, 0xd, 0xa9, 0xc3, 0x69, 0x97, 0x53, 0x58, 0x14},
};

/*******************************************************************************
 * Code
 ******************************************************************************/

/**
 * @brief Initialize database of users, first user in the database is Master
 *
 * Master user has index 0 and ability to add other users to the DB
 * mifareKey - key for mifare authentication
 * authKey - key/password saved on tag for user authentication
 * uid - unique identification of Mifare tag
 */
void initDB()
{
	user_array_ptr = &arr_user;

	memcpy((*user_array_ptr)[0].mifareKey, master_mifare, MIFARE_SIZE);
	memcpy((*user_array_ptr)[0].authKey, master_key, KEY_SIZE);
	memcpy((*user_array_ptr)[0].uid, master_uid, UID_SIZE);

	for (i=1; i<USERS; i++)
	{
		memcpy((*user_array_ptr)[i].mifareKey, default_mifare, MIFARE_SIZE);
		memcpy((*user_array_ptr)[i].authKey, default_keys[i], KEY_SIZE);
		memcpy((*user_array_ptr)[i].uid, default_uid, UID_SIZE);
	}
}

/**
 * @brief Prints database of users
 *
 */
void printDB()
{
	printf("Address: 0x%x\n", user_array_ptr);

	for (i=0; i<USERS; i++)
	{
		printf("Mifare Key: ");
		print_buf(" ", (*user_array_ptr)[i].mifareKey, MIFARE_SIZE);
		printf("authKey: ");
		print_buf(" ", (*user_array_ptr)[i].authKey, KEY_SIZE);
		printf("UID: ");
		print_buf(" ", (*user_array_ptr)[i].uid, UID_SIZE);
	}
}

/**
 * @brief Insert user to the first free position in the DB
 *
 * @param uid pointer to array with UID
 * @return true if user was inserted successfuly or false if the user is already there or 
 * if the DB is full
 */
uint8_t insertUser(const unsigned char * uid)
{
	user_array_ptr = &arr_user;

	for (i=1; i<USERS; i++)
	{
		if (memcmp((*user_array_ptr)[i].uid, uid, UID_SIZE) == 0)
		{
			printf("UID already in DB\n");
			return 0;
		}
		else if(memcmp((*user_array_ptr)[i].uid, default_uid, UID_SIZE) == 0)
		{
			memcpy((*user_array_ptr)[i].uid, uid, UID_SIZE);
			return 1;
		}
	}
	printf("DB is full\n");
	return 0;
}

/**
 * @brief delete UID from the DB (replace it with default UID)
 *
 * @param uid pointer to array with UID
 * @return true if user was deleted successfuly
 */
uint8_t deleteUser(const unsigned char * uid)
{
	user_array_ptr = &arr_user;

	if (memcmp(uid, default_uid, UID_SIZE) == 0)
	{
		printf("Error: cannot delete default UID\n");
		return 0;
	}
	for (i=1; i<USERS; i++)
	{
		if (memcmp((*user_array_ptr)[i].uid, uid, UID_SIZE) == 0)
		{
			memcpy((*user_array_ptr)[i].uid, default_uid, UID_SIZE);
			printf("UID deleted\n");
			return 1;
		}
	}
	return 0;
}


/**
 * @brief Get auth key and mifare key of the user
 *
 * @param uid unique identification of the user (tag)
 * @param authKey authoritzation key saved on a card
 * @param mifareKey mifare key
 * @return uint8_t returns True if uid is in the DB
 * 			return 2 if the user is master user
 */
uint8_t getAuth(unsigned char* uid, unsigned char* authKey, unsigned char* mifareKey)
{
	user_array_ptr = (user_t(*)[])destAdrss;

	if (memcmp(uid, default_uid, UID_SIZE) == 0)
	{
		printf("Error: cannot get authentication for default UID\n");
		return 0;
	}

	if (memcmp(uid, master_uid, UID_SIZE) == 0)
	{
		printf("Master USER tag detected\n");
		memcpy(mifareKey, master_mifare, MIFARE_SIZE);
		memcpy(authKey, master_key, KEY_SIZE);
		return 2;
	}

	for(i=0; i<USERS; i++)
	{

		if (memcmp((*user_array_ptr)[i].uid, uid, UID_SIZE) == 0)
		{
			memcpy(mifareKey, (*user_array_ptr)[i].mifareKey, MIFARE_SIZE);
			memcpy(authKey, (*user_array_ptr)[i].authKey, KEY_SIZE);
			return 1;
		}
	}
	return 0;
}

/**
 * @brief Initialize flash driver and get flash properties
 *
 * @return status_t
 */
status_t initFlash()
{
	ftfx_security_state_t securityStatus = kFTFx_SecurityStateNotSecure; /* Return protection status */
	status_t result;    /* Return code from each flash driver function */

	/* Clean up Flash, Cache driver Structure*/
	memset(&s_flashDriver, 0, sizeof(flash_config_t));
	memset(&s_cacheDriver, 0, sizeof(ftfx_cache_config_t));

	/* Setup flash driver structure for device and initialize variables. */
	result = FLASH_Init(&s_flashDriver);
	if (kStatus_FTFx_Success != result)
	{
		printf("Error during flash initialization\n");
		return result;
	}
	/* Setup flash cache driver structure for device and initialize variables. */
	result |= FTFx_CACHE_Init(&s_cacheDriver);
	if (kStatus_FTFx_Success != result)
	{
		printf("Error during cache initialization\n");
		return result;
	}
	/* Get flash properties*/
	FLASH_GetProperty(&s_flashDriver, kFLASH_PropertyPflash0BlockBaseAddr, &pflashBlockBase);
	FLASH_GetProperty(&s_flashDriver, kFLASH_PropertyPflash0TotalSize, &pflashTotalSize);
	FLASH_GetProperty(&s_flashDriver, kFLASH_PropertyPflash0SectorSize, &pflashSectorSize);

	/* Print flash information - PFlash. */
	printf("\r\n PFlash Information: ");
	printf("\r\n Total Program Flash Size:\t%d KB, Hex: (0x%x)", (pflashTotalSize / 1024), pflashTotalSize);
	printf("\r\n Program Flash Sector Size:\t%d KB, Hex: (0x%x) ", (pflashSectorSize / 1024), pflashSectorSize);

	/* Check security status. */
	result |= FLASH_GetSecurityState(&s_flashDriver, &securityStatus);
	if (kStatus_FTFx_Success != result)
	{
		printf("Cannot get flash security status\n");
		return result;
	}
	/* Print security status. */
	switch (securityStatus)
	{
	case kFTFx_SecurityStateNotSecure:
		printf("\r\n Flash is UNSECURE!");
		break;
	case kFTFx_SecurityStateBackdoorEnabled:
		printf("\r\n Flash is SECURE, BACKDOOR is ENABLED!");
		break;
	case kFTFx_SecurityStateBackdoorDisabled:
		printf("\r\n Flash is SECURE, BACKDOOR is DISABLED!");
		break;
	default:
		break;
	}
	printf("\r\n");

	/* Test pflash basic opeation only if flash is unsecure. */
	if (kFTFx_SecurityStateNotSecure == securityStatus)
	{
		/* Pre-preparation work about flash Cache/Prefetch/Speculation. */
		FTFx_CACHE_ClearCachePrefetchSpeculation(&s_cacheDriver, true);
	}

	destAdrss = pflashBlockBase + (pflashTotalSize - (SECTOR_INDEX_FROM_END * pflashSectorSize));

	return result;
}

void copyFlash()
{
	user_array_ptr = (user_t(*)[])destAdrss;
	memcpy(&arr_user, user_array_ptr, sizeof(arr_user));
	return;
}

/**
 * @brief Erase flash sector as defined in SECTOR_INDEX_FROM_END
 *
 * @return uint8_t
 */
status_t eraseFlash()
{
	status_t result;    /* Return code from each flash driver function */
	/* Erase a sector from destAdrss. */

	result = FLASH_Erase(&s_flashDriver, destAdrss, pflashSectorSize, kFTFx_ApiEraseKey);
	if (kStatus_FTFx_Success != result)
	{
		printf("Error during flash erase\n");
		return result;
	}

	/* Verify sector if it's been erased. */
	result |= FLASH_VerifyErase(&s_flashDriver, destAdrss, pflashSectorSize, kFTFx_MarginValueUser);
	if (kStatus_FTFx_Success != result)
	{
		printf("Error during flash erase verification\n");
		return result;
	}

	/* Print message for user. */
	printf("\r\n Successfully Erased Sector 0x%x -> 0x%x\r\n", destAdrss, (destAdrss + pflashSectorSize));
	return result;
}

status_t writeFlash()
{
	status_t result;    /* Return code from each flash driver function */
	uint32_t failAddr, failDat;

	printf("\r\n Size %d B, Hex: (0x%x) ", sizeof(arr_user), (uint8_t *)&arr_user);

	/* Program user array into flash*/
	result = FLASH_Program(&s_flashDriver, destAdrss, (uint8_t *)&arr_user, sizeof(arr_user));
	if (kStatus_FTFx_Success != result)
	{
		printf("Error during flash programming\n");
		return result;
	}

	/* Verify programming by Program Check command with user margin levels */
	result |= FLASH_VerifyProgram(&s_flashDriver, destAdrss, sizeof(arr_user), (const uint8_t *)&arr_user,
			kFTFx_MarginValueUser, &failAddr, &failDat);

	if (kStatus_FTFx_Success != result)
	{
		printf("Error during flash verification\n");
		return result;
	}

	printf("\r\n Successfully Written Sector 0x%x -> 0x%x\r\n", destAdrss, (destAdrss + pflashSectorSize));
	/* Post-preparation work about flash Cache/Prefetch/Speculation. */
	FTFx_CACHE_ClearCachePrefetchSpeculation(&s_cacheDriver, false);

	return result;
}

