/*
 * display.c
 *
 *  Created on: Apr 1, 2020
 *      Author: nxf46245
 */

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "Fonts/fonts.h"
#include "GUI/GUI_Paint.h"
#include "epaper_2in13.h"

#define IMAGE_SIZE ((EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1)) * EPD_HEIGHT
//#define LOCKED_STRING "$*,^"
//#define UNLOCKED_STRING "$*,`"

#define LOCKED_CHAR '^'
#define UNLOCKED_CHAR '`'
#define BATTERY_FULL '$'
#define BATTERY_LOW '"'
#define BATTERY_MED '#'
#define NFC_CHAR '*'
#define BATT_CHARGING '&'
#define SIGFOX_CHAR ','
#define EMPTY_CHAR ' '

char * default_text = "Swipe card";

typedef struct {
	bool locked;
	bool sigfoxInit;
	bool NFCInit;
	bool charging;
	int8_t battery;
} LockStatus;

// Default status
LockStatus status = {true, false, false, false, 100};

void initDisplay(void)
{
	/* Initialize Waveshare display with full update */
	EPD_Init(FULL_UPDATE);

	/* Display NXP logo */
	EPD_Display(nxp_image);
	EPD_Clear();
}

void displayText(uint8_t locked, const char * main_text, const char * second_text)
{
	static unsigned char BlackImage[IMAGE_SIZE];
	static char textBuff[6];
	textBuff[5] = '\0';

	Paint_NewImage(BlackImage, EPD_WIDTH, EPD_HEIGHT, 90, WHITE);
	Paint_SelectImage(BlackImage);
	Paint_SetMirroring(MIRROR_HORIZONTAL);
	Paint_Clear(WHITE);

	textBuff[0] = status.locked ? LOCKED_CHAR : UNLOCKED_CHAR;

	if (status.battery > 60)
		textBuff[1] = BATTERY_FULL;
	else if (status.battery > 30)
		textBuff[1] = BATTERY_MED;
	else
		textBuff[1] = BATTERY_LOW;

	textBuff[2] = status.sigfoxInit ? SIGFOX_CHAR : EMPTY_CHAR;
	textBuff[3] = status.NFCInit ? NFC_CHAR : EMPTY_CHAR;
	textBuff[4] = status.charging ? BATT_CHARGING : EMPTY_CHAR;

	Paint_DrawString_EN(2, 2, textBuff, &Font24, WHITE, BLACK);

//	if(status.locked)
//	{
//		Paint_DrawString_EN(2, 2, LOCKED_STRING, &Font24, WHITE, BLACK);
//	}
//	else
//	{
//		Paint_DrawString_EN(2,2, UNLOCKED_STRING ,&Font24, WHITE, BLACK);
//	}

	Paint_DrawString_EN(30,30, main_text, &Font24, WHITE, BLACK);

	if (second_text != NULL)
		Paint_DrawString_EN(30,70, second_text, &Font12, WHITE, BLACK);

	EPD_Display(BlackImage);
}

bool isLocked(void)
{
	return status.locked;
}

void setLock(void)
{
	status.locked = true;
}

void setUnlock(void)
{
	status.locked = false;
}

void setSigfox(void)
{
	status.sigfoxInit = true;
}

void setNFC(void)
{
	status.NFCInit = true;
}

void setBattery(uint8_t battery)
{
	status.battery = battery;
}



