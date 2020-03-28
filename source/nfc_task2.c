#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <tool.h>
#include <Nfc.h>
#include <ndef_helper.h>
#include "NfcLibrary/NdefLibrary/inc/RW_NDEF.h"
#include "nfc_task.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "app_config.h"
#include "demo_sigfox.h"


#define print_buf(x,y,z)  {int loop; PRINTF(x); for(loop=0;loop<z;loop++) PRINTF("%.2x ", y[loop]); PRINTF("\n");}

/* Discovery loop configuration according to the targeted modes of operation */
unsigned char DiscoveryTechnologies[] = {
    MODE_POLL | TECH_PASSIVE_NFCA,
    MODE_POLL | TECH_PASSIVE_NFCF,
    MODE_POLL | TECH_PASSIVE_NFCB,
    MODE_POLL | TECH_PASSIVE_15693,
};

/* Mode configuration according to the targeted modes of operation */
unsigned mode = 0 | NXPNCI_MODE_RW;

/* Maximum number characters (bytes) in NFC record. */
#define NFC_RECORD_CHAR_MAX     40

/* NFC record to be send via Sigfox (ended by '\0'). */
unsigned char nfcRec[NFC_RECORD_CHAR_MAX + 1];
/* Length of text record in "nfcRec". Negative value if the record is not valid. */
int32_t nfcRecLen = -1;

/* Stores:
 * - a string to "nfcRec" text array.
 * - its length to "nfcRecLen". */
void DEMO_AddRecord(unsigned char *m, uint32_t lenght)
{
    if ((nfcRecLen < 0) && (lenght > 0))
    {
        nfcRecLen = (int32_t)((lenght <= NFC_RECORD_CHAR_MAX) ? lenght : NFC_RECORD_CHAR_MAX);
        memcpy(nfcRec, m, (uint32_t)nfcRecLen);
        nfcRec[nfcRecLen] = '\0';
    }
}

/* Returns true if "nfcRec" is not equal to "external" and "nfcRecLen" is between 1 and 10 characters. */
bool DEMO_IsLockApproved(void)
{
	/* Check if record is valid (nfcRecLen >= 0) is automatically included. */
    if ((nfcRecLen > 0) && (nfcRecLen <= 10) && strcasecmp((char *)nfcRec, "external"))
    {
        return true;
    }

    return false;
}

/* Turns the motor for a while in order to unlock the mechanical lock. */
inline static void DEMO_Unlock(void)
{
    PRINTF("DEMO unlocked \n");
//    GPIO_PinWrite(BOARD_INITPINS_HBRIDGE_END_GPIO, BOARD_INITPINS_HBRIDGE_END_GPIO_PIN, 1);
//    App_WaitMsec(SF_MOTOR_RUNTIME_MS);
//    GPIO_PinWrite(BOARD_INITPINS_HBRIDGE_END_GPIO, BOARD_INITPINS_HBRIDGE_END_GPIO_PIN, 0);
//    GPIO_PinWrite(BOARD_INITPINS_HBRIDGE_DIR_GPIO, BOARD_INITPINS_HBRIDGE_DIR_GPIO_PIN, 1);
}

/* Turns the motor for a while in order to lock the mechanical lock. */
inline static void DEMO_Lock(void)
{
    PRINTF("DEMO locked \n");
//    GPIO_PinWrite(BOARD_INITPINS_HBRIDGE_END_GPIO, BOARD_INITPINS_HBRIDGE_END_GPIO_PIN, 1);
//    App_WaitMsec(SF_MOTOR_RUNTIME_MS);
//    GPIO_PinWrite(BOARD_INITPINS_HBRIDGE_END_GPIO, BOARD_INITPINS_HBRIDGE_END_GPIO_PIN, 0);
//    GPIO_PinWrite(BOARD_INITPINS_HBRIDGE_DIR_GPIO, BOARD_INITPINS_HBRIDGE_DIR_GPIO_PIN, 0);
}

