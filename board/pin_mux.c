/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Pins v7.0
processor: K32L2B31xxxxA
package_id: K32L2B31VLH0A
mcu_data: ksdk2_0
processor_version: 0.7.1
board: FRDM-K32L2B
pin_labels:
- {pin_num: '23', pin_signal: PTA1/LPUART0_RX/TPM2_CH0, label: 'J1[2]/D0/UART0_RX', identifier: DEBUG_UART0_RX}
- {pin_num: '24', pin_signal: PTA2/LPUART0_TX/TPM2_CH1, label: 'J1[4]/D1/UART0_TX', identifier: DEBUG_UART0_TX}
- {pin_num: '60', pin_signal: LCD_P43/PTD3/SPI0_MISO/UART2_TX/TPM0_CH3/SPI0_MOSI/FXIO0_D3, label: 'J1[6]/D2/LCD_P43/SPI_RF_MISO', identifier: LCD_P43;SIGFOX_SDI}
- {pin_num: '28', pin_signal: PTA12/TPM1_CH0, label: 'J1[8]/D3/IN1B', identifier: IN1B}
- {pin_num: '26', pin_signal: PTA4/I2C1_SDA/TPM0_CH1/NMI_b, label: 'J1[10]/D4/SW1', identifier: SW1}
- {pin_num: '27', pin_signal: PTA5/USB_CLKIN/TPM0_CH2, label: 'J1[12]/D5/USB_CLKIN', identifier: USB0_CLKIN}
- {pin_num: '17', pin_signal: CMP0_IN5/ADC0_SE4b/PTE29/TPM0_CH2/TPM_CLKIN0, label: 'J1[14]/D6/CMP0_IN5'}
- {pin_num: '18', pin_signal: DAC0_OUT/ADC0_SE23/CMP0_IN4/PTE30/TPM0_CH3/TPM_CLKIN1/LPUART1_TX/LPTMR0_ALT1, label: 'J1[16]/J4[11]/D7/CMP0_IN4/DAC_OUT/DP_CS'}
- {pin_num: '29', pin_signal: PTA13/TPM1_CH1, label: 'J2[2]/D8/IN2A', identifier: IN2A}
- {pin_num: '59', pin_signal: LCD_P42/PTD2/SPI0_MOSI/UART2_RX/TPM0_CH2/SPI0_MISO/FXIO0_D2, label: 'J2[4]/D9/LCD_P42/SPI_RF_MOSI', identifier: LCD_P42;SIGFOX_SDO}
- {pin_num: '61', pin_signal: LCD_P44/PTD4/LLWU_P14/SPI1_SS/UART2_RX/TPM0_CH4/FXIO0_D4, label: 'J2[6]/D10/SPI1_PCS0/LCD_P44/SPI_DP_SS', identifier: LCD_P44;DP_CS}
- {pin_num: '63', pin_signal: LCD_P46/ADC0_SE7b/PTD6/LLWU_P15/SPI1_MOSI/LPUART0_RX/SPI1_MISO/FXIO0_D6, label: 'J2[8]/D11/SPI1_MOSI/LCD_P46/SPI_DP_MOSI', identifier: DP_DIN}
- {pin_num: '64', pin_signal: LCD_P47/PTD7/SPI1_MISO/LPUART0_TX/SPI1_MOSI/FXIO0_D7, label: 'J2[10]/D12/SPI1_MISO/LCD_P47/SPI_DP_MISO'}
- {pin_num: '62', pin_signal: LCD_P45/ADC0_SE6b/PTD5/SPI1_SCK/UART2_TX/TPM0_CH5/FXIO0_D5, label: 'J2[12]/D13/SPI1_SCK/LED1/LCD_P45/SPI_DP_SCK', identifier: LED1;DP_SCK}
- {pin_num: '1', pin_signal: LCD_P48/PTE0/CLKOUT32K/SPI1_MISO/LPUART1_TX/RTC_CLKOUT/CMP0_OUT/I2C1_SDA, label: 'J2[18]/J4[9]/D14/I2C1_SDA/CMP0_OUT/LCD_P48/NFC_RES',
  identifier: I2C1_SDA;NFC_RES;NFC_RST}
