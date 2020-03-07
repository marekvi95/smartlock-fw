/*****************************************************************************
* | File      	:   GUI_Paint.h
* | Author      :   Waveshare team
* | Function    :	Achieve drawing: draw points, lines, boxes, circles and
*                   their size, solid dotted line, solid rectangle hollow
*                   rectangle, solid circle hollow circle.
* | Info        :
*   Achieve display characters: Display a single character, string, number
*   Achieve time display: adaptive size display time minutes and seconds
*----------------
* |	This version:   V2.0
* | Date        :   2018-11-15
* | Info        :
* 1.add: Paint_NewImage()
*    Create an image's properties
* 2.add: Paint_SelectImage()
*    Select the picture to be drawn
* 3.add: Paint_SetRotate()
*    Set the direction of the cache    
* 4.add: Paint_RotateImage() 
*    Can flip the picture, Support 0-360 degrees, 
*    but only 90.180.270 rotation is better
* 4.add: Paint_SetMirroring() 
*    Can Mirroring the picture, horizontal, vertical, origin
* 5.add: Paint_DrawString_CN() 
*    Can display Chinese(GB1312)    
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documnetation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to  whom the Software is
* furished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS OR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
******************************************************************************/
#ifndef __GUI_PAINT_H
#define __GUI_PAINT_H

#include "../Fonts/fonts.h"

/**
 * Image attributes
**/
typedef struct {
    unsigned char *Image;
    uint32_t Width;
    uint32_t Height;
    uint32_t WidthMemory;
    uint32_t HeightMemory;
    uint32_t Color;
    uint32_t Rotate;
    uint32_t Mirror;
    uint32_t WidthByte;
    uint32_t HeightByte;
} PAINT;
extern PAINT Paint;

/**
 * Display rotate
**/
#define ROTATE_0            0
#define ROTATE_90           90
#define ROTATE_180          180
#define ROTATE_270          270

/**
 * Display Flip
**/
typedef enum {
    MIRROR_NONE  = 0x00,
    MIRROR_HORIZONTAL = 0x01,
    MIRROR_VERTICAL = 0x02,
    MIRROR_ORIGIN = 0x03,
} MIRROR_IMAGE;
#define MIRROR_IMAGE_DFT MIRROR_NONE

/**
 * image color
**/
#define WHITE          0xFF
#define BLACK          0x00
#define RED            BLACK

#define IMAGE_BACKGROUND    WHITE
#define FONT_FOREGROUND     BLACK
#define FONT_BACKGROUND     WHITE

/**
 * The size of the point
**/
typedef enum {
    DOT_PIXEL_1X1  = 1,		// 1 x 1
    DOT_PIXEL_2X2  , 		// 2 X 2
    DOT_PIXEL_3X3  ,		// 3 X 3
    DOT_PIXEL_4X4  ,		// 4 X 4
    DOT_PIXEL_5X5  , 		// 5 X 5
    DOT_PIXEL_6X6  , 		// 6 X 6
    DOT_PIXEL_7X7  , 		// 7 X 7
    DOT_PIXEL_8X8  , 		// 8 X 8
} DOT_PIXEL;
#define DOT_PIXEL_DFT  DOT_PIXEL_1X1  //Default dot pilex

/**
 * Point size fill style
**/
typedef enum {
    DOT_FILL_AROUND  = 1,		// dot pixel 1 x 1
    DOT_FILL_RIGHTUP  , 		// dot pixel 2 X 2
} DOT_STYLE;
#define DOT_STYLE_DFT  DOT_FILL_AROUND  //Default dot pilex

/**
 * Line style, solid or dashed
**/
typedef enum {
    LINE_STYLE_SOLID = 0,
    LINE_STYLE_DOTTED,
} LINE_STYLE;

/**
 * Whether the graphic is filled
**/
typedef enum {
    DRAW_FILL_EMPTY = 0,
    DRAW_FILL_FULL,
} DRAW_FILL;

/**
 * Custom structure of a time attribute
**/
typedef struct {
    uint32_t Year;  //0000
    unsigned char  Month; //1 - 12
    unsigned char  Day;   //1 - 30
    unsigned char  Hour;  //0 - 23
    unsigned char  Min;   //0 - 59
    unsigned char  Sec;   //0 - 59
} PAINT_TIME;
extern PAINT_TIME sPaint_time;

//init and Clear
void Paint_NewImage(unsigned char *image, uint32_t Width, uint32_t Height, uint32_t Rotate, uint32_t Color);
void Paint_SelectImage(unsigned char *image);
void Paint_SetRotate(uint32_t Rotate);
void Paint_SetMirroring(unsigned char mirror);
void Paint_SetPixel(uint32_t Xpoint, uint32_t Ypoint, uint32_t Color);

void Paint_Clear(uint32_t Color);
void Paint_ClearWindows(uint32_t Xstart, uint32_t Ystart, uint32_t Xend, uint32_t Yend, uint32_t Color);

//Drawing
void Paint_DrawPoint(uint32_t Xpoint, uint32_t Ypoint, uint32_t Color, DOT_PIXEL Dot_Pixel, DOT_STYLE Dot_FillWay);
void Paint_DrawLine(uint32_t Xstart, uint32_t Ystart, uint32_t Xend, uint32_t Yend, uint32_t Color, LINE_STYLE Line_Style, DOT_PIXEL Dot_Pixel);
void Paint_DrawRectangle(uint32_t Xstart, uint32_t Ystart, uint32_t Xend, uint32_t Yend, uint32_t Color, DRAW_FILL Filled , DOT_PIXEL Dot_Pixel);
void Paint_DrawCircle(uint32_t X_Center, uint32_t Y_Center, uint32_t Radius, uint32_t Color, DRAW_FILL Draw_Fill , DOT_PIXEL Dot_Pixel);

//Display string
void Paint_DrawChar(uint32_t Xstart, uint32_t Ystart, const char Acsii_Char, sFONT* Font, uint32_t Color_Background, uint32_t Color_Foreground);
void Paint_DrawString_EN(uint32_t Xstart, uint32_t Ystart, const char * pString, sFONT* Font, uint32_t Color_Background, uint32_t Color_Foreground);
void Paint_DrawString_CN(uint32_t Xstart, uint32_t Ystart, const char * pString, cFONT* font, uint32_t Color_Background, uint32_t Color_Foreground);
void Paint_DrawNum(uint32_t Xpoint, uint32_t Ypoint, int32_t Nummber, sFONT* Font, uint32_t Color_Background, uint32_t Color_Foreground);
void Paint_DrawTime(uint32_t Xstart, uint32_t Ystart, PAINT_TIME *pTime, sFONT* Font, uint32_t Color_Background, uint32_t Color_Foreground);

//pic
void Paint_DrawBitMap(const unsigned char* image_buffer);


#endif




