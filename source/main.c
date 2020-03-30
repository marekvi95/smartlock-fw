/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file   	main.c
 * @brief   Application entry point.
 */

#include <sigfox.h>
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "K32L2B31A.h"
#include "fsl_debug_console.h"
#include "fsl_smc.h"
#include "fsl_rcm.h"
#include "fsl_pmc.h"
#include "sf/sf.h"
#include "nfc_task.h"
#include "epaper_2in13.h"
#include "ltc2942.h"
#include "Fonts/fonts.h"
#include "GUI/GUI_Paint.h"

/* Maximum number characters (bytes) in record. */
#define MSG_CHAR_MAX     40
/*
 * @brief   Application entry point.
 */
int main(void) {
	sf_drv_data_t sfDrvData;
	sf_device_info_t devInfo;
	status_t status = kStatus_Success;

	/* NFC record to be send via Sigfox (ended by '\0'). */
	unsigned char msg[] = "SigfoxInit";
	/* Length of text record in "msg". Negative value if the record is not valid. */
	uint32_t msgLen = sizeof(msg);

	/* Init board hardware. */
	BOARD_InitBootPins(); /* Must configure pins before PMC_ClearPeriphIOIsolationFlag */

	/* Power related. */
	SMC_SetPowerModeProtection(SMC, kSMC_AllowPowerModeAll);
	if (kRCM_SourceWakeup & RCM_GetPreviousResetSources(RCM)) /* Wakeup from VLLS. */
	{
		PMC_ClearPeriphIOIsolationFlag(PMC);
		NVIC_ClearPendingIRQ(LLWU_IRQn);
	}

	/* Initialize clocks and peripherals */
	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();

	/* Initialize Waveshare display with full update */
	EPD_Init(FULL_UPDATE);

	/* Display NXP logo */
	EPD_Display(nxp_image);
	EPD_Clear();

	uint8_t status_register = LTC2942_GetStatus();
	uint8_t control = LTC2942_GetControl();

	printf("Status: %x \r\n", status_register);
	printf("Control register: %x \r\n", control);

	uint32_t voltage = LTC2942_GetVoltage();
	uint32_t temperature = LTC2942_GetTemperature();

	printf("Voltage: %d mV\r\n", voltage);
	printf("Temperature: %d C\r\n", temperature);

	unsigned char BlackImage[4000];
	Paint_NewImage(BlackImage, EPD_WIDTH, EPD_HEIGHT, 270, WHITE);
	Paint_SelectImage(BlackImage);
	Paint_SetMirroring(MIRROR_HORIZONTAL);
	Paint_Clear(WHITE);

	Paint_DrawString_EN(2,2,"$*,^`",&Font24, WHITE, BLACK);
	Paint_DrawString_EN(30,50,"Swipe card",&Font24, WHITE, BLACK);
	EPD_Display(BlackImage);

	status = SIGFOX_SetupDriver(&sfDrvData);
	if (status != kStatus_Success)
	{
		/* Error in Sigfox initialization. */
		printf("An error occurred in SetupSigfoxDriver (%ld)\r\n", status);

	}
	else
	{
		status = SF_GetDeviceInfo(&sfDrvData, &devInfo);
		if (status == kStatus_Success)
		{
			SIGFOX_PrintDeviceInfo(&devInfo);
		}
		else
		{
			printf("Reading of Sigfox device info failed!");
		}
		if (status == kStatus_Success)
		{
			SIGFOX_SendRecords(&sfDrvData, msg, msgLen);
			/* Run the NFC task. */
			printf("\nRunning the NFC task.\n");
			task_nfc(&sfDrvData);
		}
    }


    /* Force the counter to be placed into memory. */
    volatile static int i = 0 ;
    /* Enter an infinite loop, just incrementing a counter. */
    while(1) {
        i++ ;
        /* 'Dummy' NOP to allow source level single stepping of
            tight while() loop */
        __asm volatile ("nop");
    }
    return 0 ;
}
