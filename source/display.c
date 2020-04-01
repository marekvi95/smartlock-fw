/*
 * display.c
 *
 *  Created on: Apr 1, 2020
 *      Author: nxf46245
 */



#include <stddef.h>
#include "Fonts/fonts.h"
#include "GUI/GUI_Paint.h"
#include "epaper_2in13.h"

#define IMAGE_SIZE ((EPD_WIDTH % 8 == 0)? (EPD_WIDTH / 8 ): (EPD_WIDTH / 8 + 1)) * EPD_HEIGHT
#define LOCKED_STRING "$*,^"
#define UNLOCKED_STRING "$*,`"

char * default_text = "Swipe card";

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

	Paint_NewImage(BlackImage, EPD_WIDTH, EPD_HEIGHT, 90, WHITE);
	Paint_SelectImage(BlackImage);
	Paint_SetMirroring(MIRROR_HORIZONTAL);
	Paint_Clear(WHITE);


	if(locked)
	{
		Paint_DrawString_EN(2, 2, LOCKED_STRING, &Font24, WHITE, BLACK);
	}
	else
	{
		Paint_DrawString_EN(2,2, UNLOCKED_STRING ,&Font24, WHITE, BLACK);
	}

	Paint_DrawString_EN(30,30, main_text, &Font24, WHITE, BLACK);

	if (second_text != NULL)
		Paint_DrawString_EN(30,70, second_text, &Font12, WHITE, BLACK);

	EPD_Display(BlackImage);
}
