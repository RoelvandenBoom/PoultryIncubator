/************************************************************************/
/* I2C Address ADS1115: 72
/* I2C Address HDC1080: 64 
/*                                                                     */
/************************************************************************/


/*Begining of Auto generated code by Atmel studio */
#include <Arduino.h>
#include <Wire.h>
#include "HDC1080.h"
#include "ADS1015.h"
#include "SR04.h"
#include "LCDPanel.h"


//Sample using LiquidCrystal library
#include <LiquidCrystal.h>
//#include <HDC1080.h>
//Beginning of Auto generated function prototypes by Atmel Studio
int read_LCD_buttons(void );
void configureADC(void);
void readADC(void);
void configureTimerInterrupts(void);
void runCursor(void);

//End of Auto generated function prototypes by Atmel Studio
void processButtonInput(void);
void configureHumiditySensor(void);
void readHumiditySensor(void);
void printTandRH(HDC1080_MeasurementResolution humidity, HDC1080_MeasurementResolution temperature);
void printRegister(HDC1080_Registers reg);




HDC1080 hdc1080;
ADS1115 ads;

unsigned int increment = 0;
LiquidCrystal lcddd = getLiquidCrystal();

void setup()
{
	configureTimerInterrupts();
	
	lcddd.begin(16, 2);              // start the library
	Wire.setClock(100000);
	Wire.begin();        // join i2c bus (address optional for master)
	Serial.begin(115200);
	while (!Serial) {
		; // wait for serial port to connect. Needed for native USB port only
	}
	
	hdc1080.begin(0x40);
	
	ads.setGain(GAIN_ONE);
	ads.begin();
	
	pinMode(3, OUTPUT);
	attachInterrupt(digitalPinToInterrupt(2), startTimerISR, RISING);
}

void loop()
{
	triggerUltrasonicMeasurement();

	processButtonInput();
	
	readHumiditySensor();
			
	readADC();
	
	delay(500);
}


void readADC(){
	
	 int16_t adc0, adc1, adc2, adc3;

	 adc0 = ads.readADC_SingleEnded(0) * 0.125;
	 adc1 = ads.readADC_SingleEnded(1) * 0.125;
	 adc2 = ads.readADC_SingleEnded(2) * 0.125;
	 adc3 = ads.readADC_SingleEnded(3) * 0.125;
	 
	 lcddd.setCursor(11,0);
	 lcddd.print("    ");
	 lcddd.setCursor(11,0);
	 lcddd.print(adc2);
	 
	 lcddd.setCursor(11,1);
	 lcddd.print("    ");
	 lcddd.setCursor(11,1);
	 lcddd.print(adc3);
}

void readHumiditySensor(void){
		hdc1080.setResolution(HDC1080_RESOLUTION_14BIT, HDC1080_RESOLUTION_14BIT);
		
		lcddd.setCursor(4,0);
		lcddd.print("      ");
		lcddd.setCursor(4,0);
		lcddd.print("T");
		lcddd.print(hdc1080.readTemperature());
		lcddd.setCursor(4,1);
		lcddd.print("      ");
		lcddd.setCursor(4,1);
		lcddd.print("H");
		lcddd.print(hdc1080.readHumidity());
}


void configureTimerInterrupts(){
	cli();//stop interrupts

	//set timer1 interrupt at 1Hz
	TCCR1A = 0;// set entire TCCR1A register to 0
	TCCR1B = 0;// same for TCCR1B
	TCNT1  = 0;//initialize counter value to 0
	// set compare match register for 1hz increments
	OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
	// turn on CTC mode
	TCCR1B |= (1 << WGM12);
	// Set CS12 and CS10 bits for 1024 prescaler
	TCCR1B |= (1 << CS12) | (1 << CS10);
	// enable timer compare interrupt
	TIMSK1 |= (1 << OCIE1A);

	sei();//allow interrupts
}

ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz
	runCursor();
}

void runCursor(){	
		lcddd.setCursor(15,0);
		
		switch(increment){
			case 0: lcddd.print("|");
			break;
			case 1: lcddd.print("/");
			break;
			case 2: lcddd.print("-");
			break;
			case 3: lcddd.print("\\");
		}
		
		increment++;
		if(increment == 3) increment = 0;
}