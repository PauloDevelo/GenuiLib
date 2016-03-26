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


#include "Arduino.h"
#include "GLCDWForU8GLIB.h"

namespace uilib{

/**
 * Example of a U8GLIB building :
 * U8GLIB* u8glib = new U8GLIB_ST7920_128X64_4X(8, 9, 10, 11, 4, 5, 6, 7, 18, 17, 16);
 */
GLCDWForU8GLIB::GLCDWForU8GLIB(U8GLIB* screen):GLCDWrapper(), _u8glib(screen), bckColor(0){

	setFont(TypeSmallFont);
	getU8GLIB()->setFontRefHeightAll();
	getU8GLIB()->setDefaultForegroundColor();
	getU8GLIB()->setDefaultBackgroundColor();
	getU8GLIB()->setFontPosTop();

	clrScr();
}

GLCDWForU8GLIB::~GLCDWForU8GLIB()
{
	delete _u8glib;
	_u8glib = 0;
}

void GLCDWForU8GLIB::setFont(FontType font){
	#ifdef DEBUG
	Serial.print(F("setFont-->"));Serial.println(font);
	#endif

	if(font == TypeBigFont){
		getU8GLIB()->setFont(u8g_font_6x10);
	}
	else if(font == TypeSmallFont){
		getU8GLIB()->setFont(u8g_font_4x6);
	}

	getU8GLIB()->setFontRefHeightAll();
	getU8GLIB()->setFontPosTop();

	_fontType = font;

	#ifdef DEBUG
	Serial.println(F("<--setFont"));
	#endif
}
}





