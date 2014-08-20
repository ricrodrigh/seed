/*
  LookupTable.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "LookupTable.h"

const int LookupTable::_defaultValue = -1;
int values_array[10] = {};

LookupTable::LookupTable(int mapSize) {
	_mapSize = mapSize;
	_arrayPointer = 0;

	_key = "SomeKey";	
	_value = -1;

	_values = values_array;
}

int LookupTable::getSize() {
	// Serial.print("Map size: ");
	// Serial.println(_mapSize);
	return _mapSize;
}

String & LookupTable::getKey(String &key) {
	// Serial.print("Input key: ");
	// Serial.println(key);

	// Serial.print("Table key: ");
	// Serial.println(_key);
	return _key;
}

int LookupTable::getValue() {
	// Serial.print("Table val: ");
	// Serial.println(_value);
	return _value;
}

int LookupTable::getValue(int index) {
	int value = _values[index];
	// Serial.print("-Input index");
	// Serial.println(index);
	// Serial.print("- Val in array ");
	// Serial.println(value);
	// Serial.print("- Val in array[] ");
	// Serial.println(_values[index]);
	return value;
}

boolean LookupTable::setKey(String &key) {
	// Serial.print("Input key: ");
	// Serial.println(key);
	_key = key;
	return false;
}

boolean LookupTable::setValue(int value) {
	// Serial.print("Input value: ");
	// Serial.println(value);
	_value = value;
	return false;
}

//http://stackoverflow.com/questions/3749660/how-to-resize-array-in-c
