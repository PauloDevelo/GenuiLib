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
#include "Gage.h"

namespace uilib{
int Gage::getCursor(int value){
	int cursor;
	float rate = (float)(value - _min)/(float)(_max - _min);
	if(isHorizontal()){
		rate *= (float)(getWidth() - 4);
		cursor = (int)(rate + 0.5) + getLeft() + 2;
	}
	else{
		rate *= (float)(getHeight() - 4);
		cursor = getTop() + getHeight() - 3 - (int)(rate + 0.5);
	}

	return cursor;
}

void Gage::drawStatic(){
	getGLCD()->drawRoundRect(getLeft(), getTop(), getLeft() + getWidth() - 1, getTop() + getHeight() - 1);
	_cursor = getCursor(_value.getValue());
	if(isHorizontal()){
		getGLCD()->fillRect(getLeft() + 2, getTop() + 2, _cursor, getTop() + getHeight() - 3);

		getGLCD()->setColor(_colorBck);
		getGLCD()->fillRect(_cursor, getTop() + 2, getLeft() + getWidth() - 3, getTop() + getHeight() - 3);
	}
	else{
		getGLCD()->fillRect(getLeft() + 2, _cursor , getLeft() + getWidth() - 3, getTop() + getHeight() - 3);

		getGLCD()->setColor(_colorBck);
		getGLCD()->fillRect(getLeft() + 2, getTop() + 2, getLeft() + getWidth() - 3, _cursor);
	}
}

void Gage::draw(){
		int newcursor = getCursor(_value.getValue());
		if(isHorizontal()){
			if(newcursor > _cursor){
				getGLCD()->fillRect(_cursor, getTop() + 2, newcursor, getTop() + getHeight() - 3);
			}
			else if(newcursor < _cursor){
				getGLCD()->setColor(_colorBck);
				getGLCD()->fillRect(newcursor, getTop() + 2, _cursor, getTop() + getHeight() - 3);
			}
		}
		else{
			if(newcursor < _cursor){
				getGLCD()->fillRect(getLeft() + 2, newcursor, getLeft() + getWidth() - 3, _cursor);
			}
			else if(newcursor > _cursor){
				getGLCD()->setColor(_colorBck);
				getGLCD()->fillRect(getLeft() + 2, _cursor, getLeft() + getWidth() - 3, newcursor);
			}
		}

		_cursor = newcursor;
}

void Gage::setHorizontal(bool isH){
	if(isH != isHorizontal()){
		if(isH){
			_state |= MASK_HORIZONTAL;
		}
		else{
			_state &= (~MASK_HORIZONTAL);
		}
		refresh();
	}
}
}
