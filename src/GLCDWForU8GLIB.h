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

#ifndef GLCDWFORU8GLIB_H_
#define GLCDWFORU8GLIB_H_

#include "Color.h"
#include "GLCDWrapper.h"
#include <U8glib.h>
#include <Arduino.h>

//#define DEBUG 1

namespace uilib{
class GLCDWForU8GLIB : public GLCDWrapper{
public :

	GLCDWForU8GLIB(U8GLIB* screen);
	virtual ~GLCDWForU8GLIB();

private:

	byte bckColor;
	FontType _fontType;
	//Instance de classe UTFT encapsulÃ©.
	U8GLIB* _u8glib;
	U8GLIB* getU8GLIB(){
		return _u8glib;
	}

	//Destructeur, constructeur par dÃ©faut, par copie et affectation privÃ©e pour les besoins du Singleton

	GLCDWForU8GLIB& operator= (const GLCDWForU8GLIB&){return *this;}


public :

	//Variable statiques permettant de connaitre rapidement quelques tailles


	static const unsigned int W_SF = 4;
	static const unsigned int H_SF = 6;

	static const unsigned int W_BF = 6;
	static const unsigned int H_BF = 10;

	unsigned int get_W_SCREEN() const{
		return _u8glib->getWidth();
	}
	unsigned int get_H_SCREEN() const{
		return _u8glib->getHeight();
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
		return false;
	}

	void 	startRendering(){getU8GLIB()->firstPage();}
	bool	keepRendering(){return getU8GLIB()->nextPage();}

	//Les fonctions suivantes concernent les fonctions utilisÃ©es dans le projet.
	void	clrScr(){
		#ifdef DEBUG
		Serial.println(F("clrScr-->"));
		#endif

		getU8GLIB()->setColorIndex(0);

		getU8GLIB()->drawBox( 0, 0, getU8GLIB()->getWidth(), getU8GLIB()->getHeight() );

		#ifdef DEBUG
		Serial.println(F("<--clrScr"));
		#endif
	}

	void	drawLine(int x1, int y1, int x2, int y2){
		#ifdef DEBUG
		Serial.println(F("drawLine-->"));
		Serial.println(x1);Serial.println(y1);Serial.println(x2);Serial.println(y2);
		#endif

		getU8GLIB()->drawLine(x1, y1, x2, y2);

		#ifdef DEBUG
		Serial.println(F("<--drawLine"));
		#endif
	}

	void	drawRect(int x1, int y1, int x2, int y2){
		#ifdef DEBUG
		Serial.println(F("drawRect-->"));
		#endif

		getU8GLIB()->drawFrame(x1, y1, x2 - x1 + 1, y2 - y1 + 1);

		#ifdef DEBUG
		Serial.println(F("<--drawRect"));
		#endif
	}

	void	drawRoundRect(int x1, int y1, int x2, int y2){
		#ifdef DEBUG
		Serial.println(F("drawRoundRect-->"));
		#endif

		getU8GLIB()->drawRFrame(x1, y1, x2 - x1 + 1, y2 - y1 + 1, 2);

		#ifdef DEBUG
		Serial.println(F("<--drawRoundRect"));
		#endif
	}

	void	fillRect(int x1, int y1, int x2, int y2){
		#ifdef DEBUG
		Serial.println(F("fillRect-->"));
		#endif

		getU8GLIB()->drawBox(x1, y1, x2 - x1 + 1, y2 - y1 + 1);

		#ifdef DEBUG
		Serial.println(F("<--fillRect"));
		#endif
	}

	void	fillRoundRect(int x1, int y1, int x2, int y2){
		#ifdef DEBUG
		Serial.println(F("fillRoundRect-->"));
		#endif

		getU8GLIB()->drawRBox(x1, y1, x2 - x1 + 1, y2 - y1 + 1, 2);

		#ifdef DEBUG
		Serial.println(F("<--fillRoundRect"));
		#endif
	}

	void	drawCircle(int x, int y, int radius){
		#ifdef DEBUG
		Serial.println(F("drawCircle-->"));
		#endif

		getU8GLIB()->drawCircle(x, y, radius);

		#ifdef DEBUG
		Serial.println(F("<--drawCircle"));
		#endif
	}

	void	fillCircle(int x, int y, int radius){
		#ifdef DEBUG
		Serial.println(F("fillCircle-->"));
		#endif

		getU8GLIB()->drawDisc(x, y, radius);

		#ifdef DEBUG
		Serial.println(F("<--fillCircle"));
		#endif
	}

