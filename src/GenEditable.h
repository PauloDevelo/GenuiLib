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

#ifndef GENEDITABLE_H_
#define GENEDITABLE_H_

#include "GenericContainer.h"
#include "Editable.h"

#include "Arduino.h"

namespace uilib{

template<class V, class T> class GenEditable : public Editable{
private:
	typedef Generic_Container::Pair<V, T> GenericPair;
	Generic_Container::TabPtr<GenericPair>* _tabKeyValue;

	typedef typename Generic_Container::TabPtr<GenericPair>::circularIterator CIT;
	CIT _it;
protected:
	//Les fonctions decreaseValue et increaseValue peuvent être appelées en dehors du thread de l'IHM
	void changeValue(bool dir){
		if(dir)
			_it++;
		else
			_it--;
		//On ne peut pas appeler la fonction de notification car on risquerait de bloquer l'application trop longtemps ...
	}

public:
	GenEditable(byte capacity, byte colorBck = ColorManager::DEFAULTBACKCOLOR, byte colorFore = ColorManager::DEFAULTFORECOLOR):Editable(colorBck, colorFore){
		_tabKeyValue = new Generic_Container::TabPtr<GenericPair>(capacity);
		_it = _tabKeyValue->begin();
	}

	virtual ~GenEditable(){
		delete _tabKeyValue;
		_tabKeyValue = 0;
		_it = CIT();
	}



	void addValue(V value, T sticker){
		GenericPair *cp = new GenericPair(value, sticker);
		_tabKeyValue->add(cp);
	}

	V getValue() const{
		return _it->_value;
	}

	T getData()const{
		return _it->getData();
	}
};
}


#endif /* GENEDITABLE_H_ */
