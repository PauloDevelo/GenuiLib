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

#ifndef GRAPH_H_
#define GRAPH_H_

#include "AbstractGraphic.h"
#include "HistoData.h"
#include "IHistoDataListener.h"

//#define GRAPH_H_DEBUG 1

namespace uilib{

/**
 * TODO
 * Grphic object Graph has to be tested on screen supporting local refreshing. The object will have to be modified ...
 */


class Graph : public AbstractGraphic, public IHistoDataListener{
private:
	const unsigned int _width;
	const unsigned int _height;

	const byte _colorLevel;
	const byte _nbLevel;

	const HistoData<unsigned char>& _data;

	//Permet de définir l'échelle du graph de préférence
	const long _prefMin;
	const long _prefMax;

	const char* _unit;

	byte _exp;
	byte _scale;

	bool _autoResize;

protected:
	void drawStatic();
	void draw();

	void drawHDotLine(unsigned char j){
		#ifdef GRAPH_H_DEBUG
		Serial.print(F("drawHDotLine-->"));Serial.println(j);
		#endif

		for(unsigned int i = getLeft(); i < getWidth() + getLeft(); i++){
			if(i%4 == 0){
				getGLCD()->drawPixel(i, j);
			}
		}
		#ifdef GRAPH_H_DEBUG
		Serial.println(F("<--drawHDotLine"));
		#endif
	}

	void displayLevelValue(long value, byte x, byte y){
		#ifdef GRAPH_H_DEBUG
		Serial.print(F("displayLevelValue-->"));
		Serial.print(value);Serial.print(F(", "));
		Serial.print(x);Serial.print(F(", "));
		Serial.println(y);
		#endif

		long pow = 1;
		for(int i = 0; i < _exp; i++){
			pow *= 10;
		}

		value = (value + pow / 2) / pow;

		String levelStr(value);
		levelStr.concat(_unit);
		getGLCD()->print(levelStr, x, y);

		#ifdef GRAPH_H_DEBUG
		Serial.println(F("<--displayLevelValue"));
		#endif
	}

public:
	/**
	 * Constructeur d'un graph.
	 * @param data : Tableau à 2 dimensions d'octet contenant la donnéee à afficher dans le graph. data[nbScale][size]
	 * @parma nbScale : 1ère dimension du tableau de donnée. C'est le nombre d'échelle.
	 * @param size : Data table's Second dimension. It's the number of data for one scale.
	 * @param prefMin : Prefered minimum to display.
	 * @param prefMax : Prefered max to display.
	 * @param min : Minimum value of the data. A data with a value of 0 is equal to min.
	 * @param max : Maximum value of the data. A data with a value of 255 is equal to max.
	 * @param unit : Unit of the data to display on the left (Levels)
	 * @param x : X pos (Left)
	 * @param y : Y pos (Top)
	 * @param width : Width of the graph
	 * @param height : Height of the graph
	 * @param colorBck : Color of the background
	 * @param colorFore : Color of the Foreground
	 * @param colorLevel : Color of the level
	 * @param nbLevel : Number of level to display.
	 */
	Graph(const HistoData<unsigned char>& data,
			long prefMin, long prefMax,
			const char* unit, byte exp,
			unsigned int x, unsigned int y, unsigned int width, unsigned int height, byte nbLevel = 0, bool autoResize = true,
			byte colorBkg = ColorManager::DEFAULTBACKCOLOR, byte colorFore = ColorManager::DEFAULTFORECOLOR, byte colorLevel = ColorManager::DEFAULTENABLECOLOR):
		AbstractGraphic(false, colorBkg, colorFore), _width(width), _height(height), _colorLevel(colorLevel), _nbLevel(nbLevel),
		 _data(data), _prefMin(prefMin), _prefMax(prefMax), _unit(unit), _exp(exp), _scale(0), _autoResize(autoResize){

		setLeft(x);
		setTop(y);

		data.addListener(this);

	}

	void onHistoDataModified(){
		refresh();
	}

	unsigned int getHeight()const{
		return _height;
	}

	unsigned int getWidth()const{
		return _width;
	}

	const unsigned char& getScale(){
		return _scale;
	}

	void setScale(byte scale){
		_scale = scale;
		refresh();
	}

	void changeScale(){
		_scale++;
		if(_scale >= _data.getNbScale()){
			_scale = 0;
		}
		refresh();
	}
};

}



#endif /* GRAPH_H_ */
