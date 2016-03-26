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

#ifndef abstractgraphic_h
#define abstractgraphic_h

#include "GLCDWrapper.h"
#include "Color.h"

namespace uilib{
//Classe virtuelle pure
class AbstractGraphic{
private:
	static GLCDWrapper* myGLCD;

	static const unsigned char MASK_SELECT 			= 0b00000001;
	static const unsigned char MASK_VISIBLE 		= 0b00000010;
	static const unsigned char MASK_ENABLE 			= 0b00000100;
	static const unsigned char MASK_SELECTIONNABLE 	= 0b00001000;
	static const unsigned char MASK_REFRESH_STATIC	= 0b01000000;
	static const unsigned char MASK_REFRESH_DYNAMIC	= 0b10000000;

	unsigned int _x;
	unsigned int _y;
protected:
	GLCDWrapper* getGLCD() const{return myGLCD;}
	
	const byte _colorFore;
	const byte _colorBck;

	volatile unsigned char _state;

	void refreshStatic(){
		_state |= MASK_REFRESH_STATIC;
	}

	bool staticHasToBeRefreshed()const{
		return (_state & MASK_REFRESH_STATIC);
	}
	
	virtual void drawStatic(){};
	virtual void draw() = 0;
	
	byte getForegroundColor()const;
	byte getBackgroundColor()const;

public:
	//Cette fonction doit être appelé dans le setup afin d'initialiser le pointeur sur le Wrapper de UTFT.
	static void initAbstractGraphicClass(GLCDWrapper* screen);

	AbstractGraphic(bool isSelectionnable = false, byte colorBck = ColorManager::DEFAULTBACKCOLOR, byte colorFore = ColorManager::DEFAULTFORECOLOR):
		_x(0), _y(0), _colorFore(colorFore), _colorBck(colorBck), _state(0){
		_state = (_state | MASK_VISIBLE | MASK_ENABLE | MASK_REFRESH_DYNAMIC | MASK_REFRESH_STATIC);

		if(isSelectionnable){
			_state |= MASK_SELECTIONNABLE;
		}
	}

	virtual void redraw(long milliAvailable = -1);
	
	virtual bool hasToBeRefreshed()const{
		return (_state & MASK_REFRESH_DYNAMIC);
	}

	void refresh(){
		_state |= MASK_REFRESH_DYNAMIC;
	}

	bool isEnable() const{
		return (_state & MASK_ENABLE);
	}

	virtual void setEnable(bool enable){
		if(enable != isEnable()){
			if(enable){
				_state |= MASK_ENABLE;
			}
			else{
				_state &= (~MASK_ENABLE);
			}
			_state |= (MASK_REFRESH_DYNAMIC | MASK_REFRESH_STATIC);
		}
	}

	bool isSelectionnable() const{
		return (_state & MASK_SELECTIONNABLE);
	}

	bool isSelected() const{
		return (_state & MASK_SELECT);
	}

	virtual void select(bool selected){
		if(isSelectionnable()){
			if(selected != isSelected()){
				if(selected){
					_state |= MASK_SELECT;
				}
				else{
					_state &= (~MASK_SELECT);
				}
				_state |= (MASK_REFRESH_DYNAMIC | MASK_REFRESH_STATIC);
			}
		}
		else{
			Serial.println(F("AbstractGraphic::select Tentative de selection d'un élément graphique non sélectionnable"));
		}
	}

	bool isVisible() const{
		return (_state & MASK_VISIBLE);
	}

	virtual void setVisible(bool visible){
		if(visible != isVisible()){
			if(visible){
				_state |= MASK_VISIBLE;
			}
			else{
				_state &= (~MASK_VISIBLE);
			}
			_state |= (MASK_REFRESH_DYNAMIC | MASK_REFRESH_STATIC);
		}
	}

	unsigned int getLeft() const {return _x;}
	void setLeft(unsigned int x){_x = x;}

	unsigned int getTop()const {return _y;}
	void setTop(unsigned int y){_y = y;}

	void setXY(unsigned int x, unsigned int y){
		_y = y;
		_x = x;
	}

	virtual unsigned int getHeight() const = 0;
	virtual unsigned int getWidth() const = 0;

	virtual ~AbstractGraphic(){};
};
}

#endif
