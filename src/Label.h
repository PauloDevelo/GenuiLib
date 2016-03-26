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
 *  Created on: 23 f�vr. 2016
 *  Author: Paul TORRUELLA
 */

#ifndef label_h
#define label_h

#include "AbstractGraphic.h"
#include "Arduino.h"

namespace uilib{
	
//Le type T doit être capable d'être casté en const String & !
template<class T> class Label : public AbstractGraphic{
private:
	static const unsigned char MASK_ISCENTERED 	= 0b00010000;

	void initDefaultDimension(){
		String lab(_value);
		_width = lab.length() * (_fontType == GLCDWrapper::TypeSmallFont?getGLCD()->get_W_SF():getGLCD()->get_W_BF());
	}
protected:
	const enum GLCDWrapper::FontType _fontType;
	T _value;
	unsigned int _width;
	
	void draw();
	
public:

	Label(T pstr, bool isSelectionnable = false, enum GLCDWrapper::FontType fontType = GLCDWrapper::TypeSmallFont, byte colorBck = ColorManager::DEFAULTBACKCOLOR, byte colorFore = ColorManager::DEFAULTFORECOLOR):
		AbstractGraphic(isSelectionnable, colorBck, colorFore), _fontType(fontType), _value(pstr){
		initDefaultDimension();
	}

	Label(T pstr, byte colorBck, byte colorFore, bool isSelectionnable = false):
		AbstractGraphic(isSelectionnable, colorBck, colorFore), _fontType(GLCDWrapper::TypeSmallFont), _value(pstr){
			initDefaultDimension();
	}

	unsigned int getHeight()const{
		if(_fontType == GLCDWrapper::TypeSmallFont)
			return getGLCD()->get_H_SF();
		else if(_fontType == GLCDWrapper::TypeBigFont){
			return getGLCD()->get_H_BF();
		}
		else{
			Serial.println("Unknown font type");
			return 0;
		}
	}
	
	unsigned int getWidth()const{return _width;}
	void setWidth(unsigned int width){_width = width;}

	bool isCentered()const{
		return (_state & MASK_ISCENTERED);
	}
	void setCentered(bool centered){
		if(centered != isCentered()){
			if(centered){
				_state |= MASK_ISCENTERED;
			}
			else{
				_state &= (~MASK_ISCENTERED);
			}
			refresh();
		}
	}

	T getValue(){
		return _value;
	}
};


template<class T> void Label<T>::draw(){
	if(!getGLCD()->allowLocalRefresh() && !isVisible()){
		return;
	}

	String strToDisplay(_value);

	unsigned int widthCar;
	if(_fontType == GLCDWrapper::TypeSmallFont){
		widthCar = getGLCD()->get_W_SF();
	}
	else{
		widthCar = getGLCD()->get_W_BF();
	}

	unsigned int widthStr = widthCar * strToDisplay.length();
	if(getWidth() < widthStr){
		unsigned int nbCarAllowed = getWidth()/widthCar;
		if(nbCarAllowed > 2){
			strToDisplay = strToDisplay.substring(0, nbCarAllowed - 2);
			strToDisplay += F("..");
		}
		else{
			strToDisplay = strToDisplay.substring(0, nbCarAllowed);
		}
		widthStr = nbCarAllowed * widthCar;
	}


	getGLCD()->setFont(_fontType);

	if(isCentered()){
		unsigned int gapSize = (getWidth() - widthStr) / 2;
		getGLCD()->print(strToDisplay, getLeft() + gapSize - 1, getTop());

		byte foreColor = getForegroundColor();
		byte backColor = getBackgroundColor();

		getGLCD()->setColor(backColor);
		getGLCD()->fillRect(getLeft(), getTop(), getLeft() + gapSize - 2, getTop() + getHeight() - 1);
		getGLCD()->fillRect(getLeft() + widthStr + gapSize - 1, getTop(), getLeft() + getWidth() - 1, getTop() + getHeight() - 1);
		getGLCD()->setColor(foreColor);
	}
	else{
		getGLCD()->print(strToDisplay, getLeft(), getTop());

		if(widthStr < getWidth()){
			byte foreColor = getForegroundColor();
			byte backColor = getBackgroundColor();

			getGLCD()->setColor(backColor);
			getGLCD()->fillRect(getLeft() + widthStr, getTop(), getLeft() + getWidth() - 1, getTop() + getHeight() - 1);
			getGLCD()->setColor(foreColor);
		}
	}
}
}

#endif
