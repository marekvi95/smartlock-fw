#include <nfc_task.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <tool.h>
#include <Nfc.h>
#include <sigfox.h>
#include "board.h"
#include "fsl_debug_console.h"
#include "app_config.h"
#include "display.h"
#include "user.h"


#define print_buf(x,y,z)  {int loop; PRINTF(x); for(loop=0;loop<z;loop++) PRINTF("%.2x ", y[loop]); PRINTF("\n");}

/* Discovery loop configuration according to the targeted modes of operation */
unsigned char DiscoveryTechnologies[] = {
    MODE_POLL | TECH_PASSIVE_NFCA,
//    MODE_POLL | TECH_PASSIVE_NFCF,
//    MODE_POLL | TECH_PASSIVE_NFCB,
//    MODE_POLL | TECH_PASSIVE_15693,
};

/* Mode configuration according to the targeted modes of operation */
unsigned mode = 0 | NXPNCI_MODE_RW;

/* Size of authentication key stored at the card in bytes (1 block) */
//#define AUTH_KEY_SIZE     16

/* Authentication key read from the NFC card */
//static unsigned char nfcRec[AUTH_KEY_SIZE];
//
///* Message to be sent to sigfox network */
//static unsigned char nfcMsg[SIGFOX_RECORD_CHAR_MAX];

/* Length of text record in "nfcRec". Negative value if the record is not valid. */
int32_t nfcMsgLen = -1;

/* Stores:
 * - a string to "nfcMsg" text array.
 * - its length to "nfcMsgLen". */
//void addRecord(unsigned char *m, uint32_t lenght)
//{
//    if ((nfcMsgLen < 0) && (lenght > 0))
//    {
//        nfcMsgLen = (int32_t)((lenght <= SIGFOX_RECORD_CHAR_MAX) ? lenght : SIGFOX_RECORD_CHAR_MAX);
//        memcpy(nfcMsg, m, (uint32_t)nfcMsgLen);
//        nfcMsg[nfcMsgLen] = '\0';
//    }
//}

/**
 * @brief Compares key obtained from the nfc card to key stored in MCU
 * 
 * @return true if key is approved
 * @return false if key doesn't mach
 */
//bool isLockApproved(void)
//{
////	static unsigned char authKey[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
//	//42 54 69 63 69 6e 6f 43 41 00 00 00 00 00 00 00
//	static unsigned char authKey[] = {0x42, 0x54, 0x69, 0x63, 0x69, 0x6e, 0x6f, 0x43, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
//	/* Check if record is valid */
//    if (memcmp(nfcRec, authKey, AUTH_KEY_SIZE) == 0)
//    {
//        // null array
//    	memset(nfcRec, 0, sizeof(nfcRec));
//    	displayText(0, "Approved", "Ready to unlock");
//    	return true;
//    }
//
//    displayText(0, "Not approved", "Trespassers will be prosecuted");
//    return false;
//}

/* Turns the motor for a while in order to unlock the mechanical lock. */
inline static void unlock(void)
{
	displayText(0, "Unlocking", "Driving motor");
	PRINTF("UNLOCKING \n");
//    GPIO_PinWrite(BOARD_INITPINS_HBRIDGE_END_GPIO, BOARD_INITPINS_HBRIDGE_END_GPIO_PIN, 1);
//    App_WaitMsec(SF_MOTOR_RUNTIME_MS);
//    GPIO_PinWrite(BOARD_INITPINS_HBRIDGE_END_GPIO, BOARD_INITPINS_HBRIDGE_END_GPIO_PIN, 0);
//    GPIO_PinWrite(BOARD_INITPINS_HBRIDGE_DIR_GPIO, BOARD_INITPINS_HBRIDGE_DIR_GPIO_PIN, 1);
}

