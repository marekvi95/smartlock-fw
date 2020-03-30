/*
 * demo_sigfox.h
 *
 *  Created on: 09 May 2019
 *      Author: nxf05489
 */

#ifndef SIGFOX_H_
#define SIGFOX_H_

#define BOARD_INITPINS_SIGFOX_CS_INST instanceD
#define BOARD_INITPINS_SIGFOX_AK_INST instanceC

/* Maximum number characters (bytes) in Sigfox message. */
#define SIGFOX_RECORD_CHAR_MAX  12

#include "sf/sf.h"


/*!
 * @brief Initializes SIGFOX device and SW driver.
 *
 * @param drvData Driver run-time data.
 *
 * @return Status result of the function.
 */
status_t SIGFOX_SetupDriver(sf_drv_data_t *drvData);

/*!
 * @brief Prints Sigfox device PAC & ID to LCD and via UART.
 */
void SIGFOX_PrintDeviceInfo(const sf_device_info_t *devInfo);

/*
 * @brief This function sends a string (cropped to max. 12 characters) to the Sigfox network.
 */
status_t SIGFOX_SendRecords(sf_drv_data_t *sfDriverConfig, uint8_t *nfcRec, uint32_t nfcRecLen);

/*
 * @brief This function asks OL2385 to send a string (cropped to max. 12 characters) to the Sigfox network.
 */
status_t SIGFOX_SendRecords_NonBlock(sf_drv_data_t *sfDriverConfig, uint8_t *nfcRec, uint32_t nfcRecLen);

/*
 * @brief This function checks if response from OL2385 is ready.
 */
bool SIGFOX_IsAckFrameReady(sf_drv_data_t *sfDriverConfig);

/*
 * @brief This function finishes the non-blocking operation.
 */
status_t SIGFOX_FinishNonBlock(sf_drv_data_t *sfDriverConfig);

#endif /* SIGFOX_H_ */
