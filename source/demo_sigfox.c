/*
 * demo_sigfox.c
 *
 *  Created on: 07 May 2019
 *      Author: nxf05489
 */

#include <stdio.h>
#include "app_config.h"
#include "demo_sigfox.h"
//#include "demo_lcd.h"
#include "pin_mux.h"

/*!
 * @brief Gets source clock for SPI peripheral.
 */
#define GET_SPI_MODULE_CLK() \
    (CLOCK_GetFreq(kCLOCK_BusClk))

/* Maximum number characters (bytes) in Sigfox message. */
#define SIGFOX_RECORD_CHAR_MAX  12

/* OL2385 PA Table for RCZ1 and RCZ3. */
uint8_t etsiPA[SF_PA_TBL_SIZE] =
{
    0x74, 0x74, 0x74, 0x74, 0x74, 0x74, 0x74, 0x74, 0x74, 0x74, 0x74, 0x74, 0x74, 0x74, 0x74, 0x74, 0x74, 0x74, 0x74, 0x74,
    0x74, 0x74, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x72, 0x72,
    0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72, 0x71, 0x71, 0x71, 0x71, 0x71, 0x71, 0x71, 0x71, 0x71, 0x70, 0x70, 0x70,
    0x70, 0x70, 0x70, 0x70, 0x6F, 0x6F, 0x6F, 0x6F, 0x6F, 0x6F, 0x6F, 0x6E, 0x6E, 0x6E, 0x6E, 0x6E, 0x6E, 0x6D, 0x6D, 0x6D,
    0x6D, 0x6D, 0x6C, 0x6C, 0x6C, 0x6C, 0x6C, 0x6B, 0x6B, 0x6B, 0x6B, 0x6A, 0x6A, 0x6A, 0x6A, 0x69, 0x69, 0x69, 0x69, 0x68,
    0x68, 0x68, 0x68, 0x67, 0x67, 0x67, 0x66, 0x66, 0x66, 0x66, 0x65, 0x65, 0x65, 0x64, 0x64, 0x64, 0x63, 0x63, 0x63, 0x62,
    0x62, 0x62, 0x61, 0x61, 0x60, 0x60, 0x60, 0x5F, 0x5F, 0x5E, 0x5E, 0x5D, 0x5D, 0x5D, 0x5C, 0x5C, 0x5B, 0x5B, 0x5A, 0x5A,
    0x59, 0x59, 0x58, 0x57, 0x57, 0x56, 0x56, 0x55, 0x55, 0x54, 0x53, 0x53, 0x52, 0x51, 0x51, 0x50, 0x4F, 0x4E, 0x4E, 0x4D,
    0x4C, 0x4B, 0x4A, 0x49, 0x48, 0x48, 0x47, 0x46, 0x45, 0x44, 0x42, 0x41, 0x40, 0x3F, 0x3E, 0x3C, 0x3B, 0x39, 0x38, 0x36,
    0x35, 0x33, 0x31, 0x2F, 0x2D, 0x2B, 0x29, 0x26, 0x24, 0x21, 0x1E, 0x1B, 0x17, 0x14, 0x10, 0x0C, 0x07, 0x06, 0x06, 0x06,
};

/* OL2385 PA Table for RCZ2 and RCZ4. */
uint8_t fccPA[SF_PA_TBL_SIZE] =
{
    0x74, 0x74, 0x74, 0x74, 0x74, 0x74, 0x74, 0x74, 0x74, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x73, 0x72, 0x72, 0x72, 0x72,
    0x72, 0x71, 0x71, 0x71, 0x70, 0x70, 0x70, 0x70, 0x6F, 0x6F, 0x6E, 0x6E, 0x6E, 0x6D, 0x6D, 0x6C, 0x6C, 0x6B, 0x6B, 0x6A,
    0x6A, 0x69, 0x69, 0x68, 0x67, 0x67, 0x66, 0x65, 0x64, 0x64, 0x63, 0x62, 0x61, 0x60, 0x5F, 0x5E, 0x5D, 0x5C, 0x5B, 0x5A,
    0x59, 0x57, 0x56, 0x55, 0x53, 0x52, 0x50, 0x4E, 0x4D, 0x4B, 0x48, 0x46, 0x44, 0x41, 0x3E, 0x3B, 0x38, 0x34, 0x30, 0x2B,
    0x26, 0x1F, 0x17, 0x0E, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
};

