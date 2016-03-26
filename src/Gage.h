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
#ifndef gage_h
#define gage_h

#include "Integer.h"
#include "AbstractGraphic.h"
#include "Arduino.h"

namespace uilib{
class Gage : public AbstractGraphic{
private:
	static const unsigned char MASK_HORIZONTAL 	= 0b00010000;

	int _cursor;

	void setHorizontal(bool isHorizontal);

	int getCursor(int value);

protected:
	Wrapper::Integer<int>& _value;
	const unsigned int _width;
	const unsigned int _height;

	const int _min;
	const int _max;

	void drawStatic();
	void draw();

public:
	Gage(Wrapper::Integer<int>& value, bool isHorizontal, int valueMin, int valueMax, unsigned int width, unsigned int height, byte colorBkg = ColorManager::DEFAULTBACKCOLOR, byte colorFore = ColorManager::DEFAULTFORECOLOR):
		AbstractGraphic(false, colorBkg, colorFore), _cursor(0), _value(value), _width(width), _height(height), _min(valueMin), _max(valueMax){
		setHorizontal(isHorizontal);
	}

	bool hasToBeRefreshed()const{
		if(AbstractGraphic::hasToBeRefreshed()){
			return true;
		}
		else{
			return _value.hasBeenModified();
		}
	}

	unsigned int getHeight() const{return _height;}
	unsigned int getWidth() const{return _width;}

	boolean isHorizontal() const{
		return (_state & MASK_HORIZONTAL);
	}
};
}
#endif
