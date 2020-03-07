/*
 * epaper_2in13.h
 *
 *  Created on: Dec 19, 2019
 *      Author: nxf41657
 */

#ifndef EPAPER_2IN13_H_
#define EPAPER_2IN13_H_

// Display resolution
#define EPD_WIDTH       122
#define EPD_HEIGHT      250

#define FULL_UPDATE 0
#define PART_UPDATE 1

extern const unsigned char lut_full_update[];
extern const unsigned char lut_partial_update[];
extern unsigned char gImage_2in13[];
extern unsigned char nxp_image[];

unsigned char EPD_Init(const unsigned char);
void EPD_SendCommand(unsigned char);
void EPD_SendData(unsigned char);
void EPD_SetCommandMode(void);
void EPD_SetDataMode(void);
void EPD_Reset(void);
void EPD_WaitUntilIdle(void);
void EPD_TurnOnDisplay(void);
void EPD_SetWindows(int, int, int, int);
void EPD_Clear(void);
void EPD_Black(void);
void EPD_Display(unsigned char *);
void EPD_DisplayPart(unsigned char *);
void EPD_SetCursor(int, int);


#endif /* EPAPER_2IN13_H_ */