	void	setColor(byte color){
		#ifdef DEBUG
		Serial.print(F("setColor-->"));
		Serial.println(color);
		#endif

		if(color == ColorManager::DEFAULTFORECOLOR){
			getU8GLIB()->setColorIndex(1);
		}
		else if(color == ColorManager::DEFAULTBACKCOLOR || color == ColorManager::DEFAULTENABLECOLOR) {
			getU8GLIB()->setColorIndex(0);
		}
		else{
			getU8GLIB()->setColorIndex(1);
		}

		#ifdef DEBUG
		Serial.println(F("<--setColor"));
		#endif
	}

	void	setBackColor(byte idColorBack){
		#ifdef DEBUG
		Serial.print(F("setBackColor-->"));
		Serial.println(idColorBack);
		#endif

		bckColor = (idColorBack == ColorManager::DEFAULTBACKCOLOR?0:1);

		#ifdef DEBUG
		Serial.println(F("<--setBackColor"));
		#endif
	}

	void	print(const char *st, int x, int y, int deg=0){
		#ifdef DEBUG
		Serial.print(F("print-->"));
		Serial.print(st);Serial.print(", ");
		Serial.print(x);Serial.print(", ");
		Serial.println(y);

		#endif

		if(deg == 0){


			int wstr = getU8GLIB()->getStrWidth(st);
			int hstr = (_fontType == TypeSmallFont?get_H_SF():get_H_BF());
			getU8GLIB()->setColorIndex(bckColor);
			fillRect(x, y, x + wstr - 1, y + hstr - 1);

			getU8GLIB()->setColorIndex(bckColor == 0?1:0);
			getU8GLIB()->drawStr(x, y, st);
		}

		#ifdef DEBUG
		Serial.println(F("<--print"));
		#endif
	}

	void	print(String st, int x, int y, int deg=0){
		#ifdef DEBUG
		Serial.println(F("print-->"));
		Serial.print(st);Serial.print(", ");
		Serial.print(x);Serial.print(", ");
		Serial.println(y);
		#endif

		print(st.c_str(), x, y, deg);

		#ifdef DEBUG
		Serial.println(F("<--print"));
		#endif
	}

	void	printNumI(long num, int x, int y, int length=0, char filler=' '){
		#ifdef DEBUG
		Serial.println(F("printNumI-->"));
		#endif

		String strNum = String(num);
		while((unsigned int)length > strNum.length())strNum.concat(filler);

		print(strNum, x, y, 0);

		#ifdef DEBUG
		Serial.println(F("<--printNumI"));
		#endif
	}

	void	printNumF(double num, byte dec, int x, int y, char divider='.', int length=0, char filler=' '){
		#ifdef DEBUG
		Serial.println(F("printNumF-->"));
		#endif

		String strNum = String(num, dec);
		while((unsigned int)length > strNum.length())strNum.concat(filler);

		print(strNum, x, y, 0);

		#ifdef DEBUG
		Serial.println(F("<--printNumF"));
		#endif
	}

	void setFont(FontType font);

	void	drawBitmap(int x, int y, int sx, int sy, bitmapdatatype data, int scale=1){
		#ifdef DEBUG
		Serial.println(F("drawBitmap-->"));
		#endif

		if(scale == 1){
			int size = sx * sy;
			unsigned char* ucdata = new unsigned char[size];
			for(int i = 0; i < size; i++){
				ucdata[i] = (unsigned char)data[i];
			}

			getU8GLIB()->drawBitmap(x, y, sx, sy, ucdata);

			delete ucdata;
		}

		#ifdef DEBUG
		Serial.println(F("<--drawBitmap"));
		#endif
	}

	void	drawBitmap(int x, int y, int sx, int sy, bitmapdatatype data, int deg, int rox, int roy){
		Serial.println(F("Fonction drawBitmap non implémentée."));
	}

	void	drawBitmap(int x, int y, int sx, int sy, byte *data){
		#ifdef DEBUG
		Serial.println(F("drawBitmap-->"));
		#endif

		getU8GLIB()->drawBitmap(x, y, sx, sy, data);

		#ifdef DEBUG
		Serial.println(F("<--drawBitmap"));
		#endif
	}

	void drawPixel(int x, int y){
		#ifdef DEBUG
		Serial.println(F("drawPixel-->"));
		#endif

		getU8GLIB()->drawPixel(x, y);

		#ifdef DEBUG
		Serial.println(F("<--drawPixel"));
		#endif
	}

};
}

#endif /* GLCDWFORST7920_H_ */
