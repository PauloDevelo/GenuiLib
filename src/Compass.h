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

#ifndef compass_h
#define compass_h

#include "MyMath.h"
#include "Integer.h"
#include "AbstractGraphic.h"
#include "Arduino.h"

namespace uilib{
class Compass : public AbstractGraphic{
private:
	class pixel{
	private:
		int _x;
		int _y;

	public:
		static const int ND = -32768;
		pixel():_x(ND),_y(ND){}
		pixel(int x, int y):_x(x), _y(y){}
		pixel(const pixel &ref):_x(ref._x), _y(ref._y){}

		const pixel& operator= (const pixel &px){
			_x = px._x;
			_y = px._y;
			return *this;
		}

		operator String() const{
			return String(F("(")) + String(getX()) + String(F(", ")) + String(getY()) + String(F(")"));
		}

		int getX()const{return _x;}
		int getY()const{return _y;}
		void setX(int x){_x = x;}
		void setY(int y){_y = y;}

		void fastrotate(int angleDeg, const pixel &center, const pixel& pt){
			using namespace fastmath;
			
			_x = (int)(icos(angleDeg) * (float)(pt.getX() - center.getX()) - isin(angleDeg)*(float)(center.getY() - pt.getY()) + (float)center.getX() + 0.5);
			_y = (int)(isin(angleDeg)*(float)(center.getX() - pt.getX()) + icos(angleDeg)*(float)(pt.getY() - center.getY()) + (float)center.getY() + 0.5);
		}
	};

	pixel Next;
	pixel Nint;
	pixel Ntext;

	pixel Sext;
	pixel Sint;
	pixel Stext;

	pixel Eext;
	pixel Eint;
	pixel Etext;

	pixel Wext;
	pixel Wint;
	pixel Wtext;

	pixel pt1;
	pixel pt2;
	pixel pt3;

	const pixel O;

	GLCDWrapper::FontType _cardTypeFont;
	unsigned char _dimCard;
	unsigned char _dimTriangleDest;
	unsigned char _dimDir;

	void drawDestTriangle();
	void drawCompass();

protected:
	const unsigned int _R;

	Wrapper::Integer<int>& _value;
	Wrapper::Integer<int>& _destValue;



	void drawStatic();
	void draw();

public:
	const static int NODEST = 700;

	Compass(Wrapper::Integer<int>& brg, Wrapper::Integer<int>& brgDest, unsigned int center_x, unsigned int center_y, unsigned int R,
			byte colorBkg = ColorManager::DEFAULTBACKCOLOR, byte colorFore = ColorManager::DEFAULTFORECOLOR):
		AbstractGraphic(false, colorBkg, colorFore), O((int)center_x, (int)center_y),
		_cardTypeFont(GLCDWrapper::TypeBigFont), _dimCard(20),  _dimTriangleDest(15),
		_dimDir(10), _R(R), _value(brg), _destValue(brgDest)
		{

		setLeft(center_x - R);
		setTop(center_y - R - 10);
	}

	bool hasToBeRefreshed()const{
		if(AbstractGraphic::hasToBeRefreshed()){
			return true;
		}
		else{
			return _value.hasBeenModified() || _destValue.hasBeenModified();
		}
	}

	void setDimensionCardinal(unsigned char newDimCard){
		_dimCard = newDimCard;
	}
	void setFontType(GLCDWrapper::FontType cardTypeFont){
		_cardTypeFont = cardTypeFont;
	}

	void setDimDestTriangle(unsigned char dim){
		_dimTriangleDest = dim;
	}

	void setDimDir(unsigned char dimDir){
		_dimDir = dimDir;
	}
	unsigned int getHeight() const{return 2 * _R + 10;}
	unsigned int getWidth() const{return 2 * _R;}
};
}

#endif
