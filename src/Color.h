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

#ifndef color_h
#define color_h

#include "Arduino.h"

namespace uilib{
//Classe couleur
class Color{
public:
	const byte _r;
	const byte _g;
	const byte _b;

	Color(byte r, byte g, byte b):_r(r), _g(g), _b(b){}
};

class ColorManager{
	static ColorManager m_instance;

	//Couleurs gérées
	Color colors[7] = {{0, 0, 0},{255, 0, 0},{0, 0, 255},{0, 255, 0},{255, 255, 255}, {127, 127, 127}, {0, 255, 255}};

	//Affectation, destructeur, constructeur par defaut et par copie privée pour le singleton.
	ColorManager(){}
	ColorManager (const ColorManager&){}
	ColorManager& operator= (const ColorManager&){}
	~ColorManager(){
	}

public:
	static const byte BLACK = 0;
	static const byte RED = 1;
	static const byte BLUE = 2;
	static const byte GREEN = 3;
	static const byte WHITE = 4;
	static const byte GREY = 5;
	static const byte YELLOW = 6;

	static const byte APPBCKCOLOR = 0;
	static const byte DEFAULTFORECOLOR = 3;
	static const byte DEFAULTBACKCOLOR = 0;
	static const byte DEFAULTENABLECOLOR = 5;

	static ColorManager& Instance();

	const Color& getColor(byte index) const{
		return colors[index];
	}
};
}

#endif
