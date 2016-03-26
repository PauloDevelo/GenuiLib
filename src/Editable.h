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
#ifndef editable_h
#define editable_h

#include "AbstractGraphic.h"
#include "GenericContainer.h"

#include "Arduino.h"

namespace uilib{

class Editable : public AbstractGraphic{
private:
	static const unsigned char MASK_NOTIF	= 0b00100000;
	
	void (*_fp)(const Editable& sender);

	bool hasToNotify() const{
		return (_state & MASK_NOTIF);
	}

	void setNotification(bool notify){
		if(notify != hasToNotify()){
			if(notify){
				_state |= MASK_NOTIF;
			}
			else{
				_state &= (~MASK_NOTIF);
			}
		}
	}

protected:
	//Fonction notify devant être appelé dans le thread IHM car des mises à jour graphique peuvent éventuellement être effectuées
	//dans la fonction _fp.
	void notify(){
		if(hasToNotify() && _fp != 0){
			_fp(*this);
			setNotification(false);
		}
	}

	//Les fonctions decreaseValue et increaseValue peuvent être appelées en dehors du thread de l'IHM
	virtual void changeValue(bool dir) = 0;


public:
	Editable(byte colorBck = ColorManager::DEFAULTBACKCOLOR, byte colorFore = ColorManager::DEFAULTFORECOLOR):AbstractGraphic(true, colorBck, colorFore), _fp(0){
		setNotification(false);
	}

	virtual ~Editable(){
	}

	void decrease(){
		changeValue(false);
		setNotification(true);
		refresh();
	}
	
	void increase(){
		changeValue(true);
		setNotification(true);
		refresh();
	}

	void registerOnValueChange(void (*pf)(const Editable& sender)){
		if(_fp != 0){
			Serial.println(F("Editable::registerOnValueChange On ne peut inscrire qu'une seule fonction ..."));
		}
		_fp = pf;
	}
};

}

#endif
