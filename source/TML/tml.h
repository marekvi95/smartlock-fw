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

#define TIMEOUT_INFINITE	0
#define TIMEOUT_100MS		100
#define TIMEOUT_1S			1000
#define TIMEOUT_2S			2000

#define NXPNCI_I2C_INSTANCE         I2C0
#define NXPNCI_I2C_BAUDRATE         (100000)
#define NXPNCI_I2C_ADDR             (0x28)
//#define BOARD_INITPINS_NFC_INT_GPIO GPIOB

void tml_Connect(void);
void tml_Disconnect(void);
void tml_Send(uint8_t *pBuffer, uint16_t BufferLen, uint16_t *pBytesSent);
void tml_Receive(uint8_t *pBuffer, uint16_t BufferLen, uint16_t *pBytes, uint16_t timeout);
