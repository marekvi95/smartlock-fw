/*
*         Copyright (c), NXP Semiconductors Caen / France
*
*                     (C)NXP Semiconductors
*       All rights are reserved. Reproduction in whole or in part is
*      prohibited without the written consent of the copyright owner.
*  NXP reserves the right to make changes without notice at any time.
* NXP makes no warranty, expressed, implied or statutory, including but
* not limited to any implied warranty of merchantability or fitness for any
*particular purpose, or that the use will not infringe any third party patent,
* copyright or trademark. NXP must not be liable for any loss or damage
*                          arising from its use.
*/

#include <stdint.h>
#include "pin_mux.h"
#include "fsl_i2c.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "fsl_smc.h"
#include <tool.h>
#include "tml.h"
#include "power_mode_switch.h"

i2c_master_transfer_t masterXfer;
smc_power_state_t curPowerState;
app_power_mode_t targetPowerMode;

typedef enum {ERROR = 0, SUCCESS = !ERROR} Status;

static status_t I2C_WRITE(uint8_t *pBuff, uint16_t buffLen)
{
    masterXfer.direction = kI2C_Write;
    masterXfer.data = pBuff;
    masterXfer.dataSize = buffLen;

    return I2C_MasterTransferBlocking(NXPNCI_I2C_INSTANCE, &masterXfer);
}

static status_t I2C_READ(uint8_t *pBuff, uint16_t buffLen)
{
    masterXfer.direction = kI2C_Read;
    masterXfer.data = pBuff;
    masterXfer.dataSize = buffLen;

    return I2C_MasterTransferBlocking(NXPNCI_I2C_INSTANCE, &masterXfer);
}

static Status tml_Init(void) {
    i2c_master_config_t masterConfig;
    uint32_t sourceClock;

    gpio_pin_config_t irq_config = {kGPIO_DigitalInput, 0,};
    gpio_pin_config_t ven_config = {kGPIO_DigitalOutput, 0,};

    GPIO_PinInit(BOARD_INITPINS_NFC_INT_GPIO, BOARD_INITPINS_NFC_INT_PIN, &irq_config);
    GPIO_PinInit(BOARD_INITPINS_NFC_RST_GPIO, BOARD_INITPINS_NFC_RST_PIN, &ven_config);

    I2C_MasterGetDefaultConfig(&masterConfig);
    masterConfig.baudRate_Bps = NXPNCI_I2C_BAUDRATE;
    sourceClock = CLOCK_GetFreq(I2C0_CLK_SRC);
    masterXfer.slaveAddress = NXPNCI_I2C_ADDR;
    masterXfer.subaddress = 0;
    masterXfer.subaddressSize = 0;
    masterXfer.flags = kI2C_TransferDefaultFlag;
    I2C_MasterInit(NXPNCI_I2C_INSTANCE, &masterConfig, sourceClock);

    return SUCCESS;
}

static Status tml_DeInit(void) {
	GPIO_PortClear(BOARD_INITPINS_NFC_RST_GPIO, 1U << BOARD_INITPINS_NFC_RST_PIN);
    return SUCCESS;
}

static Status tml_Reset(void) {
	GPIO_PortClear(BOARD_INITPINS_NFC_RST_GPIO, 1U << BOARD_INITPINS_NFC_RST_PIN);
	Sleep(10);
	GPIO_PortSet(BOARD_INITPINS_NFC_RST_GPIO, 1U << BOARD_INITPINS_NFC_RST_PIN);
	Sleep(10);
	return SUCCESS;
}

static Status tml_Tx(uint8_t *pBuff, uint16_t buffLen) {
    if (I2C_WRITE(pBuff, buffLen) != kStatus_Success)
    {
    	Sleep(10);
    	if(I2C_WRITE(pBuff, buffLen) != kStatus_Success)
    	{
    		return ERROR;
    	}
    }

	return SUCCESS;
}

static Status tml_Rx(uint8_t *pBuff, uint16_t buffLen, uint16_t *pBytesRead) {
    if(I2C_READ(pBuff, 3) == kStatus_Success)
    {
    	if ((pBuff[2] + 3) <= buffLen)
    	{
			if (pBuff[2] > 0)
			{
				if(I2C_READ(&pBuff[3], pBuff[2]) == kStatus_Success)
				{
					*pBytesRead = pBuff[2] + 3;
				}
				else return ERROR;
			} else
			{
				*pBytesRead = 3;
			}
    	}
		else return ERROR;
   }
    else return ERROR;

	return SUCCESS;
}

static Status tml_WaitForRx(uint32_t timeout) {
	if (timeout == 0) {
	#if defined(SLEEP_MODES) && SLEEP_MODES
	//	put the MCU to sleep here
	targetPowerMode = kAPP_PowerModeLls; /* Set up target power mode */
	curPowerState = SMC_GetPowerModeState(SMC);
	APP_GetWakeupConfig(targetPowerMode);
	APP_PowerPreSwitchHook(curPowerState, targetPowerMode);
	APP_SetWakeupConfig(targetPowerMode);
	APP_PowerModeSwitch(curPowerState, targetPowerMode); /* Go sleep */
	APP_PowerPostSwitchHook(curPowerState, targetPowerMode); /* After wakeup hook */
	#endif
	 while ((GPIO_PinRead(BOARD_INITPINS_NFC_INT_GPIO, BOARD_INITPINS_NFC_INT_PIN) == 0))
	 	;
	} else {
		int16_t to = timeout;
		while ((GPIO_PinRead(BOARD_INITPINS_NFC_INT_GPIO, BOARD_INITPINS_NFC_INT_PIN) == 0)) {
			Sleep(10);
			to -= 10;
			if (to <= 0) return ERROR;
		}
	}
	return SUCCESS;
}

void tml_Connect(void) {
	tml_Init();
	tml_Reset();
}

void tml_Disconnect(void) {
	tml_DeInit();
}

void tml_Send(uint8_t *pBuffer, uint16_t BufferLen, uint16_t *pBytesSent) {
	if(tml_Tx(pBuffer, BufferLen) == ERROR) *pBytesSent = 0;
	else *pBytesSent = BufferLen;
}

void tml_Receive(uint8_t *pBuffer, uint16_t BufferLen, uint16_t *pBytes, uint16_t timeout) {
	if (tml_WaitForRx(timeout) == ERROR) *pBytes = 0;
	else tml_Rx(pBuffer, BufferLen, pBytes);
}


