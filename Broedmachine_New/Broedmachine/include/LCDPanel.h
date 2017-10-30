/*
 * LCDPanel.h
 *
 * Created: 21/10/2017 20:15:56
 *  Author: Roel
 */ 


#ifndef LCDPANEL_H_
#define LCDPANEL_H_

#include "Arduino.h"
#include "LiquidCrystal.h"
// select the pins used on the LCD panel




// define some values used by the panel and buttons
int lcd_key     = 0;
int adc_key_in  = 0;
#define btnRIGHT  0
#define btnUP     1
#define btnDOWN   2
#define btnLEFT   3
#define btnSELECT 4
#define btnNONE   5
#define ULTRATRIG 3

void processButtonInput(void);
int read_LCD_buttons(void);
LiquidCrystal getLiquidCrystal(void);

#endif /* LCDPANEL_H_ */