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

#ifndef nmeasticker_h
#define nmeasticker_h

#include "Editable.h"
#include "AbstractGraphic.h"
#include "GLCDWrapper.h"
#include "Arduino.h"

namespace uilib{
class NMEASticker : public Editable{
private:
	static const unsigned char MASK_SAVING 	= 0b00010000;
	const String& _label;
	
	void draw();
	void save(bool hasToBeSaved);

	byte _width;
	
protected:

	void changeValue(bool){
		save(!isSaving());
	}
	
public:
	NMEASticker(const String& label):
		Editable(), _label(label){
		_width = label.length() * (byte)getGLCD()->get_W_SF() + 2;
		}

	const String& getSticker(){
		return _label;
	}

	unsigned int getHeight()const{
		return getGLCD()->get_H_SF() + 2;
	}

	unsigned int getWidth()const{
		return _width;
	}

	boolean isSaving() const{
		return (_state & MASK_SAVING);
	}
};
}

#endif
