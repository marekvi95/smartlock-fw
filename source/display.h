/*
 * display.h
 *
 *  Created on: Apr 1, 2020
 *      Author: nxf46245
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

extern char * default_text;

void initDisplay(void);
void displayText(uint8_t locked, char * main_text, char * second_text);
bool isLocked(void);
void setLock(void);
void setUnlock(void);
void setSigfox(void);
void setNFC(void);
void setBattery(uint8_t battery);


#endif /* DISPLAY_H_ */
