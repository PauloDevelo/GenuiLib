/*
 *
 * This file is a part of my arduino development.
 * If you make any modifications or improvements to the code, I would
 * appreciate that you share the code with me so that I might include
 * it in the next release. I can be contacted through paul.torruella@gmail.com

 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU GENERAL PUBLIC LICENSE 3.0 license.
 * Please see the included documents for further information.

 * Commercial use of this file and/or every others file from this library requires
 * you to buy a license that will allow commercial use. This includes using the code,
 * modified or not, as a tool to sell products.

 *  The license applies to this file and its documentation.
 *
 *  Created on: 23 févr. 2016
 *  Author: Paul TORRUELLA
 */

#ifndef stringwrapper_h
#define stringwrapper_h

#include "Arduino.h"

#ifdef DEBUG
#define DEBUGSTRINGWRAPPER
#endif

//#define DEBUGSTRINGWRAPPER

namespace Wrapper{
class StringWrapper{
private:
	const String* const _value;
	mutable String valueDisplayed;
	const unsigned char _nbMaxCar;

protected:
public:
	StringWrapper(const String* const value, unsigned char nbMaxCar):_value(value), _nbMaxCar(nbMaxCar){
		#ifdef DEBUGSTRINGWRAPPER
		Serial.print(F("StringWrapper("));Serial.print((int)value);Serial.println(String(", ") + nbMaxCar + ")-->" + (int)this);
		Serial.println(*value);
		#endif
		
	}

	boolean hasBeenModified()const{
		#ifdef DEBUGSTRINGWRAPPER
		Serial.println(F("StringWrapper::hasBeenModified()"));
		#endif

		#ifdef DEBUGSTRINGWRAPPER
		Serial.print(F("StringWrapper::hasBeenModified()-->"));Serial.println((bool)(valueDisplayed != *_value));
		#endif

		return valueDisplayed != *_value;
	}

	operator String()const{
		#ifdef DEBUGSTRINGWRAPPER
		Serial.println(F("StringWrapper::String()"));
		#endif

		#ifdef DEBUGSTRINGWRAPPER
		Serial.print(F("StringWrapper::String()-->"));Serial.println(_value->substring(0, _nbMaxCar));
		#endif

		valueDisplayed = _value->substring(0, _nbMaxCar);
		return valueDisplayed;
	}
};
}

#endif
