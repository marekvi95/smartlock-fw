/*
 * nfc_task.c
 *  Authentication and reading of tags
 *  Created on: May 14, 2019
 *      Author: Marek Vitula
 *  Some parts based on NXP NFC Library example
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <nfc_task.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <tool.h>
#include <stdbool.h>
#include <Nfc.h>
#include <sigfox.h>
#include "board.h"
#include "pin_mux.h"
#include "fsl_debug_console.h"
#include "app_config.h"
#include "display.h"
#include "user.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define print_buf(x,y,z)  {int loop; printf(x); for(loop=0;loop<z;loop++) printf("%.2x ", y[loop]); printf("\n");}

/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Discovery loop configuration according to the targeted modes of operation */
unsigned char DiscoveryTechnologies[] = {
    MODE_POLL | TECH_PASSIVE_NFCA,
};


/* Mode configuration according to the targeted modes of operation */
unsigned mode = 0 | NXPNCI_MODE_RW;

/*******************************************************************************
 * Code
 ******************************************************************************/

/* Turns the motor for a while in order to unlock the mechanical lock. */
inline static void unlock(void)
{
	displayText("Unlocking", "Driving motor");
	PRINTF("UNLOCKING \n");
	__disable_irq();
	GPIO_PinWrite(BOARD_INITPINS_PSAVE_GPIO, BOARD_INITPINS_PSAVE_PIN, 0);
	GPIO_PinWrite(BOARD_INITPINS_IN1A_GPIO, BOARD_INITPINS_IN1A_PIN, 0);
	GPIO_PinWrite(BOARD_INITPINS_IN2A_GPIO, BOARD_INITPINS_IN2A_PIN, 0);
	GPIO_PinWrite(BOARD_INITPINS_IN1B_GPIO, BOARD_INITPINS_IN1B_PIN, 1);
	GPIO_PinWrite(BOARD_INITPINS_IN2B_GPIO, BOARD_INITPINS_IN2B_PIN, 1);
	WAIT_AML_WaitMs(SF_MOTOR_RUNTIME_MS);
	GPIO_PinWrite(BOARD_INITPINS_IN1B_GPIO, BOARD_INITPINS_IN1B_PIN, 0);
	GPIO_PinWrite(BOARD_INITPINS_IN2B_GPIO, BOARD_INITPINS_IN2B_PIN, 0);
	GPIO_PinWrite(BOARD_INITPINS_PSAVE_GPIO, BOARD_INITPINS_PSAVE_PIN, 1);
	__enable_irq();
	setUnlock();
}

/* Turns the motor for a while in order to lock the mechanical lock. */
inline static void lock(void)
{
	displayText("Locking", "Driving motor");
	PRINTF("LOCKING \n");
	__disable_irq();
	GPIO_PinWrite(BOARD_INITPINS_PSAVE_GPIO, BOARD_INITPINS_PSAVE_PIN, 0);
	GPIO_PinWrite(BOARD_INITPINS_IN1A_GPIO, BOARD_INITPINS_IN1A_PIN, 1);
	GPIO_PinWrite(BOARD_INITPINS_IN2A_GPIO, BOARD_INITPINS_IN2A_PIN, 1);
	GPIO_PinWrite(BOARD_INITPINS_IN1B_GPIO, BOARD_INITPINS_IN1B_PIN, 0);
	GPIO_PinWrite(BOARD_INITPINS_IN2B_GPIO, BOARD_INITPINS_IN2B_PIN, 0);
	WAIT_AML_WaitMs(SF_MOTOR_RUNTIME_MS);
	GPIO_PinWrite(BOARD_INITPINS_IN1A_GPIO, BOARD_INITPINS_IN1A_PIN, 0);
	GPIO_PinWrite(BOARD_INITPINS_IN2A_GPIO, BOARD_INITPINS_IN2A_PIN, 0);
	GPIO_PinWrite(BOARD_INITPINS_PSAVE_GPIO, BOARD_INITPINS_PSAVE_PIN, 1);
	__enable_irq();
	setLock();
}

/**
 * @brief Compose Sigfox message
 * 
 * @param nfcMsg Pointer to nfc message
 * @param auth True if user is authenticated
 * @param lock True if the smartlock will be locked, False if opened
 */