- {pin_num: '2', pin_signal: LCD_P49/PTE1/SPI1_MOSI/LPUART1_RX/SPI1_MISO/I2C1_SCL, label: 'J2[20]/D15/I2C1_SCL/LCD_P49/~RF_RST', identifier: I2C1_SCL;SIGFOX_RST}
- {pin_num: '39', pin_signal: LCD_P12/PTB16/SPI1_MOSI/LPUART0_RX/TPM_CLKIN0/SPI1_MISO, label: 'J2[19]/LCD_P12'}
- {pin_num: '40', pin_signal: LCD_P13/PTB17/SPI1_MISO/LPUART0_TX/TPM_CLKIN1/SPI1_MOSI, label: 'J2[17]/LCD_P13'}
- {pin_num: '54', pin_signal: LCD_P25/PTC5/LLWU_P9/SPI0_SCK/LPTMR0_ALT2/CMP0_OUT, label: 'J1[15]/INT1_ACCEL/LCD_P25/BUTTON_1', identifier: INT1_ACCEL}
- {pin_num: '56', pin_signal: LCD_P27/CMP0_IN1/PTC7/SPI0_MISO/USB_SOF_OUT/SPI0_MOSI, label: 'J1[11]/USB_SOF_OUT/LCD_P27/SPI_RF_MISO', identifier: LCD_P27}
- {pin_num: '55', pin_signal: LCD_P26/CMP0_IN0/PTC6/LLWU_P10/SPI0_MOSI/EXTRG_IN/SPI0_MISO, label: 'J1[9]/LCD_P26/BUTTON_2', identifier: LCD_P26;BUTTON_2}
- {pin_num: '53', pin_signal: LCD_P24/PTC4/LLWU_P8/SPI0_SS/LPUART1_TX/TPM0_CH3, label: 'J1[7]/LCD_P24/POWER_STAT', identifier: LCD_P24;POWER_STAT}
- {pin_num: '43', pin_signal: LCD_P20/ADC0_SE14/PTC0/EXTRG_IN/USB_SOF_OUT/CMP0_OUT, label: 'J1[5]/LCD_P20/USB_SOF_OUT', identifier: LCD_P20;USB_SOF_OUT}
- {pin_num: '42', pin_signal: LCD_P15/PTB19/TPM2_CH1, label: 'J1[3]/LCD_P15', identifier: LCD_P15}
- {pin_num: '41', pin_signal: LCD_P14/PTB18/TPM2_CH0, label: 'J1[1]/LCD_P14', identifier: LCD_P14}
- {pin_num: '12', pin_signal: ADC0_DM3/ADC0_SE7a/PTE23/TPM2_CH1/UART2_RX/FXIO0_D7, label: 'J4[7]/DIFF_ADC1_DM'}
- {pin_num: '11', pin_signal: ADC0_DP3/ADC0_SE3/PTE22/TPM2_CH0/UART2_TX/FXIO0_D6, label: 'J4[5]/DIFF_ADC1_DP'}
- {pin_num: '10', pin_signal: LCD_P60/ADC0_DM0/ADC0_SE4a/PTE21/TPM1_CH1/LPUART0_RX/FXIO0_D5, label: 'J4[3]/DIFF_ADC0_DM/LCD_P60', identifier: LCD_P60}
- {pin_num: '9', pin_signal: LCD_P59/ADC0_DP0/ADC0_SE0/PTE20/TPM1_CH0/LPUART0_TX/FXIO0_D4, label: 'J4[1]/DIFF_ADC0_DP/LCD_P59', identifier: LCD_P59}
- {pin_num: '35', pin_signal: LCD_P0/ADC0_SE8/PTB0/LLWU_P5/I2C0_SCL/TPM1_CH0, label: 'J4[2]/A0/LCD_P0/NFC_IRQ', identifier: NFC_INT}
- {pin_num: '36', pin_signal: LCD_P1/ADC0_SE9/PTB1/I2C0_SDA/TPM1_CH1, label: 'J4[4]/A1/LCD_P1'}
- {pin_num: '37', pin_signal: LCD_P2/ADC0_SE12/PTB2/I2C0_SCL/TPM2_CH0, label: 'J4[6]/A2/LCD_P2/IN2B', identifier: IN2B}
- {pin_num: '38', pin_signal: LCD_P3/ADC0_SE13/PTB3/I2C0_SDA/TPM2_CH1, label: 'J4[8]/A3/LCD_P3'}
- {pin_num: '45', pin_signal: LCD_P22/ADC0_SE11/PTC2/I2C1_SDA/TPM0_CH1, label: 'J4[10]/A4/LCD_P22/I2C_PW_D'}
- {pin_num: '44', pin_signal: LCD_P21/ADC0_SE15/PTC1/LLWU_P6/RTC_CLKIN/I2C1_SCL/TPM0_CH0, label: 'J4[12]/A5/LCD_P21/I2C_PW_C'}
- {pin_num: '5', pin_signal: USB0_DP, label: 'J10[3]/USB_DP', identifier: USB0_DP}
- {pin_num: '6', pin_signal: USB0_DM, label: 'J10[2]/USB_DM', identifier: USB0_DM}
- {pin_num: '22', pin_signal: PTA0/TPM0_CH5/SWD_CLK, label: 'J11[4]/K32L2_SWD_CLK'}
- {pin_num: '25', pin_signal: PTA3/I2C1_SCL/TPM0_CH0/SWD_DIO, label: 'J11[2]/SWD_DIO_TGTMCU'}
- {pin_num: '32', pin_signal: EXTAL0/PTA18/LPUART1_RX/TPM_CLKIN0, label: EXTAL_32KHZ/PSAVE, identifier: EXTAL_32KHZ;PSAVE}
- {pin_num: '33', pin_signal: XTAL0/PTA19/LPUART1_TX/TPM_CLKIN1/LPTMR0_ALT1, label: XTAL_32KHZ, identifier: XTAL_32KHZ}
- {pin_num: '34', pin_signal: PTA20/RESET_b, label: 'J11[10]/J3[6]/RESET/SW2'}
- {pin_num: '46', pin_signal: LCD_P23/PTC3/LLWU_P7/SPI1_SCK/LPUART1_RX/TPM0_CH2/CLKOUT, label: SW3/LLWU_P7/LCD_P23/BATT_C, identifier: BATT_C}
- {pin_num: '58', pin_signal: LCD_P41/ADC0_SE5b/PTD1/SPI0_SCK/TPM0_CH1/FXIO0_D1, label: 'U2[9]/U10[9]/INT2_ACCEL/INT1_MAG/LCD_P41/SPI_RF_SCK', identifier: INT2_ACCEL;INT1_MAG;SIGFOX_SCK}
- {pin_num: '21', pin_signal: PTE25/TPM0_CH1/I2C0_SDA, label: 'U2[6]/U10[6]/I2C0_SDA/I2C_NFC_SDA', identifier: I2C0_SDA}
- {pin_num: '20', pin_signal: PTE24/TPM0_CH0/I2C0_SCL, label: 'U2[7]/U10[4]/I2C0_SCL/I2C_NFC_SCL', identifier: I2C0_SCL}
- {pin_num: '3', pin_signal: VDD17, label: P3V3_K32L2B}
- {pin_num: '13', pin_signal: VDDA, label: P3V3_K32L2B}
- {pin_num: '30', pin_signal: VDD94, label: P3V3_K32L2B}
- {pin_num: '4', pin_signal: VSS18, label: GND}
- {pin_num: '16', pin_signal: VSSA, label: GND}
- {pin_num: '31', pin_signal: VSS95, label: GND}
- {pin_num: '47', pin_signal: VSS136, label: GND}
- {pin_num: '7', pin_signal: VOUT33, label: VOUT33}
- {pin_num: '8', pin_signal: VREGIN, label: USB_REGIN, identifier: USB0_VREGIN}
- {pin_num: '15', pin_signal: VREFL, label: GND}
- {pin_num: '14', pin_signal: VREFH, label: 'J19[2]/P3V3_K32L2B'}
- {pin_num: '19', pin_signal: PTE31/TPM0_CH4, label: LED2/IN1A, identifier: IN1A}
- {pin_num: '48', pin_signal: VLL3, label: 'J12[1]/P3V3_K32L2B'}
- {pin_num: '49', pin_signal: VLL2/LCD_P4/PTC20, label: TP12/LCD_P4/DP_DC, identifier: DP_DC}
- {pin_num: '50', pin_signal: VLL1/LCD_P5/PTC21, label: TP10/LCD_P5/DP_LED, identifier: DP_BUSY}
- {pin_num: '51', pin_signal: VCAP2/LCD_P6/PTC22, label: LCD_P6/DP_RESET, identifier: DP_RST}
- {pin_num: '52', pin_signal: VCAP1/LCD_P39/PTC23, label: LCD_P39/RF_ACK, identifier: SIGFOX_ACK;SIGFOX_AK}
- {pin_num: '57', pin_signal: LCD_P40/PTD0/SPI0_SS/TPM0_CH0/FXIO0_D0, label: LCD-09_P40/SPI_RF_SS, identifier: LCD_P40;SIGFOX_CS}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

