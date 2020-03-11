/*
 * power_mode_switch.c
 *
 *  Created on: Mar 7, 2020
 *      Author: nxf46245
 */

#include "fsl_common.h"
#include "fsl_smc.h"
#include "fsl_llwu.h"
#include "fsl_rcm.h"
#include "fsl_lptmr.h"
#include "fsl_port.h"
#include "power_mode_switch.h"
#include "board.h"
#include "fsl_debug_console.h"

#include "pin_mux.h"
#include "fsl_lpuart.h"
#include "fsl_pmc.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define LLWU_WAKEUP_NFC_PIN 5U
#define LLWU_WAKEUP_BATTERY_PIN 7U
#define LLWU_WAKEUP_POWERSTAT_PIN 8U
#define LLWU_WAKEUP_PIN_TYPE kLLWU_ExternalPinRisingEdge
#define APP_WAKEUP_IRQ_TYPE kPORT_InterruptFallingEdge

/*******************************************************************************
 * Variables
 ******************************************************************************/
//static uint8_t s_wakeupTimeout;            /* Wakeup timeout. (Unit: Second) */
//static app_wakeup_source_t s_wakeupSource; /* Wakeup source.                 */

/*******************************************************************************
 * Code
 ******************************************************************************/
static void APP_InitDefaultDebugConsole(void)
{
//    uint32_t uartDefaultClkSrcFreq;
//    CLOCK_SetLpuart0Clock(APP_DEBUG_UART_DEFAULT_CLKSRC);
//    uartDefaultClkSrcFreq = CLOCK_GetFreq(APP_DEBUG_UART_DEFAULT_CLKSRC_NAME);
//    DbgConsole_Init(BOARD_DEBUG_UART_INSTANCE, APP_DEBUG_UART_BAUDRATE, BOARD_DEBUG_UART_TYPE, uartDefaultClkSrcFreq);
}

static void APP_InitVlprDebugConsole(void)
{
//    uint32_t uartVlprClkSrcFreq;
//    CLOCK_SetLpuart0Clock(APP_DEBUG_UART_VLPR_CLKSRC);
//    uartVlprClkSrcFreq = CLOCK_GetFreq(APP_DEBUG_UART_VLPR_CLKSRC_NAME);
//    DbgConsole_Init(BOARD_DEBUG_UART_INSTANCE, APP_DEBUG_UART_BAUDRATE, BOARD_DEBUG_UART_TYPE, uartVlprClkSrcFreq);
}


void APP_PowerPreSwitchHook(smc_power_state_t originPowerState, app_power_mode_t targetMode)
{
//    /* Wait for debug console output finished. */
//    while (!(kLPUART_TransmissionCompleteFlag & LPUART_GetStatusFlags((LPUART_Type *)BOARD_DEBUG_UART_BASEADDR)))
//    {
//    }
//    DbgConsole_Deinit();

    if ((kAPP_PowerModeRun != targetMode) && (kAPP_PowerModeVlpr != targetMode))
    {
        /*
         * Set pin for current leakage.
         * Debug console RX pin: Set to pinmux to disable.
         * Debug console TX pin: Don't need to change.
         */
//        PORT_SetPinMux(DEBUG_CONSOLE_RX_PORT, DEBUG_CONSOLE_RX_PIN, kPORT_PinDisabledOrAnalog);
    }
}

void APP_PowerPostSwitchHook(smc_power_state_t originPowerState, app_power_mode_t targetMode)
{
    smc_power_state_t powerState = SMC_GetPowerModeState(SMC);

    /*
     * For some other platforms, if enter LLS mode from VLPR mode, when wakeup, the
     * power mode is VLPR. But for some platforms, if enter LLS mode from VLPR mode,
     * when wakeup, the power mode is RUN. In this case, the clock setting is still
     * VLPR mode setting, so change to RUN mode setting here.
     */
    if ((kSMC_PowerStateVlpr == originPowerState) && (kSMC_PowerStateRun == powerState))
    {
        APP_SetClockRunFromVlpr();
    }

    if ((kAPP_PowerModeRun != targetMode) && (kAPP_PowerModeVlpr != targetMode))
    {
        /*
         * Debug console RX pin is set to disable for current leakage, nee to re-configure pinmux.
         * Debug console TX pin: Don't need to change.
         */
//        PORT_SetPinMux(DEBUG_CONSOLE_RX_PORT, DEBUG_CONSOLE_RX_PIN, DEBUG_CONSOLE_RX_PINMUX);
    }

    /* Set debug console clock source. */
    if (kSMC_PowerStateVlpr == powerState)
    {
        APP_InitVlprDebugConsole();
    }
    else
    {
        APP_InitDefaultDebugConsole();
    }
}

