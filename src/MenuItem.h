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

#ifndef menuitem_h
#define menuitem_h

#include "GenEditable.h"
#include "GenericContainer.h"
#include "AbstractGraphic.h"
#include "GLCDWrapper.h"
#include "Arduino.h"

namespace uilib{
template<class V, class T> class MenuItem : public GenEditable<V, T>{
private:
	typedef GenEditable<V, T> Base;

	byte _width;

protected:

	void draw(){
		Base::getGLCD()->setFont(GLCDWrapper::TypeSmallFont);
		Base::getGLCD()->print(Base::getData(), Base::getLeft() + 1, Base::getTop() + 1);
		Base::getGLCD()->drawRect(Base::getLeft(), Base::getTop(), Base::getLeft() + getWidth() - 1, Base::getTop() + getHeight() - 1);

		Base::notify();
	}

public:
	MenuItem(byte capacity, byte nbCar, byte colorBck = ColorManager::DEFAULTBACKCOLOR, byte colorFore = ColorManager::DEFAULTFORECOLOR):
		Base(capacity, colorBck, colorFore){
		_width = 2 + nbCar * AbstractGraphic::getGLCD()->get_W_SF();
	}

	unsigned int getHeight()const {
		return AbstractGraphic::getGLCD()->get_H_SF() + 2;
	}

	unsigned int getWidth()const {
		return _width;
	}

	~MenuItem(){
	}
};
}

#endif
