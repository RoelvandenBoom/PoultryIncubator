/*
 * SR04.cpp
 *
 * Created: 21/10/2017 20:10:06
 *  Author: Roel
 */ 
#include "SR04.h"
#include "LCDPanel.h"

LiquidCrystal lcdd = getLiquidCrystal();

void triggerUltrasonicMeasurement(void){
	digitalWrite(3, HIGH);
	delayMicroseconds(100);
	digitalWrite(3, LOW);
	delay(300);
}

void startTimerISR(void){
	microseconds = micros();
	detachInterrupt(digitalPinToInterrupt(2));
	attachInterrupt(digitalPinToInterrupt(2), stopTimerISR, FALLING);
}

void stopTimerISR(void){
	unsigned long timePassed = micros() - microseconds;
	unsigned long distance = (timePassed * 170) / 10000;
	lcdd = getLiquidCrystal();
	lcdd.setCursor(0,0);
	lcdd.print("    ");
	lcdd.setCursor(0,0);
	lcdd.print(distance);
	detachInterrupt(digitalPinToInterrupt(2));
	attachInterrupt(digitalPinToInterrupt(2), startTimerISR, RISING);
}