/*!
 * @brief LLWU interrupt handler.
 */
void LLWU_IRQHandler(void)
{
//    /* If wakeup by LPTMR. */
//    if (LLWU_GetInternalWakeupModuleFlag(LLWU, LLWU_LPTMR_IDX))
//    {
//        LPTMR_DisableInterrupts(LPTMR0, kLPTMR_TimerInterruptEnable);
//        LPTMR_ClearStatusFlags(LPTMR0, kLPTMR_TimerCompareFlag);
//        LPTMR_StopTimer(LPTMR0);
//    }

    /* If wakeup by NFC pin. */
    if (LLWU_GetExternalWakeupPinFlag(LLWU, LLWU_WAKEUP_NFC_PIN))
    {
        PORT_SetPinInterruptConfig(BOARD_INITPINS_NFC_INT_PORT, BOARD_INITPINS_NFC_INT_PIN, kPORT_InterruptOrDMADisabled);
        PORT_ClearPinsInterruptFlags(BOARD_INITPINS_NFC_INT_PORT, (1U << BOARD_INITPINS_NFC_INT_PIN));
        LLWU_ClearExternalWakeupPinFlag(LLWU, LLWU_WAKEUP_NFC_PIN);
    }
}

//void LPTMR0_IRQHandler(void)
//{
//    if (kLPTMR_TimerInterruptEnable & LPTMR_GetEnabledInterrupts(LPTMR0))
//    {
//        LPTMR_DisableInterrupts(LPTMR0, kLPTMR_TimerInterruptEnable);
//        LPTMR_ClearStatusFlags(LPTMR0, kLPTMR_TimerCompareFlag);
//        LPTMR_StopTimer(LPTMR0);
//    }
//}

//void PORTA_IRQHandler(void)
//{
//    if ((1U << BOARD_INITPINS_NFC_INT_PIN) & PORT_GetPinsInterruptFlags(BOARD_INITPINS_NFC_INT_PORT))
//    {
//        /* Disable interrupt. */
//        PORT_SetPinInterruptConfig(BOARD_INITPINS_NFC_INT_PORT, BOARD_INITPINS_NFC_INT_PIN, kPORT_InterruptOrDMADisabled);
//        PORT_ClearPinsInterruptFlags(BOARD_INITPINS_NFC_INT_PORT, (1U << BOARD_INITPINS_NFC_INT_PIN));
//    }
//}

// /*!
//  * @brief Get input from user about wakeup timeout
//  */
// static uint8_t APP_GetWakeupTimeout(void)
// {
//     uint8_t timeout;

//     while (1)
//     {
//         PRINTF("Select the wake up timeout in seconds.\r\n");
//         PRINTF("The allowed range is 1s ~ 9s.\r\n");
//         PRINTF("Eg. enter 5 to wake up in 5 seconds.\r\n");
//         PRINTF("\r\nWaiting for input timeout value...\r\n\r\n");

//         timeout = GETCHAR();
//         PRINTF("%c\r\n", timeout);
//         if ((timeout > '0') && (timeout <= '9'))
//         {
//             return timeout - '0';
//         }
//         PRINTF("Wrong value!\r\n");
//     }
// }

// /* Get wakeup source by user input. */
// static app_wakeup_source_t APP_GetWakeupSource(void)
// {
//     uint8_t ch;

//     while (1)
//     {
//         PRINTF("Select the wake up source:\r\n");
//         PRINTF("Press T for LPTMR - Low Power Timer\r\n");
// //        PRINTF("Press S for switch/button %s. \r\n", APP_WAKEUP_BUTTON_NAME);

//         PRINTF("\r\nWaiting for key press..\r\n\r\n");

//         ch = GETCHAR();

//         if ((ch >= 'a') && (ch <= 'z'))
//         {
//             ch -= 'a' - 'A';
//         }