/* Turns the motor for a while in order to lock the mechanical lock. */
inline static void lock(void)
{
	displayText(0, "Locking", "Driving motor");
	PRINTF("LOCKING \n");
//    GPIO_PinWrite(BOARD_INITPINS_HBRIDGE_END_GPIO, BOARD_INITPINS_HBRIDGE_END_GPIO_PIN, 1);
//    App_WaitMsec(SF_MOTOR_RUNTIME_MS);
//    GPIO_PinWrite(BOARD_INITPINS_HBRIDGE_END_GPIO, BOARD_INITPINS_HBRIDGE_END_GPIO_PIN, 0);
//    GPIO_PinWrite(BOARD_INITPINS_HBRIDGE_DIR_GPIO, BOARD_INITPINS_HBRIDGE_DIR_GPIO_PIN, 0);
}

void lockApproved(void)
{
	PRINTF(" - approved locking/unlocking \n");
}

uint8_t sendRecord(char * msg)
{
	PRINTF("sending records \n");
	return 1;
}

/**
 * @brief Reads key stored at the Mifare card
 * 
 * @return status_t 
 */
status_t readKey(unsigned char * key)
{
    #define BLK_NB_MFC      4
//    #define KEY_MFC         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	#define KEY_MFC 		  0x02, 0x12, 0x09, 0x19, 0x75, 0x91

    status_t status = 0;
    unsigned char Resp[256];
    unsigned char RespSize;
    /* Authenticate sector 1 with generic keys */
    unsigned char Auth[] = {0x40, BLK_NB_MFC/4, 0x10, KEY_MFC};
    /* Read block 4 */
    unsigned char Read[] = {0x10, 0x30, BLK_NB_MFC};

    /* Authenticate */
    status |= NxpNci_ReaderTagCmd(Auth, sizeof(Auth), Resp, &RespSize);
    if((status == NFC_ERROR) || (Resp[RespSize-1] != 0))
    {
//    	displayText(0, "Auth. Error", "Try it again, authentication failed");
    	PRINTF(" Authenticate sector %d failed with error 0x%02x\n", Auth[1], Resp[RespSize-1]);
        return status;
    }
    displayText(0, "Auth OK", "Reading key");
    PRINTF(" Authenticate sector %d succeed\n", Auth[1]);

    /* Read block */
    status |= NxpNci_ReaderTagCmd(Read, sizeof(Read), Resp, &RespSize);
    if((status == NFC_ERROR) || (Resp[RespSize-1] != 0))
    {
    	displayText(0, "Key read NOK", "Key could not be read, try it again");
    	PRINTF(" Read block %d failed with error 0x%02x\n", Read[2], Resp[RespSize-1]);
        return status;
    }
    displayText(0, "Key read OK", "Finding user in the database...");
    PRINTF(" Read block %d:", Read[2]); print_buf(" ", (Resp+1), RespSize-2);

    //TODO: hash keys
    /* Copy key to nfcRec variable */
    memcpy(key, (Resp+1), KEY_SIZE);

    return status;
}

/**
 * @brief Displays information about the discovered cards
 * 
 * @param RfIntf 
 */
void readTag(NxpNci_RfIntf_t RfIntf)
{
	if(RfIntf.Protocol == PROT_MIFARE)
	{
		PRINTF(" - POLL MODE: Remote MIFARE card activated\n");
	}
	else
	{
		PRINTF(" - POLL MODE: Undetermined target\n");
		return;
	}


	if(RfIntf.ModeTech == (MODE_POLL | TECH_PASSIVE_NFCA))
	{
		unsigned char keyDB[KEY_SIZE] = {0};
		unsigned char keyRead[KEY_SIZE] = {0};
		char msg[NAME_SIZE] = {0};

		PRINTF("\tSENS_RES = 0x%.2x 0x%.2x\n", RfIntf.Info.NFC_APP.SensRes[0], RfIntf.Info.NFC_APP.SensRes[1]);
		print_buf("\tNFCID = ", RfIntf.Info.NFC_APP.NfcId, RfIntf.Info.NFC_APP.NfcIdLen);
		if(RfIntf.Info.NFC_APP.SelResLen != 0) PRINTF("\tSEL_RES = 0x%.2x\n", RfIntf.Info.NFC_APP.SelRes[0]);

		if(getAuth(RfIntf.Info.NFC_APP.NfcId, keyDB, msg))
		{
			PRINTF(" - UID approved\n");
			PRINTF("KEY: %s\n", keyDB);
			PRINTF("MSG: %s\n", msg);

			readKey(keyRead);

		    if (memcmp(keyDB, keyRead, KEY_SIZE) == 0)
		    {
		        // null array
		    	memset(keyRead, 0, KEY_SIZE);
		    	memset(keyDB, 0, KEY_SIZE);
		    	displayText(0, "Approved", "Ready to unlock");
		    	lockApproved();
		    	sendRecord(msg);

		    }
		    else
		    {
		    	displayText(0, "REFUSED", "Try it again");
		    }
		}
		else
		{
			PRINTF(" - UID is not approved\n");
			displayText(0, "UID NOK", "Trespassers will be prosecuted");
		}
	}
	else
	{
		PRINTF(" - POLL MODE: Undetermined target\n");
		return;
	}
}


