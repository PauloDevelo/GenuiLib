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

#include "AbstractGraphic.h"

namespace uilib{

GLCDWrapper* AbstractGraphic::myGLCD = 0;
void AbstractGraphic::initAbstractGraphicClass(GLCDWrapper* screen){
	AbstractGraphic::myGLCD = screen;
}

byte AbstractGraphic::getForegroundColor()const{
	byte idColorFore;
	if(isVisible()){
		if(isEnable()){
			if(isSelected()){
				idColorFore = _colorBck;
			}
			else{
				idColorFore = _colorFore;
			}
		}
		else{
			idColorFore = ColorManager::DEFAULTENABLECOLOR;
		}
	}
	else{
		idColorFore = ColorManager::APPBCKCOLOR;
	}

	return idColorFore;
}


byte AbstractGraphic::getBackgroundColor()const{
	byte idColorBack;
	if(isVisible()){
		if(isEnable()){
			if(isSelected()){
				idColorBack = _colorFore;
			}
			else{
				idColorBack = _colorBck;
			}
		}
		else{
			idColorBack = ColorManager::APPBCKCOLOR;
		}
	}
	else{
		idColorBack = ColorManager::APPBCKCOLOR;
	}

	return idColorBack;
}

void AbstractGraphic::redraw(long){
	if(hasToBeRefreshed() || !getGLCD()->allowLocalRefresh()){

		byte idColorFore;
		byte idColorBack;

		if(isVisible()){
			if(isEnable()){
				if(isSelected()){
					idColorFore = _colorBck;
					idColorBack = _colorFore;
				}
				else{
					idColorFore = _colorFore;
					idColorBack = _colorBck;
				}
			}
			else{
				idColorFore = ColorManager::DEFAULTENABLECOLOR;
				idColorBack = ColorManager::APPBCKCOLOR;
			}
		}
		else{
			idColorFore = ColorManager::APPBCKCOLOR;
			idColorBack = ColorManager::APPBCKCOLOR;
		}
		
		myGLCD->setColor(idColorFore);
		myGLCD->setBackColor(idColorBack);

		//Permet d'éviter de redessiner à chaque fois la partie statique d'un element graphique.
		//La partie graphique static d'un élément graphique ne devrait être dessiné qu'une seule fois au début 
		//et à chaque modification de la visibilite/enable/select ...
		if(staticHasToBeRefreshed() || !getGLCD()->allowLocalRefresh()){
			drawStatic();
			_state &= (~MASK_REFRESH_STATIC);
		}

		draw();
		_state &= (~MASK_REFRESH_DYNAMIC);
	}
}

}