void composeMsg(char *nfcMsg, bool auth, bool lock)
{
    /* Set a Sigfox message *
     * 7th bit is a type of message *
     * 6th value if user is authenticated *
     * 5th status of the lock - 0 if lock is open, 1 if lock is closed *
     * 4th and 3rd battery status */
    
    #define MSG_TYPE_POS 7
    #define AUTH_POS 6
    #define LOCK_STATUS_POS 5
    #define BATT_POS 4

    unsigned char msg = 0;

    msg = (msg & ~(1U << MSG_TYPE_POS)) | (0 << MSG_TYPE_POS); // Set msg type to 0 -- authentication message
    msg = (msg & ~(1U << AUTH_POS)) | (auth << AUTH_POS); // Set  bit to auth
    msg = (msg & ~(1U << LOCK_STATUS_POS)) | (lock << LOCK_STATUS_POS); // Set lock status
    
    nfcMsg[0] = msg;
}

/**
 * @brief This function is called when the NFC tag is approved
 * Send the message and open the door
 * 
 * @param nfcMsg 
 * @param sfDriverConfig 
 * @return uint8_t 
 */
uint8_t lockApproved(bool approved, char * nfcMsg, sf_drv_data_t* sfDriverConfig)
{
	PRINTF("sending records \n");
    status_t status = kStatus_Success;
    bool sfNonBlockUsed = false;
    int32_t timeoutMs;

    /* If Tag is approved send the message and open */
    if (approved)
    {
        if (isLocked())
        {
    	    unlock();
            /* Create a Sigfox message. */
            composeMsg(nfcMsg, true, false); 
        }
        else
        {
    	    lock();
            /* Create a Sigfox message. */
            composeMsg(nfcMsg, true, true);
        }
    }
    else
    {
        /* Create a Sigfox message. */
        composeMsg(nfcMsg, false, isLocked());
    }

    /* sfNonBlockUsed is set when ACK pin is high. */
    sfNonBlockUsed = !SF_IsAckFrameReady(sfDriverConfig);

    /* Send sigfox message non-blocking. */
    if (sfNonBlockUsed)
    {
    	status = SIGFOX_SendRecords_NonBlock(sfDriverConfig, (unsigned char *)nfcMsg, SF_MSG_SIZE);
    	timeoutMs = 20000;
    }

    /* Send data via Sigfox */
    displayText("Sending...", (char*)nfcMsg);
    print_buf("Sending Sigfox message: ", nfcMsg, SF_MSG_SIZE);

    if (!sfNonBlockUsed)
    {
    	status = SIGFOX_SendRecords(sfDriverConfig, (unsigned char *)nfcMsg, SF_MSG_SIZE);
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
    	displayText("TX Failed", "Waiting 2s");
    	PRINTF("Transmission failed\n\n");
    	WAIT_AML_WaitMs(2000);
    }

	return 1;
}

/**
 * @brief Reads key stored at the Mifare card
 * 
 * @return status_t 
 */
status_t readKey(unsigned char * authKey, unsigned char * mifareKey)
{
    #define AUTH_SIZE 3 + MIFARE_SIZE

    status_t status = 0;
    unsigned char Resp[256];
    unsigned char RespSize;
    unsigned char Auth[AUTH_SIZE];

    /* Read block */
    unsigned char Read[] = {0x10, 0x30, BLK_NB_MFC};
    
    Auth[0] = 0x40; // authentication command
    Auth[1] = BLK_NB_MFC/4; // sector number
    Auth[2] = 0x10;

    memcpy(Auth + 3, mifareKey, MIFARE_SIZE); // Copy mifare key to auth from index 3

    /* Authenticate with three retries*/
    do 
    {
        status = NxpNci_ReaderTagCmd(Auth, sizeof(Auth), Resp, &RespSize);
        retries++;
        printf("Retry number %d from 3\n", retries);

        if (retries > 2)
            break;

    } while ((status == NFC_ERROR) || (Resp[RespSize-1] != 0));
    
    
    if((status == NFC_ERROR) || (Resp[RespSize-1] != 0))
    {
    	displayText("Auth. Error", "Try it again, authentication failed");
    	PRINTF(" Authenticate sector %d failed with error 0x%02x\n", Auth[1], Resp[RespSize-1]);
        return status;
    }

    PRINTF(" Authenticate sector %d succeed\n", Auth[1]);

    /* Read block */
    retries = 0;
    do 
    {
        status = NxpNci_ReaderTagCmd(Read, sizeof(Read), Resp, &RespSize);
        retries++;

        if (retries > 2)
            break;

    } while ((status == NFC_ERROR) || (Resp[RespSize-1] != 0));
    
    if((status == NFC_ERROR) || (Resp[RespSize-1] != 0))
    {
    	displayText("Key read NOK", "Key could not be read, try it again");
    	PRINTF(" Read block %d failed with error 0x%02x\n", Read[2], Resp[RespSize-1]);
        return status;
    }

    PRINTF(" Read block %d:", Read[2]); print_buf(" ", (Resp+1), RespSize-2);

    /* Copy key to authKey */
    memcpy(authKey, (Resp+1), KEY_SIZE);

    return status;
}

