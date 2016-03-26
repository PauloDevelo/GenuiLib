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

#include "GridLayout.h"

namespace uilib{

void GridLayout::addGraphic(AbstractGraphic *graphic){
	addGraphic(graphic, false);
}

void GridLayout::addGraphic(AbstractGraphic *graphic, bool centered){
	if(graphic == 0){
		//Ajout d'un blanc ...
		Serial.println("Ajout d'un blanc.");
	}
	else{
		//1er test on test la largeur de l'élément à insérer
		if(graphic->getWidth() > _widthCol){
			Serial.print(F("GridLayout::addGraphic L'élément graphic à ajouter ne peut être plus large que les colonnes du GridLayout. Graphic width :"));
			Serial.print(String(graphic->getWidth()));
			Serial.print(F(" GridLayout width :"));
			Serial.println(String(_widthCol));
			return;
		}

		if(graphic->getHeight() > _heightLine){
			Serial.println(F("GridLayout::addGraphic L'élément graphic à ajouter ne peut être plus haut que les lignes du GridLayout."));
			return;
		}

		if(_currj >= _nbLine){
			Serial.println(F("GridLayout::addGraphic Il n'y a plus de place dans le GridLayout"));
			return;
		}

		int gapH = 0;
		int gapV = 0;
		if(centered){
			gapH = (_widthCol - graphic->getWidth()) / 2;
			gapV = (_heightLine - graphic->getHeight()) / 2;
		}
		
		graphic->setLeft(getLeft() + _curri * _widthCol + gapH);
		graphic->setTop(getTop() + _currj * _heightLine + gapV);
		

		GraphicContainer::addGraphic(graphic);
	}

	_curri += 1;

	if(_curri == _nbCol){
		_currj += 1;
		_curri = 0;
	}
}

}
