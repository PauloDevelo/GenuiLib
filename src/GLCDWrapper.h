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

#ifndef glcdwrapper_h
#define glcdwrapper_h

#include "Color.h"
#include <UTFT.h>
#include <Arduino.h>

namespace uilib{
class GLCDWrapper{

	//Destructeur, constructeur par défaut, par copie et affectation privée pour les besoins du Singleton

	GLCDWrapper (const GLCDWrapper&){}
	GLCDWrapper& operator= (const GLCDWrapper&){}
public :

	enum FontType {
		TypeSmallFont,
		TypeBigFont
	}; //

	GLCDWrapper(){}
	virtual ~GLCDWrapper(){};

	virtual unsigned int get_W_SCREEN() const = 0;
	virtual unsigned int get_H_SCREEN() const = 0;
	virtual unsigned int get_W_SF() const = 0;
	virtual unsigned int get_H_SF() const = 0;
	virtual unsigned int get_W_BF() const = 0;
	virtual unsigned int get_H_BF() const = 0;

	virtual bool 	allowLocalRefresh() const = 0;
	virtual void 	startRendering() = 0;
	virtual bool	keepRendering() = 0;

	//Les fonctions suivantes concernent les fonctions utilisées dans le projet.
	virtual void	clrScr() = 0;

	virtual void	drawLine(int x1, int y1, int x2, int y2) = 0;

	virtual void	drawRect(int x1, int y1, int x2, int y2) = 0;

	virtual void	drawRoundRect(int x1, int y1, int x2, int y2) = 0;

	virtual void	fillRect(int x1, int y1, int x2, int y2) = 0;

	virtual void	fillRoundRect(int x1, int y1, int x2, int y2) = 0;

	virtual void	drawCircle(int x, int y, int radius) = 0;

	virtual void	fillCircle(int x, int y, int radius) = 0;

	virtual void	setColor(byte color) = 0;

	virtual void	setBackColor(byte idColorBack) = 0;

	virtual void	print(const char *st, int x, int y, int deg=0) = 0;

	virtual void	print(String st, int x, int y, int deg=0) = 0;

	virtual void	printNumI(long num, int x, int y, int length=0, char filler=' ') = 0;

	virtual void	printNumF(double num, byte dec, int x, int y, char divider='.', int length=0, char filler=' ') = 0;

	virtual void 	setFont(FontType font) = 0;
			
	virtual void	drawBitmap(int x, int y, int sx, int sy, bitmapdatatype data, int scale=1) = 0;

	virtual void	drawBitmap(int x, int y, int sx, int sy, bitmapdatatype data, int deg, int rox, int roy) = 0;

	virtual void	drawBitmap(int x, int y, int sx, int sy, byte *data) = 0;

	virtual void drawPixel(int x, int y) = 0;

};
}

#endif