#if defined(MASTER_MODE) && MASTER_MODE
/**
 * @brief Master procedure is called when the master tag is detected
 *  - procedure for saving new tags to the DB
 *   i. tag DB is inserted into DB
 *   ii. authentication key is written to the tag
 * 
 * @param RfIntf 
 * @param sfDriverConfig 
 */
void masterProcedure(NxpNci_RfIntf_t RfIntf, sf_drv_data_t* sfDriverConfig)
{    
    #define KEY_MFC         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF // default Mifare key
    #define WRITE_SIZE 17
    bool status;
    status_t result;
    unsigned char Resp[256];
    unsigned char RespSize;
    /* Authenticate sector 1 with generic keys */
    unsigned char Auth[AUTH_SIZE];
    /* Read block 4 */
    unsigned char Read[] = {0x10, 0x30, BLK_NB_MFC};
    /* Write block 4 */
    unsigned char WritePart1[] = {0x10, 0xA0, BLK_NB_MFC};
    unsigned char WritePart2[WRITE_SIZE];
    unsigned char authKey[KEY_SIZE] = {0};
	unsigned char mifareKey[MIFARE_SIZE] = {0};

    /* 1. Insert UID to the user DB */
    status = insertUser(RfIntf.Info.NFC_APP.NfcId);
    if (!status)
    {
        PRINTF("Master procedure failed, cannot insert user \n");
        return;
    }

    /* 2. Erase and write flash */
    result = eraseFlash();
    if (!result)
	{
		printf("Error during flash erase\n");
		return;
	}
    result = writeFlash();
    if (!result)
	{
		printf("Error during flash write\n");
		return;
	}

    /* 3. Get auth of the user */
    status = getAuth(RfIntf.Info.NFC_APP.NfcId, authKey, mifareKey);
    if (!status)
    {
        PRINTF("Master procedure failed, cannot get auth of new user \n");
        return;
    }

    Auth[0] = 0x40; // authentication command
    Auth[1] = BLK_NB_MFC/4; // sector number
    Auth[2] = 0x10;

    memcpy(Auth + 3, mifareKey, MIFARE_SIZE); // Copy mifare key to auth from index 3

    /* 4. Authenticate sector */
    status = NxpNci_ReaderTagCmd(Auth, sizeof(Auth), Resp, &RespSize);
    if((status == NFC_ERROR) || (Resp[RespSize-1] != 0))
    {
        PRINTF(" Authenticate sector %d failed with error 0x%02x\n", Auth[1], Resp[RespSize-1]);
        return;
    }
    PRINTF(" Authenticate sector %d succeed\n", Auth[1]);

    WritePart2[0] = 0x10;
    memcpy(WritePart2 + 1, authKey, KEY_SIZE); // Copy keys to write array

    /* 5. Write block with key */
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

    /* 6. Read block */
    status = NxpNci_ReaderTagCmd(Read, sizeof(Read), Resp, &RespSize);
    if((status == NFC_ERROR) || (Resp[RespSize-1] != 0))
    {
        PRINTF(" Read failed with error 0x%02x\n", Resp[RespSize-1]);
        return;
    }
    PRINTF(" Read block %d:", Read[2]); print_buf(" ", (Resp+1), RespSize-2);
    return;
}

/**
 * @brief Displays information about the discovered cards
 * 
 * @param RfIntf 
 */
