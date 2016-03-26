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

#ifndef integer_h
#define integer_h

#include "Arduino.h"

namespace Wrapper{
template<class T> class Integer{
private:
	const T* const _value;
	const char* _unit;
	const byte _exp;
	mutable T valueDisplayed;

protected:
public:

	Integer(const T* const value, const char* unit = 0, byte exp = 0):_value(value), _unit(unit), _exp(exp), valueDisplayed(0){

	}

	boolean hasBeenModified()const{
		return valueDisplayed != *_value;
	}

	T getValue()const{
		long pow = 1;
		for(int i = 0; i < _exp; i++){
			pow *= 10;
		}

		valueDisplayed = *_value;

		return (pow / 2 + *_value) / pow;
	}

	operator String()const{
		String retour(getValue());
		if(_unit != 0){
			retour += _unit;
		}

		return retour;
	}
};
}

#endif
