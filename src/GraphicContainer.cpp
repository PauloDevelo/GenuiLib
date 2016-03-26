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

#include "GraphicContainer.h"

namespace uilib{

bool GraphicContainer::hasToBeRefreshed()const{
	bool hasToBeRefr = false;

	Generic_Container::Fifo<AbstractGraphic>::iterator it = begin();
	while(!hasToBeRefr && it != end()){
		hasToBeRefr |= it->hasToBeRefreshed();
		it++;
	}

	return hasToBeRefr;
}

void GraphicContainer::addGraphic(AbstractGraphic *graphic){
	_gList.add(graphic);

	if(graphic->isSelectionnable() && graphic->isVisible() && graphic->isEnable() && graphic->isSelected()){
		if(*_selection != 0 && !allowMultipleSelection()){
			_selection->select(false);
		}
		_selection = _gList.last();
	}
}

/**
 * Permet de supprimer u graphic de la liste des composants. Attention, contrairement à la fonction removeAll, cette fonction ne libère
 * pas la mémoire allouée par le graphic, mais retourne le pointeur de l'élément graphic supprimé.
 */
AbstractGraphic* GraphicContainer::remove(AbstractGraphic* graphic){
	if(_gList.remove(graphic)){
		graphic->setVisible(false);
		graphic->redraw();
		return graphic;
	}
	else{
		return 0;
	}
}


void GraphicContainer::removeAll(){
	AbstractGraphic* graphic = _gList.pop();
	while(graphic != 0){
		graphic->setVisible(false);
		graphic->redraw();
		
		delete graphic;
		graphic = _gList.pop();
	}

	_selection = _gList.begin();

}

void GraphicContainer::redraw(long milliAvailable){
	typedef Generic_Container::Fifo<AbstractGraphic>::iterator IT;

	unsigned long debut = millis();
	IT it = _gList.begin();
	IT end = _gList.end();

	while(it != end && (milliAvailable == -1 || milliAvailable > (long)(millis() - debut))) {
		it->redraw();
		it++;
	}
}

void GraphicContainer::setVisible(bool visible){
	typedef Generic_Container::Fifo<AbstractGraphic>::iterator IT;

	IT it = _gList.begin();
	IT end = _gList.end();

	while(it != end) {
		it->setVisible(visible);
		it++;
	}
}

void GraphicContainer::setEnable(bool enable){
	typedef Generic_Container::Fifo<AbstractGraphic>::iterator IT;

	IT it = _gList.begin();
	IT end = _gList.end();

	while(it != end) {
		it->setEnable(enable);
		it++;
	}
}

AbstractGraphic* GraphicContainer::changeSelection(){
	if(_gList.isEmpty())return 0;
	
	Generic_Container::Fifo<AbstractGraphic>::iterator first(_selection != _gList.end()?_selection:_gList.begin());

	Generic_Container::Fifo<AbstractGraphic>::iterator next(_selection);
	if(next == _gList.end())
		next = _gList.begin();
	else{
		next++;
		if(next == _gList.end())next = _gList.begin();
	}

	while(next != first && (!next->isSelectionnable() || !next->isEnable() || !next->isVisible())){
		next++;
		if(next == _gList.end())next = _gList.begin();
	}

	if(_selection != _gList.end())
		_selection->select(false);
	
	if(next != _gList.end()){
		next->select(true);
		_selection = next;
	}

	return *_selection;
}

}