//	switch(RfIntf.Protocol){
////    case PROT_T1T:
////    case PROT_T2T:
////    case PROT_T3T:
////    case PROT_ISODEP:
////        PRINTF(" - POLL MODE: Remote T%dT activated\n", RfIntf.Protocol);
////        break;
////    case PROT_ISO15693:
////        PRINTF(" - POLL MODE: Remote ISO15693 card activated\n");
////        break;
//    case PROT_MIFARE:
//        PRINTF(" - POLL MODE: Remote MIFARE card activated\n");
//        break;
//    default:
//        PRINTF(" - POLL MODE: Undetermined target\n");
//        return;
//    }
//
//    switch(RfIntf.ModeTech) {
//    case (MODE_POLL | TECH_PASSIVE_NFCA):
//        PRINTF("\tSENS_RES = 0x%.2x 0x%.2x\n", RfIntf.Info.NFC_APP.SensRes[0], RfIntf.Info.NFC_APP.SensRes[1]);
//        print_buf("\tNFCID = ", RfIntf.Info.NFC_APP.NfcId, RfIntf.Info.NFC_APP.NfcIdLen);
//        if(RfIntf.Info.NFC_APP.SelResLen != 0) PRINTF("\tSEL_RES = 0x%.2x\n", RfIntf.Info.NFC_APP.SelRes[0]);
//
//
//
//    break;
//
////    case (MODE_POLL | TECH_PASSIVE_NFCB):
////        if(RfIntf.Info.NFC_BPP.SensResLen != 0) print_buf("\tSENS_RES = ", RfIntf.Info.NFC_BPP.SensRes, RfIntf.Info.NFC_BPP.SensResLen);
////    break;
////
////    case (MODE_POLL | TECH_PASSIVE_NFCF):
////        PRINTF("\tBitrate = %s\n", (RfIntf.Info.NFC_FPP.BitRate==1)?"212":"424");
////        if(RfIntf.Info.NFC_FPP.SensResLen != 0) print_buf("\tSENS_RES = ", RfIntf.Info.NFC_FPP.SensRes, RfIntf.Info.NFC_FPP.SensResLen);
////    break;
////
////    case (MODE_POLL | TECH_PASSIVE_15693):
////        print_buf("\tID = ", RfIntf.Info.NFC_VPP.ID, sizeof(RfIntf.Info.NFC_VPP.ID));
////        PRINTF("\tAFI = 0x%.2x\n", RfIntf.Info.NFC_VPP.AFI);
////        PRINTF("\tDSFID = 0x%.2x\n", RfIntf.Info.NFC_VPP.DSFID);
////    break;
//
//    default:
//        break;
//    }
//}

/**
 * @brief Called when NFC cards are detected
 * 
 * @param RfIntf 
 */
