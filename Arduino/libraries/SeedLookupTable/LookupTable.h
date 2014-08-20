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
		
		int getValue();
		String & getKey(String &key);
		
		boolean setValue(int value);
		boolean setKey(String &key);

		int getValue(int index);

	private:
		int _mapSize;
		int _arrayPointer;
		
		String _key;
		int _value;
		
		int* _values;

		static const int _defaultValue;
};

#endif
