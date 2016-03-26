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

#ifndef gridlayout_h
#define gridlayout_h

#include "GraphicContainer.h"
#include "GLCDWrapper.h"
#include "Arduino.h"

namespace uilib{
	
class GridLayout : public GraphicContainer{
private:
	unsigned int _curri;
	unsigned int _currj;

	//height in pixel
	const byte _nbLine;
	const unsigned int _heightLine;

	const byte _nbCol;
	const unsigned int _widthCol;

public:
	GridLayout(byte nbCol, byte nbLine, unsigned int widthCol, unsigned int heightLine, unsigned int x, unsigned int y):
		GraphicContainer(), 
		_curri(0), _currj(0), 
		_nbLine(nbLine), _heightLine(heightLine), 
		_nbCol(nbCol), _widthCol(widthCol){
		setLeft(x);
		setTop(y);
	}
	GridLayout(byte nbCol, byte nbLine, AbstractGraphic *firstElmt, unsigned int x, unsigned int y):
		GraphicContainer(), 
		_curri(0), _currj(0),
		_nbLine(nbLine), _heightLine(firstElmt->getHeight()),
		_nbCol(nbCol), _widthCol(firstElmt->getWidth()){
		setLeft(x);
		setTop(y);

		addGraphic(firstElmt);
	}

	virtual void addGraphic(AbstractGraphic *graphic);

	void addGraphic(AbstractGraphic *graphic, bool centered);

	virtual void removeAll(){
		_curri = 0;
		_currj = 0;
		GraphicContainer::removeAll();
	}

	unsigned int getWidth() const{
		return (unsigned int)_nbCol * (unsigned int)_widthCol;
	}
	unsigned int getHeight() const{
		return (unsigned int)_nbLine * (unsigned int)_heightLine;
	}
};

template<class G> class GenGridLayout : public GridLayout {
public :
	GenGridLayout(byte nbCol, byte nbLine, unsigned int widthCol, unsigned int heightLine, unsigned int x, unsigned int y):
		GridLayout(nbCol, nbLine, widthCol, heightLine, x, y){}
	
	GenGridLayout(byte nbCol, byte nbLine, AbstractGraphic *firstElmt, unsigned int x, unsigned int y):
		GridLayout(nbCol, nbLine, firstElmt, x, y){}

	virtual void addGraphic(G* graphic){
		GridLayout::addGraphic(graphic);
	}

	virtual G* changeSelection(){
		return static_cast<G*>(GridLayout::changeSelection());
	}

	virtual G* getSelection(){
		return static_cast<G*>(GridLayout::getSelection());
	}
};

}

#endif
