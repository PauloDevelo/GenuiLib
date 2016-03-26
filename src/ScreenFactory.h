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

#ifndef SCREENFACTORY_H_
#define SCREENFACTORY_H_

#include "GLCDWForU8GLIB.h"
#include "GLCDWForUTFT.h"

namespace uilib{

class ScreenFactory{

public:
	enum ScreenType{
		ILI9341,
		ST7920
	};

	static GLCDWrapper* buildScreen(ScreenType type){
		if(type == ILI9341){
			UTFT* utft = new UTFT(ILI9341_S5P, 9, 8, 12, 11, 10);
			utft->InitLCD();
			return new GLCDWForUTFT(utft);
		}
		if(type == ST7920){
			U8GLIB* u8glib = new U8GLIB_ST7920_128X64_4X(8, 9, 10, 11, 4, 5, 6, 7, 18, 17, 16);
			return new GLCDWForU8GLIB(u8glib);
		}
		else{
			return 0;
		}
	}
};

}

#endif /* SCREENFACTORY_H_ */
