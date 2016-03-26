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

#ifndef GLCDWFORUTFT_H_
#define GLCDWFORUTFT_H_

#include "Color.h"
#include "GLCDWrapper.h"
#include <UTFT.h>
#include <Arduino.h>

namespace uilib{
class GLCDWForUTFT : public GLCDWrapper{
public :

	GLCDWForUTFT(UTFT* screen);
	virtual ~GLCDWForUTFT();

private:
	//Variable statiques permettant de connaitre rapidement quelques tailles
	static const unsigned int W_SCREEN = 320;
	static const unsigned int H_SCREEN = 240;

	static const unsigned int W_SF = 8;
	static const unsigned int H_SF = 12;

	static const unsigned int W_BF = 16;
	static const unsigned int H_BF = 16;

	//Instance de classe UTFT encapsulé.
	UTFT* _utft;
	UTFT* getUTFT(){
		return _utft;
	}

	//Destructeur, constructeur par défaut, par copie et affectation privée pour les besoins du Singleton

	GLCDWForUTFT& operator= (const GLCDWForUTFT&){return *this;}


public :

	unsigned int get_W_SCREEN() const{
		return W_SCREEN;
	}
	unsigned int get_H_SCREEN() const{
		return H_SCREEN;
	}
	unsigned int get_W_SF() const{
		return W_SF;
	}
	unsigned int get_H_SF() const{
		return H_SF;
	}
	unsigned int get_W_BF() const{
		return W_BF;
	}
	unsigned int get_H_BF() const{
		return H_BF;
	}

	bool allowLocalRefresh() const{
		return true;
	}
	void 	startRendering(){}
	bool	keepRendering(){return false;}


	//Les fonctions suivantes concernent les fonctions utilisées dans le projet.
	void	clrScr(){
		getUTFT()->clrScr();
	}

	void	drawLine(int x1, int y1, int x2, int y2){
		getUTFT()->drawLine(x1, y1, x2, y2);
	}

	void	drawRect(int x1, int y1, int x2, int y2){
		getUTFT()->drawRect(x1, y1, x2, y2);
	}

	void	drawRoundRect(int x1, int y1, int x2, int y2){
		getUTFT()->drawRoundRect(x1, y1, x2, y2);
	}

	void	fillRect(int x1, int y1, int x2, int y2){
		getUTFT()->fillRect(x1, y1, x2, y2);
	}

	void	fillRoundRect(int x1, int y1, int x2, int y2){
		getUTFT()->fillRoundRect(x1, y1, x2, y2);
	}

	void	drawCircle(int x, int y, int radius){
		getUTFT()->drawCircle(x, y, radius);
	}

	void	fillCircle(int x, int y, int radius){
		getUTFT()->fillCircle(x, y, radius);
	}

	void	setColor(byte color){
		const Color& mycolor = ColorManager::Instance().getColor(color);
		getUTFT()->setColor(mycolor._r, mycolor._g, mycolor._b);
	}

	void	setBackColor(byte idColorBack){
		const Color& colorBack = ColorManager::Instance().getColor(idColorBack);
		getUTFT()->setBackColor(colorBack._r, colorBack._g, colorBack._b);
	}

	void	print(const char *st, int x, int y, int deg=0){
		getUTFT()->print(st, x, y, deg);
	}

	void	print(String st, int x, int y, int deg=0){
		getUTFT()->print(st, x, y, deg);
	}

	void	printNumI(long num, int x, int y, int length=0, char filler=' '){
		getUTFT()->printNumI(num, x, y, length, filler);
	}

	void	printNumF(double num, byte dec, int x, int y, char divider='.', int length=0, char filler=' '){
		getUTFT()->printNumF(num, dec, x, y, divider, length, filler);
	}

	void setFont(FontType font);

	void	drawBitmap(int x, int y, int sx, int sy, bitmapdatatype data, int scale=1){
		getUTFT()->drawBitmap(x, y, sx, sy, data, scale);
	}

	void	drawBitmap(int x, int y, int sx, int sy, bitmapdatatype data, int deg, int rox, int roy){
		getUTFT()->drawBitmap(x, y, sx, sy, data, deg, rox, roy);
	}

	void	drawBitmap(int x, int y, int sx, int sy, byte *data){
		getUTFT()->drawBitmap(x, y, sx, sy, data);
	}

	void drawPixel(int x, int y){
		#ifdef DEBUG
		Serial.println(F("drawPixel-->"));
		#endif

		getUTFT()->drawPixel(x, y);

		#ifdef DEBUG
		Serial.println(F("<--drawPixel"));
		#endif
	}

};
}


#endif /* GLCDWFORUTFT_H_ */