void PCD_MIFARE_scenario (void)
{
    #define BLK_NB_MFC      4
    #define KEY_MFC         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
    #define DATA_WRITE_MFC  0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xaa, 0xbb, 0xcc, 0xdd, 0xee, 0xff

    bool status;
    unsigned char Resp[256];
    unsigned char RespSize;
    /* Authenticate sector 1 with generic keys */
    unsigned char Auth[] = {0x40, BLK_NB_MFC/4, 0x10, KEY_MFC};
    /* Read block 4 */
    unsigned char Read[] = {0x10, 0x30, BLK_NB_MFC};
    /* Write block 4 */
    unsigned char WritePart1[] = {0x10, 0xA0, BLK_NB_MFC};
    unsigned char WritePart2[] = {0x10, DATA_WRITE_MFC};

    /* Authenticate */
    status = NxpNci_ReaderTagCmd(Auth, sizeof(Auth), Resp, &RespSize);
    if((status == NFC_ERROR) || (Resp[RespSize-1] != 0))
    {
        PRINTF(" Authenticate sector %d failed with error 0x%02x\n", Auth[1], Resp[RespSize-1]);
        return;
    }
    PRINTF(" Authenticate sector %d succeed\n", Auth[1]);

    /* Read block */
    status = NxpNci_ReaderTagCmd(Read, sizeof(Read), Resp, &RespSize);
    if((status == NFC_ERROR) || (Resp[RespSize-1] != 0))
    {
        PRINTF(" Read block %d failed with error 0x%02x\n", Read[2], Resp[RespSize-1]);
        return;
    }
    PRINTF(" Read block %d:", Read[2]); print_buf(" ", (Resp+1), RespSize-2);

    /* Write block */
    status = NxpNci_ReaderTagCmd(WritePart1, sizeof(WritePart1), Resp, &RespSize);
    if((status == NFC_ERROR) || (Resp[RespSize-1] != 0))
    {
        PRINTF(" Write block %d failed with error 0x%02x\n", WritePart1[2], Resp[RespSize-1]);
        return;
    }
    status = NxpNci_ReaderTagCmd(WritePart2, sizeof(WritePart2), Resp, &RespSize);
    if((status == NFC_ERROR) || (Resp[RespSize-1] != 0))
    {
        PRINTF(" Write block %d failed with error 0x%02x\n", WritePart1[2], Resp[RespSize-1]);
        return;
    }
    PRINTF(" Block %d written\n", WritePart1[2]);

    /* Read block */
    status = NxpNci_ReaderTagCmd(Read, sizeof(Read), Resp, &RespSize);
    if((status == NFC_ERROR) || (Resp[RespSize-1] != 0))
    {
        PRINTF(" Read failed with error 0x%02x\n", Resp[RespSize-1]);
        return;
    }
    PRINTF(" Read block %d:", Read[2]); print_buf(" ", (Resp+1), RespSize-2);
}

void displayCardInfo(NxpNci_RfIntf_t RfIntf)
{
    switch(RfIntf.Protocol){
    case PROT_T1T:
    case PROT_T2T:
    case PROT_T3T:
    case PROT_ISODEP:
        PRINTF(" - POLL MODE: Remote T%dT activated\n", RfIntf.Protocol);
        break;
    case PROT_ISO15693:
        PRINTF(" - POLL MODE: Remote ISO15693 card activated\n");
        break;
    case PROT_MIFARE:
        PRINTF(" - POLL MODE: Remote MIFARE card activated\n");
        break;
    default:
        PRINTF(" - POLL MODE: Undetermined target\n");
        return;
    }

    switch(RfIntf.ModeTech) {
    case (MODE_POLL | TECH_PASSIVE_NFCA):
        PRINTF("\tSENS_RES = 0x%.2x 0x%.2x\n", RfIntf.Info.NFC_APP.SensRes[0], RfIntf.Info.NFC_APP.SensRes[1]);
        print_buf("\tNFCID = ", RfIntf.Info.NFC_APP.NfcId, RfIntf.Info.NFC_APP.NfcIdLen);
        if(RfIntf.Info.NFC_APP.SelResLen != 0) PRINTF("\tSEL_RES = 0x%.2x\n", RfIntf.Info.NFC_APP.SelRes[0]);
    break;

    case (MODE_POLL | TECH_PASSIVE_NFCB):
        if(RfIntf.Info.NFC_BPP.SensResLen != 0) print_buf("\tSENS_RES = ", RfIntf.Info.NFC_BPP.SensRes, RfIntf.Info.NFC_BPP.SensResLen);
    break;

    case (MODE_POLL | TECH_PASSIVE_NFCF):
        PRINTF("\tBitrate = %s\n", (RfIntf.Info.NFC_FPP.BitRate==1)?"212":"424");
        if(RfIntf.Info.NFC_FPP.SensResLen != 0) print_buf("\tSENS_RES = ", RfIntf.Info.NFC_FPP.SensRes, RfIntf.Info.NFC_FPP.SensResLen);
    break;

    case (MODE_POLL | TECH_PASSIVE_15693):
        print_buf("\tID = ", RfIntf.Info.NFC_VPP.ID, sizeof(RfIntf.Info.NFC_VPP.ID));
        PRINTF("\tAFI = 0x%.2x\n", RfIntf.Info.NFC_VPP.AFI);
        PRINTF("\tDSFID = 0x%.2x\n", RfIntf.Info.NFC_VPP.DSFID);
    break;

    default:
        break;
    }
}

void task_nfc_reader(NxpNci_RfIntf_t RfIntf)
{
    /* For each discovered cards */
    while(1){
        /* Display detected card information */
        displayCardInfo(RfIntf);

        /* What's the detected card type ? */
        switch(RfIntf.Protocol) {
        case PROT_MIFARE:
            /* Run dedicated scenario to demonstrate MIFARE card management */
            PCD_MIFARE_scenario();
            break;

        default:
            break;
        }

        /* If more cards (or multi-protocol card) were discovered (only same technology are supported) select next one */
        if(RfIntf.MoreTags) {
            if(NxpNci_ReaderActivateNext(&RfIntf) == NFC_ERROR) break;
        }
        /* Otherwise leave */
        else break;
    }

    /* Wait for card removal */
    NxpNci_ProcessReaderMode(RfIntf, PRESENCE_CHECK);

    PRINTF("CARD REMOVED\n");

    /* Restart discovery loop */
    NxpNci_StopDiscovery();
    NxpNci_StartDiscovery(DiscoveryTechnologies,sizeof(DiscoveryTechnologies));
}

