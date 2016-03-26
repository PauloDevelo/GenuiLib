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

#include "Compass.h"

namespace uilib{
void Compass::drawStatic(){
	getGLCD()->drawCircle(O.getX(), O.getY(), _R);
	getGLCD()->drawLine(O.getX(), O.getY() - _R, O.getX(), O.getY() - _R - _dimDir);
}

void Compass::draw(){
	if(_value.hasBeenModified() || _destValue.hasBeenModified() || !isVisible() || !getGLCD()->allowLocalRefresh()){
		drawDestTriangle();
	}
	if(_value.hasBeenModified() || !isVisible() || !getGLCD()->allowLocalRefresh()){
		drawCompass();
	}
}

void Compass::drawCompass(){
	int brg = _value.getValue();
	boolean visible = isVisible();
	getGLCD()->setFont(_cardTypeFont);

	byte colorFore =  getForegroundColor();
	byte colorBck =  getBackgroundColor();
	//
	//Affichage du Nord
	//
	//On efface
	if((Next.getX() != pixel::ND || !visible) && getGLCD()->allowLocalRefresh()){
		getGLCD()->setColor(colorBck);
		getGLCD()->drawLine(Next.getX(), Next.getY(), Nint.getX(), Nint.getY());
	}
	
	pixel temp = pixel(O.getX(), O.getY() - _R + 1);
	if(visible){
		//Trace du Nord
		Next.fastrotate(brg, O, temp);
		temp.setY(temp.getY() + _dimCard);
		Nint.fastrotate(brg, O, temp);

		//Puis on retrace
		getGLCD()->setColor(ColorManager::RED);
		getGLCD()->drawLine(Next.getX(), Next.getY(), Nint.getX(), Nint.getY());
	}

	//
	//Affichage du Sud
	//
	//On efface
	if((Sext.getX() != pixel::ND || !visible) && getGLCD()->allowLocalRefresh()){
		getGLCD()->setColor(colorBck);
		getGLCD()->drawLine(Sext.getX(), Sext.getY(), Sint.getX(), Sint.getY());
	}

	if(visible){
		Sext.setX(2 * O.getX() - Next.getX());
		Sext.setY(2 * O.getY() - Next.getY());

		Sint.setX(2 * O.getX() - Nint.getX());
		Sint.setY(2 * O.getY() - Nint.getY());
		//Puis on retrace
		getGLCD()->setColor(colorFore);
		getGLCD()->drawLine(Sext.getX(), Sext.getY(), Sint.getX(), Sint.getY());
	}

	//On efface le texte du N et du S
	if((Ntext.getX() != pixel::ND || !visible) && getGLCD()->allowLocalRefresh()){
		getGLCD()->setColor(colorBck);
		getGLCD()->print(F("N"), Ntext.getX(), Ntext.getY());
	    getGLCD()->print(F("S"), Stext.getX(), Stext.getY());
		getGLCD()->setColor(colorFore);
	}

	if(visible){
		//Puis on retrace
		temp.setY(temp.getY() + 2 + getGLCD()->get_H_BF()/2);
		Ntext.fastrotate(brg, O, temp);
		temp.setX(Ntext.getX());
		temp.setY(Ntext.getY());
		
		Stext.setX(2 * O.getX() - Ntext.getX());
		Stext.setY(2 * O.getY() - Ntext.getY());
		Ntext.setX(Ntext.getX() - getGLCD()->get_W_BF()/2);
		Ntext.setY(Ntext.getY() - getGLCD()->get_H_BF()/2);
		Stext.setX(Stext.getX() - getGLCD()->get_W_BF()/2);
		Stext.setY(Stext.getY() - getGLCD()->get_H_BF()/2);
		getGLCD()->print(F("N"), Ntext.getX(), Ntext.getY());
	    getGLCD()->print(F("S"), Stext.getX(), Stext.getY());
	}

    //
    //Affichage de l'W
    //
    //On efface
	if((Wext.getX() != pixel::ND || !visible) && getGLCD()->allowLocalRefresh()){
		getGLCD()->setColor(colorBck);
		getGLCD()->drawLine(Wext.getX(), Wext.getY(), Wint.getX(), Wint.getY());
		getGLCD()->setColor(colorFore);
	}

	if(visible){
		Wext.setX(O.getX() + Next.getY() - O.getY());
		Wext.setY(O.getY() + O.getX() - Next.getX());

		Wint.setX(O.getX() + Nint.getY() - O.getY());
		Wint.setY(O.getY() + O.getX() - Nint.getX());

		//Puis on retrace
		getGLCD()->drawLine(Wext.getX(), Wext.getY(), Wint.getX(), Wint.getY());
	}

	//
	//Affichage de l'E
	//
	//On efface
	if((Eext.getX() != pixel::ND || !visible) && getGLCD()->allowLocalRefresh()){
		getGLCD()->setColor(colorBck);
		getGLCD()->drawLine(Eext.getX(), Eext.getY(), Eint.getX(), Eint.getY());
		getGLCD()->setColor(colorFore);
	}

	if(visible){
		Eext.setX(2 * O.getX() - Wext.getX());
		Eext.setY(2 * O.getY() - Wext.getY());

		Eint.setX(2 * O.getX() - Wint.getX());
		Eint.setY(2 * O.getY() - Wint.getY());

		//Puis on retrace
		getGLCD()->drawLine(Eext.getX(), Eext.getY(), Eint.getX(), Eint.getY());
	}

	//On efface le texte de l'E et de l'O
	if((Etext.getX() != pixel::ND || !visible) && getGLCD()->allowLocalRefresh()){
		getGLCD()->setColor(colorBck);
		getGLCD()->print(F("E"), Etext.getX(), Etext.getY());
	    getGLCD()->print(F("W"), Wtext.getX(), Wtext.getY());
		getGLCD()->setColor(colorFore);
	}

	if(visible){
		//Puis on retrace
		Wtext.setX(O.getX() + temp.getY() - O.getY());
		Wtext.setY(O.getY() + O.getX() - temp.getX());
		
		Etext.setX(2 * O.getX() - Wtext.getX());
		Etext.setY(2 * O.getY() - Wtext.getY());
		Etext.setX(Etext.getX() - getGLCD()->get_W_BF()/2);
		Etext.setY(Etext.getY() - getGLCD()->get_H_BF()/2);
		Wtext.setX(Wtext.getX() - getGLCD()->get_W_BF()/2);
		Wtext.setY(Wtext.getY() - getGLCD()->get_H_BF()/2);
		getGLCD()->print(F("E"), Etext.getX(), Etext.getY());
	    getGLCD()->print(F("W"), Wtext.getX(), Wtext.getY());
	}
}

void Compass::drawDestTriangle(){
	Serial.println("drawDestTriangle");

	int brgDest = _destValue.getValue();
	int brg = _value.getValue();
	byte backColor = getBackgroundColor();

	//On efface deja le précédent triangle de destination
	if((brgDest != NODEST || !isVisible())&& pt1.getX() != pixel::ND && getGLCD()->allowLocalRefresh()){
		getGLCD()->setColor(backColor);
		getGLCD()->drawLine(pt1.getX(), pt1.getY(), pt2.getX(), pt2.getY());
		getGLCD()->drawLine(pt2.getX(), pt2.getY(), pt3.getX(), pt3.getY());
		getGLCD()->drawLine(pt3.getX(), pt3.getY(), pt1.getX(), pt1.getY());
	}

	//Puis on le retrace si nécessaire.
    if(brgDest != NODEST && isVisible()){
    	getGLCD()->setColor(ColorManager::RED);

    	pixel depart1(O.getX(), O.getY() - _R + 1);
    	pixel depart2(O.getX() - _dimTriangleDest/2, O.getY() - _R + 1 + _dimTriangleDest);
    	pixel depart3(O.getX() + _dimTriangleDest/2, O.getY() - _R + 1 + _dimTriangleDest);

    	pt1.fastrotate(brg - brgDest, O, depart1);
    	pt2.fastrotate(brg - brgDest, O, depart2);
    	pt3.fastrotate(brg - brgDest, O, depart3);

    	getGLCD()->drawLine(pt1.getX(), pt1.getY(), pt2.getX(), pt2.getY());
		getGLCD()->drawLine(pt2.getX(), pt2.getY(), pt3.getX(), pt3.getY());
		getGLCD()->drawLine(pt3.getX(), pt3.getY(), pt1.getX(), pt1.getY());
	}

	getGLCD()->setColor(getForegroundColor());
}
}
