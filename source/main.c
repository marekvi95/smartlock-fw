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
 * @file    K32L2B31xxxxA_Project.c
 * @brief   Application entry point.
 */
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
/* TODO: insert other include files here. */
#include "nfc_task.h"
#include "sf/sf.h"
#include "demo_sigfox.h"
#include "epaper_2in13.h"
#include "ltc2942.h"
#include "Fonts/fonts.h"
#include "GUI/GUI_Paint.h"
//#include "power_mode_switch.h"
/* TODO: insert other definitions and declarations here. */
/* Maximum number characters (bytes) in record. */
#define MSG_CHAR_MAX     40
/*
 * @brief   Application entry point.
 */
int main(void) {
	sf_drv_data_t sfDrvData;
	sf_device_info_t devInfo;
	status_t status = kStatus_Success;
	// smc_power_state_t curPowerState;
    // app_power_mode_t targetPowerMode;
    // bool needSetWakeup; /* Need to set wakeup. */

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

	BOARD_InitBootClocks();
	BOARD_InitBootPeripherals();
	/* Init FSL debug console. */
	// BOARD_InitDebugConsole();

	/* Initialize Waveshare display */
	EPD_Init(FULL_UPDATE);

	/* Display NXP logo */
	EPD_Display(nxp_image);
	EPD_Clear();

	unsigned char BlackImage[4000];
	Paint_NewImage(BlackImage, EPD_WIDTH, EPD_HEIGHT, 270, WHITE);
	Paint_SelectImage(BlackImage);
	Paint_SetMirroring(MIRROR_HORIZONTAL); //
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
			/* Run the NFC polling app. */
			printf("\nRunning the NXP-NCI project.\n");
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
