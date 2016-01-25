/**
 * @file        lcd.cpp
 * @brief       simple LCD driver module
 */

#include "stm324xg_eval_lcd.h"

volatile uint16_t TextColor, BackColor; // globals needed by LCD driver

/** @brief LCD initialization
 *
 * needs to be once called before theLCD screen can be used
 *  */
void lcd_init( void)
{
  /* Initialize the LCD */
	BSP_LCD_Init();

    /* Clear the LCD */
	BSP_LCD_Clear(LCD_COLOR_YELLOW);

    /* Set the LCD Back Color */
	BSP_LCD_SetBackColor(LCD_COLOR_YELLOW);

    /* Set the LCD Text Color */
	BSP_LCD_SetTextColor(LCD_COLOR_BLUE);
}

/** @brief write a single line of text on the LCD */
void lcd_write_line( unsigned line, char * text)
{
	BSP_LCD_DisplayStringAtLine( LINE(line), (uint8_t *)text);
}