//         if (ch == 'T')
//         {
//             return kAPP_WakeupSourceLptmr;
//         }
//         else if (ch == 'S')
//         {
//             return kAPP_WakeupSourcePin;
//         }
//         else
//         {
//             PRINTF("Wrong value!\r\n");
//         }
//     }
// }

// /* Get wakeup timeout and wakeup source. */
// void APP_GetWakeupConfig(app_power_mode_t targetMode)
// {
//     /* Get wakeup source by user input. */
//     if (targetMode == kAPP_PowerModeVlls0)
//     {
//         /* In VLLS0 mode, the LPO is disabled, LPTMR could not work. */
//         PRINTF("Not support LPTMR wakeup because LPO is disabled in VLLS0 mode.\r\n");
//         s_wakeupSource = kAPP_WakeupSourcePin;
//     }
//     else
//     {
//         /* Get wakeup source by user input. */
//         s_wakeupSource = APP_GetWakeupSource();
//     }

//     if (kAPP_WakeupSourceLptmr == s_wakeupSource)
//     {
//         /* Wakeup source is LPTMR, user should input wakeup timeout value. */
//         s_wakeupTimeout = APP_GetWakeupTimeout();
//         PRINTF("Will wakeup in %d seconds.\r\n", s_wakeupTimeout);
//     }
//     else
//     {
// //        PRINTF("Press %s to wake up.\r\n", APP_WAKEUP_BUTTON_NAME);
//     }
// }

void APP_SetWakeupConfig(app_power_mode_t targetMode)
{
    // /* Set LPTMR timeout value. */
    // if (kAPP_WakeupSourceLptmr == s_wakeupSource)
    // {
    //     LPTMR_SetTimerPeriod(LPTMR0, (LPO_CLK_FREQ * s_wakeupTimeout) - 1U);
    //     LPTMR_StartTimer(LPTMR0);
    // }

    // /* Set the wakeup module. */
    // if (kAPP_WakeupSourceLptmr == s_wakeupSource)
    // {
    //     LPTMR_EnableInterrupts(LPTMR0, kLPTMR_TimerInterruptEnable);
    // }
    // else
    // {
    //     PORT_SetPinInterruptConfig(BOARD_INITPINS_NFC_INT_PORT, BOARD_INITPINS_NFC_INT_PIN, APP_WAKEUP_IRQ_TYPE);
    // }

    PORT_SetPinInterruptConfig(BOARD_INITPINS_NFC_INT_PORT, BOARD_INITPINS_NFC_INT_PIN, APP_WAKEUP_IRQ_TYPE);

    /* If targetMode is VLLS/LLS, setup LLWU. */
    if ((kAPP_PowerModeWait != targetMode) && (kAPP_PowerModeVlpw != targetMode) &&
        (kAPP_PowerModeVlps != targetMode) && (kAPP_PowerModeStop != targetMode))
    {
//        if (kAPP_WakeupSourceLptmr == s_wakeupSource)
//        {
//            LLWU_EnableInternalModuleInterruptWakup(LLWU, LLWU_LPTMR_IDX, true);
//        }
//        else
//        {
//            LLWU_SetExternalWakeupPinMode(LLWU, LLWU_WAKEUP_NFC_PIN, LLWU_WAKEUP_PIN_TYPE);
//        }
        LLWU_SetExternalWakeupPinMode(LLWU, LLWU_WAKEUP_NFC_PIN, LLWU_WAKEUP_PIN_TYPE);
        NVIC_EnableIRQ(LLWU_IRQn);
    }
}

void APP_ShowPowerMode(smc_power_state_t powerMode)
{
    switch (powerMode)
    {
        case kSMC_PowerStateRun:
            PRINTF("    Power mode: RUN\r\n");
            break;
        case kSMC_PowerStateVlpr:
            PRINTF("    Power mode: VLPR\r\n");
            break;
        default:
            PRINTF("    Power mode wrong\r\n");
            break;
    }
}

/*
 * Check whether could switch to target power mode from current mode.
 * Return true if could switch, return false if could not switch.
 */
