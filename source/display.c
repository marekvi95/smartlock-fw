/*
 * display.c
 *
 *  Created on: Apr 1, 2020
 *      Author: Marek Vitula
 */

#include <stddef.h>
#include <stdbool.h>
#include <stdint.h>
#include "Fonts/fonts.h"
#include "GUI/GUI_Paint.h"
#include "epaper_2in13.h"

#define IMAGE_SIZE ((EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1)) * EPD_HEIGHT

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

/**
 * @brief Status of the lock
 * 
 */
typedef struct {
	bool locked;
	bool sigfoxInit;
	bool NFCInit;
	bool charging;
	int8_t battery;
} LockStatus;

// Default status
LockStatus status = {true, false, false, false, 100};

/**
 * @brief Initialize Waveshare display and display NXP logo for a moment
 * 
 */
void initDisplay(void)
{
	/* Initialize Waveshare display with full update */
	EPD_Init(FULL_UPDATE);

	/* Display NXP logo */
	EPD_Display(nxp_image);
	EPD_Clear();
}

/**
 * @brief Display text on the waveshare display
 * Also displays status bar 
 * 
 * @param main_text Main text that will be displayed with font size 24
 * @param second_text Secondary text will be displayed with font size 12
 */
void displayText(const char * main_text, const char * second_text)
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

void triggerCharging()
{
	status.charging = !status.charging;

	if (status.charging)
	{
		displayText("Charging", "Charging started");
	}
	else
	{
		displayText("Charging stop", "Charging aborted");
	}
}

/**
 * @brief Returns status of the battery for the Sigfox message
 * 
 * @return uint8_t batt status
 */
uint8_t getBatteryMsg()
{
	#define CHARGING_MSG 0
	#define FULL_MSG 3
	#define MED_MSG 2
	#define LOW_MSG 1

	uint8_t batt;

	if (status.charging)
		batt = CHARGING_MSG;
	else if (status.battery > 60)
		batt = FULL_MSG;
	else if (status.battery > 30)
		batt = MED_MSG;
	else
		batt = LOW_MSG;

	return batt;
}

uint8_t getBatteryFull()
{
	return status.battery;
}