void task_nfc_reader(NxpNci_RfIntf_t RfIntf)
{
    /* For each discovered cards */
    while(1){
        /* Display detected card information */
        readTag(RfIntf);

//        /* What's the detected card type ? */
//        switch(RfIntf.Protocol) {
//        case PROT_MIFARE:
//            /* Read key stored at the sector 1 block 4 */
//            readKey();
//            break;
//
//        default:
//            break;
//        }

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
//    NxpNci_StartDiscovery(DiscoveryTechnologies,sizeof(DiscoveryTechnologies));
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

    nfcMsgLen = -1;

    PRINTF("App initialized for RCZ%d.", ((uint8_t)SF_STANDARD)+1);

    while(1)
    {
        displayText(doorClosed, default_text, "waiting for the tag discovery");
    	PRINTF("\nWAITING FOR DEVICE DISCOVERY\n");

        /* Wait until a peer is discovered */
        while(NxpNci_WaitForDiscoveryNotification(&RfInterface) != NFC_SUCCESS)
        	;

        if ((RfInterface.ModeTech & MODE_MASK) == MODE_POLL)
        {
            task_nfc_reader(RfInterface);

//             if (isLockApproved())
//            {
//
//            	/* Open/Close the door and create a Sigfox message. */
//            	for (i = 0; i <= 10; i++)
//            	{
//            		nfcMsg[12 - i] = nfcMsg[10 - i];
//            	}
//            	if (doorClosed)
//            	{
//            		unlock();
//            		nfcMsg[0] = 'O';
//            	}
//            	else
//            	{
//            		lock();
//            		nfcMsg[0] = 'C';
//            	}
//            	nfcMsg[1] = ':';
//            	nfcMsgLen += 2;
//            	doorClosed = !doorClosed;
//
//            	/* sfNonBlockUsed is set when ACK pin is high. */
//            	sfNonBlockUsed = !SF_IsAckFrameReady(sfDriverConfig);
//
//            	/* Send sigfox message non-blocking. */
//            	if (sfNonBlockUsed)
//            	{
//            		status = SIGFOX_SendRecords_NonBlock(sfDriverConfig, nfcMsg, (uint32_t)nfcMsgLen);
//            		timeoutMs = 20000;
//            	}
//
//            	/* Wait until user reads message on LCD. */
//            	// App_WaitMsec(2000);
//            	timeoutMs -= 2000;
//
//            	/* Send data via Sigfox */
//            	displayText(doorClosed, "Sending...", (char*)nfcMsg);
//            	PRINTF("   Sending \"%s\" via Sigfox\n\n", nfcMsg);
//
//
//            	if (!sfNonBlockUsed)
//            	{
//            		status = SIGFOX_SendRecords(sfDriverConfig, nfcMsg, (uint32_t)nfcMsgLen);
//            	}
//            	else if (status == kStatus_Success)
//            	{
//            		while (!SF_IsAckFrameReady(sfDriverConfig))
//            		{
//            			if (timeoutMs < 0)
//            			{
//            				status = kStatus_SF_SpiTimeout;
//            				break;
//            			}
//            			WAIT_AML_WaitMs(50);
//            			timeoutMs -= 50;
//            		}
//
//            		if (status == kStatus_Success)
//            		{
//            			status = SIGFOX_FinishNonBlock(sfDriverConfig);
//            		}
//            	}
//
//            	if (status == kStatus_Success)
//            	{
//            		PRINTF("Transmission succeeded\n\n");
//            	}
//            	else
//            	{
//            		PRINTF("Transmission failed\n\n");
//            		WAIT_AML_WaitMs(2000);
//
//            	}
//            }
//            else
//            {
//            	/* Lock was not approved.*/
//            	if (nfcMsgLen >= 0)
//            	{
//            		PRINTF("Access denied!\n\nUser: %s", nfcMsg);
//
//            		WAIT_AML_WaitMs(2000);
//
//            	}
//            	else
//            	{
//            		/* NFC tag removed to early or it does not contain a text record. */
//            		PRINTF("Tag removed too early\n\n");
//            	}
//            }
//
//            nfcMsgLen = -1; /* Do not process the NFC record anymore. */

            /* Start Discovery - Do not check the return value! It returns NXPNCI_ERROR in case NXP badge was read! */
            NxpNci_StartDiscovery(DiscoveryTechnologies,sizeof(DiscoveryTechnologies));
        }
        else
        {
            PRINTF("WRONG DISCOVERY\n");
        }
    }
}