void task_nfc(sf_drv_data_t* sfDriverConfig)
{
    NxpNci_RfIntf_t RfInterface;
    status_t status = kStatus_Success;
//    char m[100];
    bool doorClosed = false;
    bool sfNonBlockUsed = false;
    int32_t timeoutMs;
    uint8_t i;

    /* Open connection to NXPNCI device */
    if (NxpNci_Connect() == NFC_ERROR) {
        PRINTF("Error: cannot connect to NXPNCI device\n");
        return;
    }

    if (NxpNci_ConfigureSettings() == NFC_ERROR) {
        PRINTF("Error: cannot configure NXPNCI settings\n");
        return;
    }

    if (NxpNci_ConfigureMode(mode) == NFC_ERROR)
    {
        PRINTF("Error: cannot configure NXPNCI\n");
        return;
    }

    /* Start Discovery */
    if (NxpNci_StartDiscovery(DiscoveryTechnologies,sizeof(DiscoveryTechnologies)) != NFC_SUCCESS)
    {
        PRINTF("Error: cannot start discovery\n");
        return;
    }

    nfcRecLen = -1;

    PRINTF("Demo initialized for RCZ%d.", ((uint8_t)SF_STANDARD)+1);
    while(1)
    {
        PRINTF("\nWAITING FOR DEVICE DISCOVERY\n");

        /* Wait until a peer is discovered */
        while(NxpNci_WaitForDiscoveryNotification(&RfInterface) != NFC_SUCCESS)
        	;

        if ((RfInterface.ModeTech & MODE_MASK) == MODE_POLL)
        {
            task_nfc_reader(RfInterface);

             if (DEMO_IsLockApproved())
            {

            	/* Open/Close the door and create a Sigfox message. */
            	for (i = 0; i <= 10; i++)
            	{
            		nfcRec[12 - i] = nfcRec[10 - i];
            	}
            	if (doorClosed)
            	{
            		DEMO_Unlock();
            		nfcRec[0] = 'O';
            	}
            	else
            	{
            		DEMO_Lock();
            		nfcRec[0] = 'C';
            	}
            	nfcRec[1] = ':';
            	nfcRecLen += 2;
            	doorClosed = !doorClosed;

            	/* sfNonBlockUsed is set when ACK pin is high. */
            	sfNonBlockUsed = !SF_IsAckFrameReady(sfDriverConfig);

            	/* Send sigfox message non-blocking. */
            	if (sfNonBlockUsed)
            	{
            		status = SIGFOX_SendRecords_NonBlock(sfDriverConfig, nfcRec, (uint32_t)nfcRecLen);
            		timeoutMs = 20000;
            	}

            	/* Wait until user reads message on LCD. */
            	// App_WaitMsec(2000);
            	timeoutMs -= 2000;

            	/* Send data via Sigfox */
            	PRINTF("   Sending \"%s\" via Sigfox\n\n", nfcRec);


            	if (!sfNonBlockUsed)
            	{
            		status = SIGFOX_SendRecords(sfDriverConfig, nfcRec, (uint32_t)nfcRecLen);
            	}
            	else if (status == kStatus_Success)
            	{
            		while (!SF_IsAckFrameReady(sfDriverConfig))
            		{
            			if (timeoutMs < 0)
            			{
            				status = kStatus_SF_SpiTimeout;
            				break;
            			}
            			WAIT_AML_WaitMs(50);
//            			App_WaitMsec(50);
            			timeoutMs -= 50;
            		}

            		if (status == kStatus_Success)
            		{
            			status = SIGFOX_FinishNonBlock(sfDriverConfig);
            		}
            	}

            	if (status == kStatus_Success)
            	{
            		PRINTF("Transmission succeeded\n\n");
            	}
            	else
            	{
            		PRINTF("Transmission failed\n\n");
            		// App_WaitMsec(2000);

            	}
            }
            else
            {
            	/* Lock was not approved.*/
            	if (nfcRecLen >= 0)
            	{
            		PRINTF("Access denied!\n\nUser: %s", nfcRec);

            		// App_WaitMsec(2000);

            	}
            	else
            	{
            		/* NFC tag removed to early or it does not contain a text record. */
            	}
            }

            nfcRecLen = -1; /* Do not process the NFC record anymore. */

            /* Start Discovery - Do not check the return value! It returns NXPNCI_ERROR in case NXP badge was read! */
            NxpNci_StartDiscovery(DiscoveryTechnologies,sizeof(DiscoveryTechnologies));
        }
        else
        {
            PRINTF("WRONG DISCOVERY\n");
        }
    }
}
