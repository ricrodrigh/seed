/*
  LookupTable.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "LookupTable.h"

LookupTable::LookupTable(int mapSize) {
	_mapSize = mapSize;
}

int LookupTable::getSize() {
	return _mapSize;
}