bool APP_CheckPowerMode(smc_power_state_t curPowerState, app_power_mode_t targetPowerMode)
{
    bool modeValid = true;

    /*
     * Check wether the mode change is allowed.
     *
     * 1. If current mode is HSRUN mode, the target mode must be RUN mode.
     * 2. If current mode is RUN mode, the target mode must not be VLPW mode.
     * 3. If current mode is VLPR mode, the target mode must not be HSRUN/WAIT/STOP mode.
     * 4. If already in the target mode.
     */
    switch (curPowerState)
    {
        case kSMC_PowerStateRun:
            if (kAPP_PowerModeVlpw == targetPowerMode)
            {
                PRINTF("Could not enter VLPW mode from RUN mode.\r\n");
                modeValid = false;
            }
            break;

        case kSMC_PowerStateVlpr:
            if ((kAPP_PowerModeWait == targetPowerMode) || (kAPP_PowerModeStop == targetPowerMode))
            {
                PRINTF("Could not enter HSRUN/STOP/WAIT modes from VLPR mode.\r\n");
                modeValid = false;
            }
            break;
        default:
            PRINTF("Wrong power state.\r\n");
            modeValid = false;
            break;
    }

    if (!modeValid)
    {
        return false;
    }

    /* Don't need to change power mode if current mode is already the target mode. */
    if (((kAPP_PowerModeRun == targetPowerMode) && (kSMC_PowerStateRun == curPowerState)) ||
        ((kAPP_PowerModeVlpr == targetPowerMode) && (kSMC_PowerStateVlpr == curPowerState)))
    {
        PRINTF("Already in the target power mode.\r\n");
        return false;
    }

    return true;
}

/*
 * Power mode switch.
 */
void APP_PowerModeSwitch(smc_power_state_t curPowerState, app_power_mode_t targetPowerMode)
{
    smc_power_mode_vlls_config_t vlls_config;
    vlls_config.enablePorDetectInVlls0 = true;

    switch (targetPowerMode)
    {
        case kAPP_PowerModeVlpr:
            APP_SetClockVlpr();
            SMC_SetPowerModeVlpr(SMC);
            while (kSMC_PowerStateVlpr != SMC_GetPowerModeState(SMC))
            {
            }
            break;

        case kAPP_PowerModeRun:

            /* Power mode change. */
            SMC_SetPowerModeRun(SMC);
            while (kSMC_PowerStateRun != SMC_GetPowerModeState(SMC))
            {
            }

            /* If enter RUN from VLPR, change clock after the power mode change. */
            if (kSMC_PowerStateVlpr == curPowerState)
            {
                APP_SetClockRunFromVlpr();
            }
            break;

        case kAPP_PowerModeWait:
            SMC_PreEnterWaitModes();
            SMC_SetPowerModeWait(SMC);
            SMC_PostExitWaitModes();
            break;

        case kAPP_PowerModeStop:
            SMC_PreEnterStopModes();
            SMC_SetPowerModeStop(SMC, kSMC_PartialStop);
            SMC_PostExitStopModes();
            break;

        case kAPP_PowerModeVlpw:
            SMC_PreEnterWaitModes();
            SMC_SetPowerModeVlpw(SMC);
            SMC_PostExitWaitModes();
            break;

        case kAPP_PowerModeVlps:
            SMC_PreEnterStopModes();
            SMC_SetPowerModeVlps(SMC);
            SMC_PostExitStopModes();
            break;

        case kAPP_PowerModeLls:
            SMC_PreEnterStopModes();
            SMC_SetPowerModeLls(SMC);
            SMC_PostExitStopModes();
            break;

        case kAPP_PowerModeVlls0:
            vlls_config.subMode = kSMC_StopSub0;
            SMC_PreEnterStopModes();
            SMC_SetPowerModeVlls(SMC, &vlls_config);
            SMC_PostExitStopModes();
            break;

        case kAPP_PowerModeVlls1:
            vlls_config.subMode = kSMC_StopSub1;
            SMC_PreEnterStopModes();
            SMC_SetPowerModeVlls(SMC, &vlls_config);
            SMC_PostExitStopModes();
            break;

        case kAPP_PowerModeVlls3:
            vlls_config.subMode = kSMC_StopSub3;
            SMC_PreEnterStopModes();
            SMC_SetPowerModeVlls(SMC, &vlls_config);
            SMC_PostExitStopModes();
            break;

        default:
            PRINTF("Wrong value");
            break;
    }
}
