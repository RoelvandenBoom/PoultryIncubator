/*
 * SR04.h
 *
 * Created: 21/10/2017 20:11:31
 *  Author: Roel
 */ 


#ifndef SR04_H_
#define SR04_H_

#include "Arduino.h"

unsigned long microseconds;

void startTimerISR(void );
void stopTimerISR(void );
void triggerUltrasonicMeasurement(void);



#endif /* SR04_H_ */