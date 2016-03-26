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

#include "GLCDWForUTFT.h"

//#define DEBUG 1

// Declare which fonts we will be using
extern uint8_t SmallFont[];
// Declare which fonts we will be using
extern uint8_t BigFont[];

namespace uilib{

/**
 * Building example for an instance of UTFT :
 * _utft = new UTFT(ILI9341_S5P, ld_mosi, ld_sck, ld_cs, ld_reset, ld_dc);
 * _utft->InitLCD();
 */
GLCDWForUTFT::GLCDWForUTFT(UTFT* utft):GLCDWrapper(), _utft(utft){
	setColor(ColorManager::APPBCKCOLOR);
	_utft->fillRect(0, 0, GLCDWForUTFT::W_SCREEN - 1, GLCDWForUTFT::H_SCREEN - 1);
}

GLCDWForUTFT::~GLCDWForUTFT()
{
	delete _utft;
	_utft = 0;
}

void GLCDWForUTFT::setFont(FontType font){
	if(font == TypeBigFont){
		getUTFT()->setFont(BigFont);
	}
	else if(font == TypeSmallFont){
		getUTFT()->setFont(SmallFont);
	}
}
}

