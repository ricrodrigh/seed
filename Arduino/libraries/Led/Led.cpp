/*
  Copyright 2014 OllinLabs, Inc. or its affiliates. All Rights Reserved.
*/
#include "Arduino.h"
#include "Led.h"


Led::Led(byte pin){
	_pin = pin;
	_state = LOW;
	pinMode(_pin,OUTPUT);
}

boolean Led::getState() { 
	return _state; 
}

void Led::turnOn(){
	digitalWrite(_pin, HIGH);
	_state = HIGH;
}

void Led::turnOff(){
	digitalWrite(_pin, LOW);
	_state = LOW;
}
	
void Led::toggle(){
	_state ? turnOff() : turnOn();
}

void Led::blink(unsigned int time, byte times){
	for (byte i=0; i < times; i++){
		toggle();
		delay(time / 2);
		toggle();
		delay(time / 2);
	}
}

void Led::setPWMValue(byte val){
	analogWrite(_pin, val);
	val <= 127 ? _state = LOW : _state = HIGH;
}

void Led::fadeIn(unsigned int time){
	for (byte value = 0 ; value < 255; value += 5){ 
		analogWrite(_pin, value);
		delay(time/(255/5));
	} 
	turnOn();
}

void Led::fadeOut(unsigned int time){
	for (byte value = 255; value > 0; value -= 5){ 
		analogWrite(_pin, value); 
		delay(time/(255/5)); 
	}
	turnOff();
}