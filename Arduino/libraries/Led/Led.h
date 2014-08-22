/*
  Copyright 2014 OllinLabs, Inc. or its affiliates. All Rights Reserved.
*/
#ifndef Led_h
#define Led_h

#include "Arduino.h" 

/*
Represents an Arduino controlable LED

@author: Ricardo Rodriguez
*/
class Led{
	public:
		Led(byte pin);
		boolean getState();
    	void turnOn();
		void turnOff();
		void toggle();
		void blink(unsigned int time, byte times=1);
		void setPWMValue(byte val);
		void fadeIn(unsigned int time);
		void fadeOut(unsigned int time);
  	private:
		boolean _state;
		byte _pin;

};

#endif