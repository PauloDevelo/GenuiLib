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
#ifndef float_h
#define float_h

#include "Arduino.h"

namespace Wrapper{
class Float{
private:
	const float* const _value;
	const char* _unit;
	mutable float valueDisplayed;
	const unsigned char _decPlaces;
	unsigned char _nbCarMax;

protected:
public:
	Float(const float* const value, unsigned char decimalPlaces, unsigned char nbCarMax, const char* unit = 0);

	boolean hasBeenModified()const{
		return valueDisplayed != *_value;
	}

	operator String()const;
};
}

#endif
