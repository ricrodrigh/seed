/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef LookupTable_h
#define LookupTable_h

#include "Arduino.h"

class LookupTable 
{
	public:
		LookupTable(int mapSize);
		int getSize();
		int getValue(const String &key);
		boolean put(const String &key, int *pValue);
	private:
		int _mapSize;
};

#endif
