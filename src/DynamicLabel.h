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
#ifndef dynamiclabel_h
#define dynamiclabel_h

#include "Label.h"
#include "Arduino.h"

namespace uilib{
//Le type T doit être capable d'être casté en String !
template<class T> class DynamicLabel : public Label<T>{
private:
protected:
	bool hasToBeRefreshed()const{
		if(AbstractGraphic::hasToBeRefreshed()){
			return true;
		}
		else{
			return Label<T>::_value.hasBeenModified();
		}
	}
	
public:
	DynamicLabel(T pstr, bool isSelectionnable = false, enum GLCDWrapper::FontType fontType = GLCDWrapper::TypeSmallFont, byte colorBck = ColorManager::DEFAULTBACKCOLOR, byte colorFore = ColorManager::DEFAULTFORECOLOR):
		Label<T>(pstr, isSelectionnable, fontType, colorBck, colorFore){
	}

	DynamicLabel(T pstr, byte colorBck, byte colorFore, bool isSelectionnable = false):
		Label<T>(pstr, colorBck, colorFore, isSelectionnable){
	}

	~DynamicLabel(){
	}
};
}
#endif
