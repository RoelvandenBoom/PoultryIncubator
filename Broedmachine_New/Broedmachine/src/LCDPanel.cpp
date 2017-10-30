/*
 * LCDPanel.cpp
 *
 * Created: 21/10/2017 20:15:44
 *  Author: Roel
 */ 

#include "LCDPanel.h"

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

void processButtonInput(void){
	lcd.setCursor(0,1);            // move to the begining of the second line
	noInterrupts();
	lcd_key = read_LCD_buttons();  // read the buttons

	switch (lcd_key)               // depending on which button was pushed, we perform an action
	{
		case btnRIGHT:
		{
			lcd.print("RIGHT ");
			break;
		}
		case btnLEFT:
		{
			lcd.print("LEFT   ");
			break;
		}
		case btnUP:
		{
			lcd.print("UP    ");
			break;
		}
		case btnDOWN:
		{
			lcd.print("DOWN  ");
			break;
		}
		case btnSELECT:
		{
			lcd.print("SELECT");
			break;
		}
		case btnNONE:
		{
			lcd.print("NONe  ");
			break;
		}
	}
	interrupts();
}

// read the buttons
int read_LCD_buttons(void)
{
	adc_key_in = analogRead(0);      // read the value from the sensor
	// my buttons when read are centered at these values: 0, 144, 329, 504, 741
	// we add approx 50 to those values and check to see if we are close
	if (adc_key_in > 1000) return btnNONE; // We make this the 1st option for speed reasons since it will be the most likely result
	// For V1.1 us this threshold
	if (adc_key_in < 50)   return btnRIGHT;
	if (adc_key_in < 250)  return btnUP;
	if (adc_key_in < 450)  return btnDOWN;
	if (adc_key_in < 650)  return btnLEFT;
	if (adc_key_in < 850)  return btnSELECT;

	return btnNONE;  // when all others fail, return this...
}

LiquidCrystal getLiquidCrystal(){
	return lcd;
}