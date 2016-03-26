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

#include "NMEASticker.h"

namespace uilib{
void NMEASticker::save(bool hasToBeSaved){
	if(hasToBeSaved != isSaving()){
		if(hasToBeSaved){
			_state |= MASK_SAVING;
		}
		else{
			_state &= (~MASK_SAVING);
		}
	}
}

void NMEASticker::draw(){
	getGLCD()->setFont(GLCDWrapper::TypeSmallFont);
	getGLCD()->print(_label, getLeft() + 1, getTop() + 1);

	if(isSaving() && isVisible()){
		getGLCD()->setColor(ColorManager::RED);
	}
	getGLCD()->drawRoundRect(getLeft(), getTop(), getLeft() + getWidth() - 1, getTop() + getHeight() - 1);

	notify();
}
}
