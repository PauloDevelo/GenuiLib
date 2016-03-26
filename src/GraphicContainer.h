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

#ifndef graphiccontainer_h
#define graphiccontainer_h

#include "GenericContainer.h"
#include "GLCDWrapper.h"
#include "Color.h"
#include "AbstractGraphic.h"

namespace uilib{
class GraphicContainer : public AbstractGraphic{
private:
	Generic_Container::Fifo<AbstractGraphic> _gList;
	Generic_Container::Fifo<AbstractGraphic>::iterator _selection;

	static const unsigned char MASK_MULTIPLESELECTION 	= 0b00010000;

protected:
	void draw(){}

	bool allowMultipleSelection() const{
		return (_state & MASK_MULTIPLESELECTION);
	}

public:
	GraphicContainer(bool allowMultipleSelect = false):
		AbstractGraphic(false){
			if(allowMultipleSelect){
				_state |= MASK_MULTIPLESELECTION;
			}
			else{
				_state &= (~MASK_MULTIPLESELECTION);
			}
	}

	~GraphicContainer(){
	}
	
	bool hasToBeRefreshed()const;

	void redraw(long milliAvailable = -1);
	virtual void addGraphic(AbstractGraphic* graphic);

	virtual AbstractGraphic* remove(AbstractGraphic* graphic);
	virtual void removeAll();
	
	void setVisible(bool isVisible);
	void setEnable(bool isEnable);

	unsigned int getHeight() const {
		return getGLCD()->get_H_SCREEN();
	}

	unsigned int getWidth()const {
		return getGLCD()->get_W_SCREEN();
	}

	Generic_Container::Fifo<AbstractGraphic>::iterator begin()const{
		return _gList.begin();
	}
	Generic_Container::Fifo<AbstractGraphic>::iterator end()const{
		return _gList.end();
	}

	virtual AbstractGraphic* getSelection(){
		return *_selection;
	}

	virtual AbstractGraphic* changeSelection();
};
}

#endif
