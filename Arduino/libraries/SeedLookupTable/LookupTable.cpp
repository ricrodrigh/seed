/*
  LookupTable.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "LookupTable.h"

LookupTable::LookupTable(int mapSize) {
	_mapSize = mapSize;
	_arrayPointer = 0;
	
	_value = "SomeVal";
	_key = -1;
}

int LookupTable::getSize() {
	return _mapSize;
}

int LookupTable::getValue(const String &key) {
	Serial.print("Get key: ");
	Serial.println(key);
	for(int i = 0; i < _mapSize; i++) {
		Serial.print("\t ");
		Serial.print(i);
		Serial.print(":");
		if(_keySet[i] == key) {
			return _values[i];
		}
	}
	return _defaultValue;
}

void LookupTable::printValues() {
	Serial.println("Printing values");
	for(int i = 0; i < _mapSize; i++) {
		Serial.print("\t ");
		Serial.print(i);
		Serial.print(":");
		int value = _values[i];
		Serial.println(*value);
	}
}

boolean LookupTable::put(const String &key, int *pValue) {
	if(_arrayPointer < _mapSize) {
		_keySet[_arrayPointer] = key;
		//_values[_arrayPointer] = *pValue;
		_arrayPointer = _arrayPointer + 1;
		return true;
	}
	return false;
}

boolean LookupTable::put(const String &key) {
	if(_arrayPointer < _mapSize) {
		_keySet[_arrayPointer] = key;
		_arrayPointer = _arrayPointer + 1;
		return true;
	}
	return false;
}

const int LookupTable::_defaultValue = -1;