/*!
 * @brief Initializes SIGFOX device and SW driver.
 *
 * @param drvData Driver run-time data.
 *
 * @return Status result of the function.
 */
status_t SIGFOX_SetupDriver(sf_drv_data_t *drvData)
{
    sf_user_config_t userConfig;
    uint32_t i;

    /* Reset of Sigfox board. */
    GPIO_PinWrite(BOARD_INITPINS_SIGFOX_RST_GPIO, BOARD_INITPINS_SIGFOX_RST_PIN, 0);
    for(i = 0; i < 50000; i++);
    GPIO_PinWrite(BOARD_INITPINS_SIGFOX_RST_GPIO, BOARD_INITPINS_SIGFOX_RST_PIN, 1);
    for(i = 0; i < 50000; i++);

    SF_GetDefaultConfig(&userConfig);
    userConfig.xtal = SF_XTAL;
    userConfig.netStandard = SF_STANDARD;

    /* GPIOs initialization.
     * Note: GPIO settings are place in pin_mux.h file. */
//    /* ACK pin. */
//    drvData->gpioConfig.ackAdcInstance = BOARD_INITPINS_SIGFOX_AK_PERIPHERAL;
//    drvData->gpioConfig.ackAdcChannel = BOARD_INITPINS_SIGFOX_AK_CHANNEL;
    /* ACK pin. */
    drvData->gpioConfig.ackPin.gpioInstance = BOARD_INITPINS_SIGFOX_AK_INST;
    drvData->gpioConfig.ackPin.gpioPinNumber = BOARD_INITPINS_SIGFOX_AK_PIN;

    /* CS pin. */
    drvData->gpioConfig.csPin.gpioInstance = BOARD_INITPINS_SIGFOX_CS_INST;
    drvData->gpioConfig.csPin.gpioPinNumber = BOARD_INITPINS_SIGFOX_CS_PIN;

    SF_SetupGPIOs(&(drvData->gpioConfig));

    /* SPI initialization. */
    drvData->spiConfig.baudRate = 125000U;
    drvData->spiConfig.sourceClkHz = GET_SPI_MODULE_CLK();
    drvData->spiConfig.spiInstance = 0;

    SF_SetupSPI(&(drvData->spiConfig), NULL);

    /* Sigfox driver initialization.
     * Note: drvData->gpioConfig and drvData->spiConfig structures are used
     * by SF_SetupGPIOs, SF_SetupSPI and SF_Init. */
    return SF_Init(drvData, &userConfig);
}

/*!
 * @brief Prints Sigfox device PAC & ID to LCD and via UART.
 */
void SIGFOX_PrintDeviceInfo(const sf_device_info_t *devInfo)
{
//    char m[100];

    AML_ASSERT(devInfo != NULL);

    /* Send to UART. */
    printf("\tDevice ID:\t0x%08lx\r\n", devInfo->devId);

    printf("\tPAC = 0x");
    printf("%02x%02x ", devInfo->devPac[0], devInfo->devPac[1]);
    printf("%02x%02x ", devInfo->devPac[2], devInfo->devPac[3]);
    printf("%02x%02x ", devInfo->devPac[4], devInfo->devPac[5]);
    printf("%02x%02x\r\n", devInfo->devPac[6], devInfo->devPac[7]);

    printf("\tDevice version = 0x");
    printf("%02x%02x ", devInfo->devVersion[6], devInfo->devVersion[5]);
    printf("%02x%02x ", devInfo->devVersion[4], devInfo->devVersion[3]);
    printf("%02x%02x ", devInfo->devVersion[2], devInfo->devVersion[1]);
    printf("%02x\r\n", devInfo->devVersion[0]);

    printf("\tLibrary version = 0x");
    printf("%02x%02x ", devInfo->libVersion[10], devInfo->libVersion[9]);
    printf("%02x%02x ", devInfo->libVersion[8], devInfo->libVersion[7]);
    printf("%02x%02x ", devInfo->libVersion[6], devInfo->libVersion[5]);
    printf("%02x%02x ", devInfo->libVersion[4], devInfo->libVersion[3]);
    printf("%02x%02x ", devInfo->libVersion[2], devInfo->libVersion[1]);
    printf("%02x\r\n", devInfo->libVersion[0]);

//    /* Show on LCD. */
//    sprintf(m, "ID:\n%08lx\n\nPAC:\n%02x%02x%02x%02x%02x%02x%02x%02x", devInfo->devId,
//			devInfo->devPac[0], devInfo->devPac[1], devInfo->devPac[2], devInfo->devPac[3],
//			devInfo->devPac[4], devInfo->devPac[5], devInfo->devPac[6], devInfo->devPac[7]);
//    DEMO_ShowMessage(m, GUI_BLACK);
}

