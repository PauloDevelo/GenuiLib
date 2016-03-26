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

#include "Graph.h"
#include "MyMath.h"

void uilib::Graph::drawStatic(){
	#ifdef GRAPH_H_DEBUG
	Serial.println(F("drawStatic-->"));
	#endif

	if(_nbLevel != 0){
		getGLCD()->setColor(_colorLevel);
		getGLCD()->setFont(GLCDWrapper::TypeSmallFont);

		unsigned int spaceBetweenLevel = getHeight()/_nbLevel;

		long max = _prefMax;
		long min = _prefMin;
		if(_autoResize){
			if(_data.get_max() > max)max = _data.get_max();
			if(_data.get_min() < min)min = _data.get_min();
		}
		#ifdef GRAPH_H_DEBUG
		Serial.print("Min = ");Serial.println(min);
		Serial.print("Max = ");Serial.println(max);
		#endif

		for(int i = 0; i < _nbLevel; i++){
			int ii = (spaceBetweenLevel + 1)/2 + i * spaceBetweenLevel;
			int y = getTop() + ii;

			long value = fastmath::roundedmap(ii, 0, getHeight() - 1, max, min);
			displayLevelValue(value, 0, y - getGLCD()->get_H_SF() - 1);

			drawHDotLine(y);
		}

	}

	#ifdef GRAPH_H_DEBUG
	Serial.println(F("<--drawStatic"));
	#endif
}

void uilib::Graph::draw(){
	#ifdef GRAPH_H_DEBUG
	Serial.println(F("draw-->"));
	#endif

	getGLCD()->setColor(_colorFore);

	long max = _prefMax;
	long min = _prefMin;

	if(_autoResize){
		if(_data.get_max() > max)max = _data.get_max();
		if(_data.get_min() < min)min = _data.get_min();
	}

	long realValue;
	for(int i = getWidth() - 1; i >= 0 ; i--){

		unsigned int datai = fastmath::roundedmap(i, 0, getWidth() - 1, _data.getSize() - 1, 0);
		if(_data.getValue(datai, _scale, realValue)){
			unsigned int j = fastmath::roundedmap(realValue, min, max, getHeight() - 1, 0);
			getGLCD()->drawPixel(getLeft() + i, getTop() + j);

			#ifdef GRAPH_H_DEBUG
			Serial.print(F("data i"));Serial.println(datai);
			Serial.print(F("Real value "));Serial.println(realValue);
			Serial.print(F("pixel i"));Serial.println(i);
			Serial.print(F("pixel j"));Serial.println(j);
			#endif
		}
		else{
			#ifdef GRAPH_H_DEBUG
			Serial.println(F("<--draw"));
			#endif
			return;
		}
	}

	#ifdef GRAPH_H_DEBUG
	Serial.println(F("<--draw"));
	#endif
}



