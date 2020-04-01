/*
 * power_mode_switch.c
 *
 *  Created on: Mar 7, 2020
 *      Author: nxf46245
 */
#include <stdio.h>
#include "fsl_common.h"
#include "fsl_smc.h"
#include "fsl_llwu.h"
#include "fsl_rcm.h"
#include "fsl_lptmr.h"
#include "fsl_port.h"
#include "power_mode_switch.h"
#include "board.h"
#include "pin_mux.h"
#include "fsl_pmc.h"
#include "fsl_debug_console.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define LLWU_WAKEUP_NFC_PIN 5U
#define LLWU_WAKEUP_BATTERY_PIN 7U
#define LLWU_WAKEUP_POWERSTAT_PIN 8U
#define LLWU_WAKEUP_PIN_TYPE kLLWU_ExternalPinRisingEdge
#define APP_WAKEUP_IRQ_TYPE kPORT_InterruptRisingEdge

/*******************************************************************************
 * Code
 ******************************************************************************/

void APP_PowerPreSwitchHook(smc_power_state_t originPowerState, app_power_mode_t targetMode)
{
    if ((kAPP_PowerModeRun != targetMode) && (kAPP_PowerModeVlpr != targetMode))
    {
        /*
         * Set pins for current leakage to disabled or analog.
         * Keep only LLWU pins routed as GPIO
         */
//        BOARD_DisablePins();
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
         * Set pins back to normal
         */
//        BOARD_InitPins();
    }
}

/*!
 * @brief LLWU interrupt handler.
 */
void LLWU_IRQHandler(void)
{
    /* If wakeup by NFC pin. */
    if (LLWU_GetExternalWakeupPinFlag(LLWU, LLWU_WAKEUP_NFC_PIN))
    {
    	PORT_SetPinInterruptConfig(BOARD_INITPINS_NFC_INT_PORT, BOARD_INITPINS_NFC_INT_PIN, kPORT_InterruptOrDMADisabled);
    	PORT_ClearPinsInterruptFlags(BOARD_INITPINS_NFC_INT_PORT, (1U << BOARD_INITPINS_NFC_INT_PIN));
        LLWU_ClearExternalWakeupPinFlag(LLWU, LLWU_WAKEUP_NFC_PIN);
        PRINTF("LLWU Wakeup by NFC Pin.\r\n");
    }
    /* If wakeup by power stat pin. */
    if (LLWU_GetExternalWakeupPinFlag(LLWU, LLWU_WAKEUP_POWERSTAT_PIN))
    {
        // PORT_SetPinInterruptConfig(BOARD_INITPINS_NFC_INT_PORT, BOARD_INITPINS_NFC_INT_PIN, kPORT_InterruptOrDMADisabled);
        PORT_ClearPinsInterruptFlags(BOARD_INITPINS_POWER_STAT_PORT, (1U << BOARD_INITPINS_POWER_STAT_PIN));
        LLWU_ClearExternalWakeupPinFlag(LLWU, LLWU_WAKEUP_POWERSTAT_PIN);
        PRINTF("LLWU Wakeup by Power stat Pin.\r\n");
    }
    /* If wakeup by battery pin. */
    if (LLWU_GetExternalWakeupPinFlag(LLWU, LLWU_WAKEUP_BATTERY_PIN))
    {
        // PORT_SetPinInterruptConfig(BOARD_INITPINS_NFC_INT_PORT, BOARD_INITPINS_NFC_INT_PIN, kPORT_InterruptOrDMADisabled);
        PORT_ClearPinsInterruptFlags(BOARD_INITPINS_BATT_C_PORT, (1U << BOARD_INITPINS_BATT_C_PIN));
        LLWU_ClearExternalWakeupPinFlag(LLWU, LLWU_WAKEUP_BATTERY_PIN);
        PRINTF("LLWU Wakeup by battery Pin.\r\n");
    }
}

void PORTC_IRQHandler(void)
{
    if ((1U << BOARD_INITPINS_POWER_STAT_PIN) & PORT_GetPinsInterruptFlags(BOARD_INITPINS_POWER_STAT_PORT))
    {
        /* Disable interrupt. */
        PORT_SetPinInterruptConfig(BOARD_INITPINS_POWER_STAT_PORT, BOARD_INITPINS_POWER_STAT_PIN, kPORT_InterruptOrDMADisabled);
        PORT_ClearPinsInterruptFlags(BOARD_INITPINS_POWER_STAT_PORT, (1U << BOARD_INITPINS_POWER_STAT_PIN));
    }
    /* IRQ battery low voltage */
    if ((1U << BOARD_INITPINS_BATT_C_PIN) & PORT_GetPinsInterruptFlags(BOARD_INITPINS_BATT_C_PORT))
    {
        /* Disable interrupt. */
        PORT_SetPinInterruptConfig(BOARD_INITPINS_BATT_C_PORT, BOARD_INITPINS_BATT_C_PIN, kPORT_InterruptOrDMADisabled);
        PORT_ClearPinsInterruptFlags(BOARD_INITPINS_BATT_C_PORT, (1U << BOARD_INITPINS_BATT_C_PIN));
    }
}

void APP_SetWakeupConfig(app_power_mode_t targetMode)
{
    // PORT_SetPinInterruptConfig(BOARD_INITPINS_NFC_INT_PORT, BOARD_INITPINS_NFC_INT_PIN, APP_WAKEUP_IRQ_TYPE); No IRQ on portB
    PORT_SetPinInterruptConfig(BOARD_INITPINS_POWER_STAT_PORT, BOARD_INITPINS_POWER_STAT_PIN, APP_WAKEUP_IRQ_TYPE);
    PORT_SetPinInterruptConfig(BOARD_INITPINS_BATT_C_PORT, BOARD_INITPINS_BATT_C_PIN, APP_WAKEUP_IRQ_TYPE);

    /* If targetMode is VLLS/LLS, setup LLWU. */
    if ((kAPP_PowerModeWait != targetMode) && (kAPP_PowerModeVlpw != targetMode) &&
        (kAPP_PowerModeVlps != targetMode) && (kAPP_PowerModeStop != targetMode))
    {
        LLWU_SetExternalWakeupPinMode(LLWU, LLWU_WAKEUP_POWERSTAT_PIN, LLWU_WAKEUP_PIN_TYPE);
        LLWU_SetExternalWakeupPinMode(LLWU, LLWU_WAKEUP_BATTERY_PIN, LLWU_WAKEUP_PIN_TYPE);
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