/*
 * @brief This function sends a string (cropped to max. 12 characters) to the Sigfox network.
 */
status_t SIGFOX_SendRecords(sf_drv_data_t *sfDriverConfig, uint8_t *nfcRec, uint32_t nfcRecLen)
{
    sf_msg_payload_t payload;
//    uint8_t readTable[SF_PA_TBL_SIZE];
    status_t status = kStatus_Success;

    status = SF_WakeUp(sfDriverConfig);
    status |= SF_ChangeNetworkStandard(sfDriverConfig, SF_STANDARD, 0, SF_XTAL, sfTxRepeat3, sfPa14);
    status |= SF_UpdatePATable(sfDriverConfig, SF_STANDARD,
    		((SF_STANDARD == sfNetStandardETSI) || (SF_STANDARD == sfNetStandardARIB)) ? etsiPA : fccPA);

    /* Check that PA Table was set well. */
//    status |= SF_ReadCurrentPATable(sfDriverConfig, sfNetStandardETSI, readTable);
//    for (uint32_t i = 0; i < SF_PA_TBL_SIZE; i++)
//    {
//        if (table[i] != tableRead[i])
//            return kStatus_Fail;
//    }

    payload.payload = nfcRec;
    payload.payloadLen = (nfcRecLen <= SIGFOX_RECORD_CHAR_MAX) ? nfcRecLen : SIGFOX_RECORD_CHAR_MAX;
    if (status == kStatus_Success)
    {
        status = SF_SendPayload(sfDriverConfig, &payload);
    }

    status |= SF_Sleep(sfDriverConfig);

    return status;
}

/*
 * @brief This function asks OL2385 to send a string (cropped to max. 12 characters) to the Sigfox network.
 */
status_t SIGFOX_SendRecords_NonBlock(sf_drv_data_t *sfDriverConfig, uint8_t *nfcRec, uint32_t nfcRecLen)
{
    sf_msg_payload_t payload;
    status_t status = kStatus_Success;

    status = SF_WakeUp(sfDriverConfig);
    status |= SF_ChangeNetworkStandard(sfDriverConfig, SF_STANDARD, 0, SF_XTAL, sfTxRepeat3, sfPa14);
    status |= SF_UpdatePATable(sfDriverConfig, SF_STANDARD,
    		((SF_STANDARD == sfNetStandardETSI) || (SF_STANDARD == sfNetStandardARIB)) ? etsiPA : fccPA);

    payload.payload = nfcRec;
    payload.payloadLen = (nfcRecLen <= SIGFOX_RECORD_CHAR_MAX) ? nfcRecLen : SIGFOX_RECORD_CHAR_MAX;
    if (status == kStatus_Success)
    {
        status = SF_SendCommandNonBlock(sfDriverConfig, sfSpiCmdSendPayload, &payload);
    }

    return status;
}

/*
 * @brief This function checks if response from OL2385 is ready.
 */
bool SIGFOX_IsAckFrameReady(sf_drv_data_t *sfDriverConfig)
{
    return SF_IsAckFrameReady(sfDriverConfig);
}

/*
 * @brief This function finishes the non-blocking operation.
 */
status_t SIGFOX_FinishNonBlock(sf_drv_data_t *sfDriverConfig)
{
    sf_msg_payload_t recvPayload;
    uint8_t tmp[10];

    recvPayload.payload = tmp;
    recvPayload.payloadLen = 10;

    return SF_ReadAckFrameNonBlock(sfDriverConfig, &recvPayload, 10U);

    return kStatus_Success;
}