#include "fsl_common.h"
#include "fsl_port.h"
#include "fsl_gpio.h"
#include "pin_mux.h"

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitBootPins
 * Description   : Calls initialization functions.
 *
 * END ****************************************************************************************************************/
void BOARD_InitBootPins(void)
{
    BOARD_InitPins();
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_InitPins:
- options: {callFromInitBoot: 'true', coreID: core0, enableClock: 'true'}
- pin_list:
  - {pin_num: '20', peripheral: I2C0, signal: SCL, pin_signal: PTE24/TPM0_CH0/I2C0_SCL}
  - {pin_num: '21', peripheral: I2C0, signal: SDA, pin_signal: PTE25/TPM0_CH1/I2C0_SDA}
  - {pin_num: '57', peripheral: GPIOD, signal: 'GPIO, 0', pin_signal: LCD_P40/PTD0/SPI0_SS/TPM0_CH0/FXIO0_D0, identifier: SIGFOX_CS}
  - {pin_num: '58', peripheral: SPI0, signal: SCK, pin_signal: LCD_P41/ADC0_SE5b/PTD1/SPI0_SCK/TPM0_CH1/FXIO0_D1, identifier: SIGFOX_SCK}
  - {pin_num: '59', peripheral: SPI0, signal: MOSI, pin_signal: LCD_P42/PTD2/SPI0_MOSI/UART2_RX/TPM0_CH2/SPI0_MISO/FXIO0_D2, identifier: SIGFOX_SDO}
  - {pin_num: '60', peripheral: SPI0, signal: MISO, pin_signal: LCD_P43/PTD3/SPI0_MISO/UART2_TX/TPM0_CH3/SPI0_MOSI/FXIO0_D3, identifier: SIGFOX_SDI}
  - {pin_num: '61', peripheral: SPI1, signal: PCS0, pin_signal: LCD_P44/PTD4/LLWU_P14/SPI1_SS/UART2_RX/TPM0_CH4/FXIO0_D4, identifier: DP_CS}
  - {pin_num: '62', peripheral: SPI1, signal: SCK, pin_signal: LCD_P45/ADC0_SE6b/PTD5/SPI1_SCK/UART2_TX/TPM0_CH5/FXIO0_D5, identifier: DP_SCK}
  - {pin_num: '63', peripheral: SPI1, signal: MOSI, pin_signal: LCD_P46/ADC0_SE7b/PTD6/LLWU_P15/SPI1_MOSI/LPUART0_RX/SPI1_MISO/FXIO0_D6}
  - {pin_num: '64', peripheral: SPI1, signal: MISO, pin_signal: LCD_P47/PTD7/SPI1_MISO/LPUART0_TX/SPI1_MOSI/FXIO0_D7}
  - {pin_num: '35', peripheral: LLWU, signal: 'P, 5', pin_signal: LCD_P0/ADC0_SE8/PTB0/LLWU_P5/I2C0_SCL/TPM1_CH0, identifier: ''}
  - {pin_num: '1', peripheral: GPIOE, signal: 'GPIO, 0', pin_signal: LCD_P48/PTE0/CLKOUT32K/SPI1_MISO/LPUART1_TX/RTC_CLKOUT/CMP0_OUT/I2C1_SDA, identifier: NFC_RST,
    direction: OUTPUT}
  - {pin_num: '2', peripheral: GPIOE, signal: 'GPIO, 1', pin_signal: LCD_P49/PTE1/SPI1_MOSI/LPUART1_RX/SPI1_MISO/I2C1_SCL, identifier: SIGFOX_RST, direction: OUTPUT,
    gpio_init_state: 'false'}
  - {pin_num: '7', peripheral: USB0, signal: VOUT33, pin_signal: VOUT33}
  - {pin_num: '8', peripheral: USB0, signal: VREGIN, pin_signal: VREGIN}
  - {pin_num: '3', peripheral: SUPPLY, signal: 'VDD, 0', pin_signal: VDD17}
  - {pin_num: '4', peripheral: SUPPLY, signal: 'VSS, 0', pin_signal: VSS18}
  - {pin_num: '13', peripheral: SUPPLY, signal: 'VDDA, 0', pin_signal: VDDA}
  - {pin_num: '16', peripheral: SUPPLY, signal: 'VSSA, 0', pin_signal: VSSA}
  - {pin_num: '30', peripheral: SUPPLY, signal: 'VDD, 1', pin_signal: VDD94}
  - {pin_num: '31', peripheral: SUPPLY, signal: 'VSS, 1', pin_signal: VSS95}
  - {pin_num: '47', peripheral: SUPPLY, signal: 'VSS, 2', pin_signal: VSS136}
  - {pin_num: '34', peripheral: RCM, signal: RESET, pin_signal: PTA20/RESET_b}
  - {pin_num: '25', peripheral: SWD, signal: DIO, pin_signal: PTA3/I2C1_SCL/TPM0_CH0/SWD_DIO}
  - {pin_num: '44', peripheral: I2C1, signal: SCL, pin_signal: LCD_P21/ADC0_SE15/PTC1/LLWU_P6/RTC_CLKIN/I2C1_SCL/TPM0_CH0}
  - {pin_num: '45', peripheral: I2C1, signal: SDA, pin_signal: LCD_P22/ADC0_SE11/PTC2/I2C1_SDA/TPM0_CH1}
  - {pin_num: '46', peripheral: LLWU, signal: 'P, 7', pin_signal: LCD_P23/PTC3/LLWU_P7/SPI1_SCK/LPUART1_RX/TPM0_CH2/CLKOUT, identifier: ''}
  - {pin_num: '53', peripheral: LLWU, signal: 'P, 8', pin_signal: LCD_P24/PTC4/LLWU_P8/SPI0_SS/LPUART1_TX/TPM0_CH3}
  - {pin_num: '54', peripheral: LLWU, signal: 'P, 9', pin_signal: LCD_P25/PTC5/LLWU_P9/SPI0_SCK/LPTMR0_ALT2/CMP0_OUT}
  - {pin_num: '55', peripheral: LLWU, signal: 'P, 10', pin_signal: LCD_P26/CMP0_IN0/PTC6/LLWU_P10/SPI0_MOSI/EXTRG_IN/SPI0_MISO, identifier: BUTTON_2}
  - {pin_num: '29', peripheral: GPIOA, signal: 'GPIO, 13', pin_signal: PTA13/TPM1_CH1, direction: OUTPUT}
  - {pin_num: '37', peripheral: GPIOB, signal: 'GPIO, 2', pin_signal: LCD_P2/ADC0_SE12/PTB2/I2C0_SCL/TPM2_CH0, direction: OUTPUT}
  - {pin_num: '22', peripheral: SWD, signal: CLK, pin_signal: PTA0/TPM0_CH5/SWD_CLK}
  - {pin_num: '52', peripheral: GPIOC, signal: 'GPIO, 23', pin_signal: VCAP1/LCD_P39/PTC23, identifier: SIGFOX_AK, direction: INPUT, pull_enable: enable}
  - {pin_num: '51', peripheral: GPIOC, signal: 'GPIO, 22', pin_signal: VCAP2/LCD_P6/PTC22, direction: OUTPUT}
  - {pin_num: '50', peripheral: GPIOC, signal: 'GPIO, 21', pin_signal: VLL1/LCD_P5/PTC21, direction: INPUT}
  - {pin_num: '49', peripheral: GPIOC, signal: 'GPIO, 20', pin_signal: VLL2/LCD_P4/PTC20, direction: OUTPUT}
  - {pin_num: '35', peripheral: GPIOB, signal: 'GPIO, 0', pin_signal: LCD_P0/ADC0_SE8/PTB0/LLWU_P5/I2C0_SCL/TPM1_CH0, direction: INPUT, gpio_interrupt: kPORT_InterruptRisingEdge,
    pull_enable: enable}
  - {pin_num: '46', peripheral: GPIOC, signal: 'GPIO, 3', pin_signal: LCD_P23/PTC3/LLWU_P7/SPI1_SCK/LPUART1_RX/TPM0_CH2/CLKOUT, direction: INPUT, pull_enable: enable}
  - {pin_num: '53', peripheral: GPIOC, signal: 'GPIO, 4', pin_signal: LCD_P24/PTC4/LLWU_P8/SPI0_SS/LPUART1_TX/TPM0_CH3, identifier: POWER_STAT, direction: INPUT,
    pull_enable: enable}
  - {pin_num: '28', peripheral: GPIOA, signal: 'GPIO, 12', pin_signal: PTA12/TPM1_CH0, direction: OUTPUT}
  - {pin_num: '19', peripheral: GPIOE, signal: 'GPIO, 31', pin_signal: PTE31/TPM0_CH4, direction: OUTPUT}
  - {pin_num: '32', peripheral: GPIOA, signal: 'GPIO, 18', pin_signal: EXTAL0/PTA18/LPUART1_RX/TPM_CLKIN0, identifier: PSAVE, direction: OUTPUT}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_InitPins
 * Description   : Configures pin routing and optionally pin electrical features.
 *
 * END ****************************************************************************************************************/
void BOARD_InitPins(void)
{
    /* Port A Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortA);
    /* Port B Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortB);
    /* Port C Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortC);
    /* Port D Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortD);
    /* Port E Clock Gate Control: Clock enabled */
    CLOCK_EnableClock(kCLOCK_PortE);

    gpio_pin_config_t IN1B_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTA12 (pin 28)  */
    GPIO_PinInit(BOARD_INITPINS_IN1B_GPIO, BOARD_INITPINS_IN1B_PIN, &IN1B_config);

    gpio_pin_config_t IN2A_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTA13 (pin 29)  */
    GPIO_PinInit(BOARD_INITPINS_IN2A_GPIO, BOARD_INITPINS_IN2A_PIN, &IN2A_config);

    gpio_pin_config_t PSAVE_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTA18 (pin 32)  */
    GPIO_PinInit(BOARD_INITPINS_PSAVE_GPIO, BOARD_INITPINS_PSAVE_PIN, &PSAVE_config);

    gpio_pin_config_t NFC_INT_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTB0 (pin 35)  */
    GPIO_PinInit(BOARD_INITPINS_NFC_INT_GPIO, BOARD_INITPINS_NFC_INT_PIN, &NFC_INT_config);

    gpio_pin_config_t IN2B_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTB2 (pin 37)  */
    GPIO_PinInit(BOARD_INITPINS_IN2B_GPIO, BOARD_INITPINS_IN2B_PIN, &IN2B_config);

    gpio_pin_config_t BATT_C_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTC3 (pin 46)  */
    GPIO_PinInit(BOARD_INITPINS_BATT_C_GPIO, BOARD_INITPINS_BATT_C_PIN, &BATT_C_config);

    gpio_pin_config_t POWER_STAT_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTC4 (pin 53)  */
    GPIO_PinInit(BOARD_INITPINS_POWER_STAT_GPIO, BOARD_INITPINS_POWER_STAT_PIN, &POWER_STAT_config);

    gpio_pin_config_t DP_DC_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTC20 (pin 49)  */
    GPIO_PinInit(BOARD_INITPINS_DP_DC_GPIO, BOARD_INITPINS_DP_DC_PIN, &DP_DC_config);

    gpio_pin_config_t DP_BUSY_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTC21 (pin 50)  */
    GPIO_PinInit(BOARD_INITPINS_DP_BUSY_GPIO, BOARD_INITPINS_DP_BUSY_PIN, &DP_BUSY_config);

    gpio_pin_config_t DP_RST_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTC22 (pin 51)  */
    GPIO_PinInit(BOARD_INITPINS_DP_RST_GPIO, BOARD_INITPINS_DP_RST_PIN, &DP_RST_config);

    gpio_pin_config_t SIGFOX_AK_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTC23 (pin 52)  */
    GPIO_PinInit(BOARD_INITPINS_SIGFOX_AK_GPIO, BOARD_INITPINS_SIGFOX_AK_PIN, &SIGFOX_AK_config);

    gpio_pin_config_t NFC_RST_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTE0 (pin 1)  */
    GPIO_PinInit(BOARD_INITPINS_NFC_RST_GPIO, BOARD_INITPINS_NFC_RST_PIN, &NFC_RST_config);

    gpio_pin_config_t SIGFOX_RST_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTE1 (pin 2)  */
    GPIO_PinInit(BOARD_INITPINS_SIGFOX_RST_GPIO, BOARD_INITPINS_SIGFOX_RST_PIN, &SIGFOX_RST_config);

    gpio_pin_config_t IN1A_config = {
        .pinDirection = kGPIO_DigitalOutput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTE31 (pin 19)  */
    GPIO_PinInit(BOARD_INITPINS_IN1A_GPIO, BOARD_INITPINS_IN1A_PIN, &IN1A_config);

    /* PORTA0 (pin 22) is configured as SWD_CLK */
    PORT_SetPinMux(PORTA, 0U, kPORT_MuxAlt7);

    /* PORTA12 (pin 28) is configured as PTA12 */
    PORT_SetPinMux(BOARD_INITPINS_IN1B_PORT, BOARD_INITPINS_IN1B_PIN, kPORT_MuxAsGpio);

    /* PORTA13 (pin 29) is configured as PTA13 */
    PORT_SetPinMux(BOARD_INITPINS_IN2A_PORT, BOARD_INITPINS_IN2A_PIN, kPORT_MuxAsGpio);

    /* PORTA18 (pin 32) is configured as PTA18 */
    PORT_SetPinMux(BOARD_INITPINS_PSAVE_PORT, BOARD_INITPINS_PSAVE_PIN, kPORT_MuxAsGpio);

    /* PORTA20 (pin 34) is configured as RESET_b */
    PORT_SetPinMux(PORTA, 20U, kPORT_MuxAlt7);

    /* PORTA3 (pin 25) is configured as SWD_DIO */
    PORT_SetPinMux(PORTA, 3U, kPORT_MuxAlt7);

    /* PORTB0 (pin 35) is configured as LLWU_P5, PTB0 */
    PORT_SetPinMux(BOARD_INITPINS_NFC_INT_PORT, BOARD_INITPINS_NFC_INT_PIN, kPORT_MuxAsGpio);

    /* Interrupt configuration on PORTB0 (pin 35): Interrupt on rising edge */
    PORT_SetPinInterruptConfig(BOARD_INITPINS_NFC_INT_PORT, BOARD_INITPINS_NFC_INT_PIN, kPORT_InterruptRisingEdge);

    PORTB->PCR[0] = ((PORTB->PCR[0] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))

                     /* Pull Enable: Internal pullup or pulldown resistor is enabled on the corresponding pin. */
                     | (uint32_t)(PORT_PCR_PE_MASK));

    /* PORTB2 (pin 37) is configured as PTB2 */
    PORT_SetPinMux(BOARD_INITPINS_IN2B_PORT, BOARD_INITPINS_IN2B_PIN, kPORT_MuxAsGpio);

    /* PORTC1 (pin 44) is configured as I2C1_SCL */
    PORT_SetPinMux(PORTC, 1U, kPORT_MuxAlt2);

    /* PORTC2 (pin 45) is configured as I2C1_SDA */
    PORT_SetPinMux(PORTC, 2U, kPORT_MuxAlt2);

    /* PORTC20 (pin 49) is configured as PTC20 */
    PORT_SetPinMux(BOARD_INITPINS_DP_DC_PORT, BOARD_INITPINS_DP_DC_PIN, kPORT_MuxAsGpio);

    /* PORTC21 (pin 50) is configured as PTC21 */
    PORT_SetPinMux(BOARD_INITPINS_DP_BUSY_PORT, BOARD_INITPINS_DP_BUSY_PIN, kPORT_MuxAsGpio);

    /* PORTC22 (pin 51) is configured as PTC22 */
    PORT_SetPinMux(BOARD_INITPINS_DP_RST_PORT, BOARD_INITPINS_DP_RST_PIN, kPORT_MuxAsGpio);

    /* PORTC23 (pin 52) is configured as PTC23 */
    PORT_SetPinMux(BOARD_INITPINS_SIGFOX_AK_PORT, BOARD_INITPINS_SIGFOX_AK_PIN, kPORT_MuxAsGpio);

    PORTC->PCR[23] = ((PORTC->PCR[23] &
                       /* Mask bits to zero which are setting */
                       (~(PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))

                      /* Pull Enable: Internal pullup or pulldown resistor is enabled on the corresponding pin. */
                      | (uint32_t)(PORT_PCR_PE_MASK));

    /* PORTC3 (pin 46) is configured as LLWU_P7, PTC3 */
    PORT_SetPinMux(BOARD_INITPINS_BATT_C_PORT, BOARD_INITPINS_BATT_C_PIN, kPORT_MuxAsGpio);

    PORTC->PCR[3] = ((PORTC->PCR[3] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))

                     /* Pull Enable: Internal pullup or pulldown resistor is enabled on the corresponding pin. */
                     | (uint32_t)(PORT_PCR_PE_MASK));

    /* PORTC4 (pin 53) is configured as LLWU_P8, PTC4 */
    PORT_SetPinMux(BOARD_INITPINS_POWER_STAT_PORT, BOARD_INITPINS_POWER_STAT_PIN, kPORT_MuxAsGpio);

    PORTC->PCR[4] = ((PORTC->PCR[4] &
                      /* Mask bits to zero which are setting */
                      (~(PORT_PCR_PE_MASK | PORT_PCR_ISF_MASK)))

                     /* Pull Enable: Internal pullup or pulldown resistor is enabled on the corresponding pin. */
                     | (uint32_t)(PORT_PCR_PE_MASK));

    /* PORTC5 (pin 54) is configured as LLWU_P9 */
    PORT_SetPinMux(BOARD_INITPINS_INT1_ACCEL_PORT, BOARD_INITPINS_INT1_ACCEL_PIN, kPORT_MuxAsGpio);

    /* PORTC6 (pin 55) is configured as LLWU_P10 */
    PORT_SetPinMux(BOARD_INITPINS_BUTTON_2_PORT, BOARD_INITPINS_BUTTON_2_PIN, kPORT_MuxAsGpio);

    /* PORTD0 (pin 57) is configured as PTD0 */
    PORT_SetPinMux(BOARD_INITPINS_SIGFOX_CS_PORT, BOARD_INITPINS_SIGFOX_CS_PIN, kPORT_MuxAsGpio);

    /* PORTD1 (pin 58) is configured as SPI0_SCK */
    PORT_SetPinMux(BOARD_INITPINS_SIGFOX_SCK_PORT, BOARD_INITPINS_SIGFOX_SCK_PIN, kPORT_MuxAlt2);

    /* PORTD2 (pin 59) is configured as SPI0_MOSI */
    PORT_SetPinMux(BOARD_INITPINS_SIGFOX_SDO_PORT, BOARD_INITPINS_SIGFOX_SDO_PIN, kPORT_MuxAlt2);

    /* PORTD3 (pin 60) is configured as SPI0_MISO */
    PORT_SetPinMux(BOARD_INITPINS_SIGFOX_SDI_PORT, BOARD_INITPINS_SIGFOX_SDI_PIN, kPORT_MuxAlt2);

    /* PORTD4 (pin 61) is configured as SPI1_SS */
    PORT_SetPinMux(BOARD_INITPINS_DP_CS_PORT, BOARD_INITPINS_DP_CS_PIN, kPORT_MuxAlt2);

    /* PORTD5 (pin 62) is configured as SPI1_SCK */
    PORT_SetPinMux(BOARD_INITPINS_DP_SCK_PORT, BOARD_INITPINS_DP_SCK_PIN, kPORT_MuxAlt2);

    /* PORTD6 (pin 63) is configured as SPI1_MOSI */
    PORT_SetPinMux(BOARD_INITPINS_DP_DIN_PORT, BOARD_INITPINS_DP_DIN_PIN, kPORT_MuxAlt2);

    /* PORTD7 (pin 64) is configured as SPI1_MISO */
    PORT_SetPinMux(PORTD, 7U, kPORT_MuxAlt2);

    /* PORTE0 (pin 1) is configured as PTE0 */
    PORT_SetPinMux(BOARD_INITPINS_NFC_RST_PORT, BOARD_INITPINS_NFC_RST_PIN, kPORT_MuxAsGpio);

    /* PORTE1 (pin 2) is configured as PTE1 */
    PORT_SetPinMux(BOARD_INITPINS_SIGFOX_RST_PORT, BOARD_INITPINS_SIGFOX_RST_PIN, kPORT_MuxAsGpio);

    /* PORTE24 (pin 20) is configured as I2C0_SCL */
    PORT_SetPinMux(BOARD_INITPINS_I2C0_SCL_PORT, BOARD_INITPINS_I2C0_SCL_PIN, kPORT_MuxAlt5);

    /* PORTE25 (pin 21) is configured as I2C0_SDA */
    PORT_SetPinMux(BOARD_INITPINS_I2C0_SDA_PORT, BOARD_INITPINS_I2C0_SDA_PIN, kPORT_MuxAlt5);

    /* PORTE31 (pin 19) is configured as PTE31 */
    PORT_SetPinMux(BOARD_INITPINS_IN1A_PORT, BOARD_INITPINS_IN1A_PIN, kPORT_MuxAsGpio);
}

/* clang-format off */
/*
 * TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
BOARD_DisablePins:
- options: {callFromInitBoot: 'false', coreID: core0, enableClock: 'false'}
- pin_list:
  - {pin_num: '35', peripheral: LLWU, signal: 'P, 5', pin_signal: LCD_P0/ADC0_SE8/PTB0/LLWU_P5/I2C0_SCL/TPM1_CH0, identifier: ''}
  - {pin_num: '7', peripheral: USB0, signal: VOUT33, pin_signal: VOUT33}
  - {pin_num: '8', peripheral: USB0, signal: VREGIN, pin_signal: VREGIN}
  - {pin_num: '3', peripheral: SUPPLY, signal: 'VDD, 0', pin_signal: VDD17}
  - {pin_num: '4', peripheral: SUPPLY, signal: 'VSS, 0', pin_signal: VSS18}
  - {pin_num: '13', peripheral: SUPPLY, signal: 'VDDA, 0', pin_signal: VDDA}
  - {pin_num: '16', peripheral: SUPPLY, signal: 'VSSA, 0', pin_signal: VSSA}
  - {pin_num: '30', peripheral: SUPPLY, signal: 'VDD, 1', pin_signal: VDD94}
  - {pin_num: '31', peripheral: SUPPLY, signal: 'VSS, 1', pin_signal: VSS95}
  - {pin_num: '47', peripheral: SUPPLY, signal: 'VSS, 2', pin_signal: VSS136}
  - {pin_num: '34', peripheral: RCM, signal: RESET, pin_signal: PTA20/RESET_b}
  - {pin_num: '25', peripheral: SWD, signal: DIO, pin_signal: PTA3/I2C1_SCL/TPM0_CH0/SWD_DIO}
  - {pin_num: '46', peripheral: LLWU, signal: 'P, 7', pin_signal: LCD_P23/PTC3/LLWU_P7/SPI1_SCK/LPUART1_RX/TPM0_CH2/CLKOUT}
  - {pin_num: '53', peripheral: LLWU, signal: 'P, 8', pin_signal: LCD_P24/PTC4/LLWU_P8/SPI0_SS/LPUART1_TX/TPM0_CH3, identifier: POWER_STAT}
  - {pin_num: '54', peripheral: LLWU, signal: 'P, 9', pin_signal: LCD_P25/PTC5/LLWU_P9/SPI0_SCK/LPTMR0_ALT2/CMP0_OUT}
  - {pin_num: '55', peripheral: LLWU, signal: 'P, 10', pin_signal: LCD_P26/CMP0_IN0/PTC6/LLWU_P10/SPI0_MOSI/EXTRG_IN/SPI0_MISO, identifier: BUTTON_2}
  - {pin_num: '22', peripheral: SWD, signal: CLK, pin_signal: PTA0/TPM0_CH5/SWD_CLK}
  - {pin_num: '35', peripheral: GPIOB, signal: 'GPIO, 0', pin_signal: LCD_P0/ADC0_SE8/PTB0/LLWU_P5/I2C0_SCL/TPM1_CH0, direction: INPUT, gpio_interrupt: kPORT_InterruptRisingEdge}
  - {pin_num: '46', peripheral: GPIOC, signal: 'GPIO, 3', pin_signal: LCD_P23/PTC3/LLWU_P7/SPI1_SCK/LPUART1_RX/TPM0_CH2/CLKOUT, identifier: ''}
  - {pin_num: '53', peripheral: GPIOC, signal: 'GPIO, 4', pin_signal: LCD_P24/PTC4/LLWU_P8/SPI0_SS/LPUART1_TX/TPM0_CH3}
  - {pin_num: '19', peripheral: n/a, signal: disabled, pin_signal: PTE31/TPM0_CH4, identifier: ''}
  - {pin_num: '20', peripheral: n/a, signal: disabled, pin_signal: PTE24/TPM0_CH0/I2C0_SCL, identifier: ''}
  - {pin_num: '21', peripheral: n/a, signal: disabled, pin_signal: PTE25/TPM0_CH1/I2C0_SDA}
  - {pin_num: '28', peripheral: n/a, signal: disabled, pin_signal: PTA12/TPM1_CH0, identifier: ''}
  - {pin_num: '29', peripheral: n/a, signal: disabled, pin_signal: PTA13/TPM1_CH1, identifier: ''}
  - {pin_num: '1', peripheral: LCD, signal: 'P, 48', pin_signal: LCD_P48/PTE0/CLKOUT32K/SPI1_MISO/LPUART1_TX/RTC_CLKOUT/CMP0_OUT/I2C1_SDA}
  - {pin_num: '2', peripheral: LCD, signal: 'P, 49', pin_signal: LCD_P49/PTE1/SPI1_MOSI/LPUART1_RX/SPI1_MISO/I2C1_SCL}
  - {pin_num: '37', peripheral: ADC0, signal: 'SE, 12', pin_signal: LCD_P2/ADC0_SE12/PTB2/I2C0_SCL/TPM2_CH0, identifier: ''}
  - {pin_num: '44', peripheral: ADC0, signal: 'SE, 15', pin_signal: LCD_P21/ADC0_SE15/PTC1/LLWU_P6/RTC_CLKIN/I2C1_SCL/TPM0_CH0}
  - {pin_num: '45', peripheral: ADC0, signal: 'SE, 11', pin_signal: LCD_P22/ADC0_SE11/PTC2/I2C1_SDA/TPM0_CH1}
  - {pin_num: '49', peripheral: LCD, signal: 'P, 4', pin_signal: VLL2/LCD_P4/PTC20}
  - {pin_num: '50', peripheral: LCD, signal: 'P, 5', pin_signal: VLL1/LCD_P5/PTC21, identifier: ''}
  - {pin_num: '52', peripheral: LCD, signal: 'P, 39', pin_signal: VCAP1/LCD_P39/PTC23}
  - {pin_num: '57', peripheral: LCD, signal: 'P, 40', pin_signal: LCD_P40/PTD0/SPI0_SS/TPM0_CH0/FXIO0_D0}
  - {pin_num: '58', peripheral: ADC0, signal: 'SE, 5b', pin_signal: LCD_P41/ADC0_SE5b/PTD1/SPI0_SCK/TPM0_CH1/FXIO0_D1}
  - {pin_num: '59', peripheral: LCD, signal: 'P, 42', pin_signal: LCD_P42/PTD2/SPI0_MOSI/UART2_RX/TPM0_CH2/SPI0_MISO/FXIO0_D2}
  - {pin_num: '60', peripheral: LCD, signal: 'P, 43', pin_signal: LCD_P43/PTD3/SPI0_MISO/UART2_TX/TPM0_CH3/SPI0_MOSI/FXIO0_D3}
  - {pin_num: '61', peripheral: LCD, signal: 'P, 44', pin_signal: LCD_P44/PTD4/LLWU_P14/SPI1_SS/UART2_RX/TPM0_CH4/FXIO0_D4}
  - {pin_num: '62', peripheral: ADC0, signal: 'SE, 6b', pin_signal: LCD_P45/ADC0_SE6b/PTD5/SPI1_SCK/UART2_TX/TPM0_CH5/FXIO0_D5}
  - {pin_num: '63', peripheral: ADC0, signal: 'SE, 7b', pin_signal: LCD_P46/ADC0_SE7b/PTD6/LLWU_P15/SPI1_MOSI/LPUART0_RX/SPI1_MISO/FXIO0_D6, identifier: ''}
  - {pin_num: '64', peripheral: LCD, signal: 'P, 47', pin_signal: LCD_P47/PTD7/SPI1_MISO/LPUART0_TX/SPI1_MOSI/FXIO0_D7}
  - {pin_num: '51', peripheral: LCD, signal: 'P, 6', pin_signal: VCAP2/LCD_P6/PTC22, identifier: ''}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS ***********
 */
/* clang-format on */

/* FUNCTION ************************************************************************************************************
 *
 * Function Name : BOARD_DisablePins
 * Description   : Disable output pins before going to sleep mode
 *
 * END ****************************************************************************************************************/
void BOARD_DisablePins(void)
{

    gpio_pin_config_t NFC_INT_config = {
        .pinDirection = kGPIO_DigitalInput,
        .outputLogic = 0U
    };
    /* Initialize GPIO functionality on pin PTB0 (pin 35)  */
    GPIO_PinInit(BOARD_DISABLEPINS_NFC_INT_GPIO, BOARD_DISABLEPINS_NFC_INT_PIN, &NFC_INT_config);

    /* PORTA0 (pin 22) is configured as SWD_CLK */
    PORT_SetPinMux(PORTA, 0U, kPORT_MuxAlt7);

    /* PORTA12 (pin 28) is disabled */
    PORT_SetPinMux(PORTA, 12U, kPORT_PinDisabledOrAnalog);

    /* PORTA13 (pin 29) is disabled */
    PORT_SetPinMux(PORTA, 13U, kPORT_PinDisabledOrAnalog);

    /* PORTA20 (pin 34) is configured as RESET_b */
    PORT_SetPinMux(PORTA, 20U, kPORT_MuxAlt7);

    /* PORTA3 (pin 25) is configured as SWD_DIO */
    PORT_SetPinMux(PORTA, 3U, kPORT_MuxAlt7);

    /* PORTB0 (pin 35) is configured as LLWU_P5, PTB0 */
    PORT_SetPinMux(BOARD_DISABLEPINS_NFC_INT_PORT, BOARD_DISABLEPINS_NFC_INT_PIN, kPORT_MuxAsGpio);

    /* Interrupt configuration on PORTB0 (pin 35): Interrupt on rising edge */
    PORT_SetPinInterruptConfig(BOARD_DISABLEPINS_NFC_INT_PORT, BOARD_DISABLEPINS_NFC_INT_PIN, kPORT_InterruptRisingEdge);

    /* PORTB2 (pin 37) is configured as ADC0_SE12 */
    PORT_SetPinMux(PORTB, 2U, kPORT_PinDisabledOrAnalog);

    /* PORTC1 (pin 44) is configured as ADC0_SE15 */
    PORT_SetPinMux(PORTC, 1U, kPORT_PinDisabledOrAnalog);

    /* PORTC2 (pin 45) is configured as ADC0_SE11 */
    PORT_SetPinMux(PORTC, 2U, kPORT_PinDisabledOrAnalog);

    /* PORTC20 (pin 49) is configured as LCD_P4 */
    PORT_SetPinMux(BOARD_DISABLEPINS_DP_DC_PORT, BOARD_DISABLEPINS_DP_DC_PIN, kPORT_PinDisabledOrAnalog);

    /* PORTC21 (pin 50) is configured as LCD_P5 */
    PORT_SetPinMux(PORTC, 21U, kPORT_PinDisabledOrAnalog);

    /* PORTC22 (pin 51) is configured as LCD_P6 */
    PORT_SetPinMux(PORTC, 22U, kPORT_PinDisabledOrAnalog);

    /* PORTC23 (pin 52) is configured as LCD_P39 */
    PORT_SetPinMux(PORTC, 23U, kPORT_PinDisabledOrAnalog);

    /* PORTC3 (pin 46) is configured as LLWU_P7, PTC3 */
    PORT_SetPinMux(BOARD_DISABLEPINS_BATT_C_PORT, BOARD_DISABLEPINS_BATT_C_PIN, kPORT_MuxAsGpio);

    /* PORTC4 (pin 53) is configured as LLWU_P8, PTC4 */
    PORT_SetPinMux(BOARD_DISABLEPINS_POWER_STAT_PORT, BOARD_DISABLEPINS_POWER_STAT_PIN, kPORT_MuxAsGpio);

    /* PORTC5 (pin 54) is configured as LLWU_P9 */
    PORT_SetPinMux(BOARD_DISABLEPINS_INT1_ACCEL_PORT, BOARD_DISABLEPINS_INT1_ACCEL_PIN, kPORT_MuxAsGpio);

    /* PORTC6 (pin 55) is configured as LLWU_P10 */
    PORT_SetPinMux(BOARD_DISABLEPINS_BUTTON_2_PORT, BOARD_DISABLEPINS_BUTTON_2_PIN, kPORT_MuxAsGpio);

    /* PORTD0 (pin 57) is configured as LCD_P40 */
    PORT_SetPinMux(PORTD, 0U, kPORT_PinDisabledOrAnalog);

    /* PORTD1 (pin 58) is configured as ADC0_SE5b */
    PORT_SetPinMux(PORTD, 1U, kPORT_PinDisabledOrAnalog);

    /* PORTD2 (pin 59) is configured as LCD_P42 */
    PORT_SetPinMux(PORTD, 2U, kPORT_PinDisabledOrAnalog);

    /* PORTD3 (pin 60) is configured as LCD_P43 */
    PORT_SetPinMux(PORTD, 3U, kPORT_PinDisabledOrAnalog);

    /* PORTD4 (pin 61) is configured as LCD_P44 */
    PORT_SetPinMux(PORTD, 4U, kPORT_PinDisabledOrAnalog);

    /* PORTD5 (pin 62) is configured as ADC0_SE6b */
    PORT_SetPinMux(PORTD, 5U, kPORT_PinDisabledOrAnalog);

    /* PORTD6 (pin 63) is configured as ADC0_SE7b */
    PORT_SetPinMux(PORTD, 6U, kPORT_PinDisabledOrAnalog);

    /* PORTD7 (pin 64) is configured as LCD_P47 */
    PORT_SetPinMux(PORTD, 7U, kPORT_PinDisabledOrAnalog);

    /* PORTE0 (pin 1) is configured as LCD_P48 */
    PORT_SetPinMux(PORTE, 0U, kPORT_PinDisabledOrAnalog);

    /* PORTE1 (pin 2) is configured as LCD_P49 */
    PORT_SetPinMux(PORTE, 1U, kPORT_PinDisabledOrAnalog);

    /* PORTE24 (pin 20) is disabled */
    PORT_SetPinMux(PORTE, 24U, kPORT_PinDisabledOrAnalog);

    /* PORTE25 (pin 21) is disabled */
    PORT_SetPinMux(BOARD_DISABLEPINS_I2C0_SDA_PORT, BOARD_DISABLEPINS_I2C0_SDA_PIN, kPORT_PinDisabledOrAnalog);

    /* PORTE31 (pin 19) is disabled */
    PORT_SetPinMux(PORTE, 31U, kPORT_PinDisabledOrAnalog);
}
/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/