void readTag(NxpNci_RfIntf_t RfIntf, sf_drv_data_t* sfDriverConfig)
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
		unsigned char mifareKey[MIFARE_SIZE] = {0};
        char msg[SF_MSG_SIZE] = {0};
        uint8_t authStatus = 0;

		PRINTF("\tSENS_RES = 0x%.2x 0x%.2x\n", RfIntf.Info.NFC_APP.SensRes[0], RfIntf.Info.NFC_APP.SensRes[1]);
		print_buf("\tNFCID = ", RfIntf.Info.NFC_APP.NfcId, RfIntf.Info.NFC_APP.NfcIdLen);
		if(RfIntf.Info.NFC_APP.SelResLen != 0) PRINTF("\tSEL_RES = 0x%.2x\n", RfIntf.Info.NFC_APP.SelRes[0]);

        #if defined(MASTER_MODE) && MASTER_MODE
        static bool masterFlag = false;
        
        if(masterFlag)
        {
            masterFlag = false;
            masterProcedure(RfIntf, sfDriverConfig);
            return;
        }
        #endif

        memcpy(msg + 1, RfIntf.Info.NFC_APP.NfcId, UID_SIZE); // Copy UID to the first index of sigfox msg
        authStatus = getAuth(RfIntf.Info.NFC_APP.NfcId, keyDB, mifareKey); // Find tag in DB

        #if defined(MASTER_MODE) && MASTER_MODE
        /* if auth status > 1 master tag is detected */
        if(authStatus > 1)
        {
            PRINTF(" - Master UID approved\n");
            print_buf("Authentication KEY:", keyDB, KEY_SIZE);
            print_buf("\nMifare KEY", mifareKey, MIFARE_SIZE);

			readKey(keyRead, mifareKey); // Read key from the NFC tag

		    if (memcmp(keyDB, keyRead, KEY_SIZE) == 0) // Compare key with the DB
		    {
		        // null array
		    	memset(keyRead, 0, KEY_SIZE);
		    	memset(keyDB, 0, KEY_SIZE);
                PRINTF(" - Master Key approved\n");    
                /* set master flag, next card that will be detected will be saved to DB */
                masterFlag = true;
                displayText("Master mode", "Next detected tag will be saved to DB");
		    }
        }
		else if(authStatus)
		{
			PRINTF(" - UID approved\n");
            print_buf("Authentication KEY:", keyDB, KEY_SIZE);
            print_buf("\nMifare KEY", mifareKey, MIFARE_SIZE);

			readKey(keyRead, mifareKey); // Read key from the NFC tag

		    if (memcmp(keyDB, keyRead, KEY_SIZE) == 0) // Compare key with the DB
		    {
		        // null array
		    	memset(keyRead, 0, KEY_SIZE);
		    	memset(keyDB, 0, KEY_SIZE);
		    	
                lockApproved(true, msg, sfDriverConfig); // Send message and open the door

		    }
		    else
		    {
		    	displayText("REFUSED", "Try it again");
		    }
		}
		else
		{
			PRINTF(" - UID is not approved\n");
			displayText("UID NOK", "Trespassers will be prosecuted");
            lockApproved(false, msg, sfDriverConfig); // Send message that UID cannot be authenticated
		}
	}
	else
	{
		PRINTF(" - POLL MODE: Undetermined target\n");
		return;
	}
}


/**
 * @brief Called when NFC cards are detected
 * 
 * @param RfIntf 
 */
void task_nfc_reader(NxpNci_RfIntf_t RfIntf, sf_drv_data_t* sfDriverConfig)
{
    /* For each discovered cards */
    while(1){
        /* Read tag */
        readTag(RfIntf, sfDriverConfig);

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

/**
 * @brief NFC polling loop initialization
 * 
 * @param sfDriverConfig 
 */
void task_nfc(sf_drv_data_t* sfDriverConfig)
{
    NxpNci_RfIntf_t RfInterface;

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


    PRINTF("App initialized for RCZ%d.", ((uint8_t)SF_STANDARD)+1);
    setNFC(); // set flag that NFC is initialized

    while(1)
    {
        displayText(default_text, "waiting for the tag discovery");
    	PRINTF("\nWAITING FOR DEVICE DISCOVERY\n");

        /* Wait until a peer is discovered */
        while(NxpNci_WaitForDiscoveryNotification(&RfInterface) != NFC_SUCCESS)
        	;

        if ((RfInterface.ModeTech & MODE_MASK) == MODE_POLL)
        {
            task_nfc_reader(RfInterface, sfDriverConfig);

//            /* Start Discovery - Do not check the return value! It returns NXPNCI_ERROR in case NXP badge was read! */
//            NxpNci_StartDiscovery(DiscoveryTechnologies,sizeof(DiscoveryTechnologies));
        }
        else
        {
            PRINTF("WRONG DISCOVERY\n");
        }
    }
}
