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
#include "Float.h"

Wrapper::Float::Float(const float* const value, unsigned char decimalPlaces, unsigned char nbCarMax, const char* unit):
_value(value), _unit(unit), valueDisplayed(-32768), _decPlaces(decimalPlaces), _nbCarMax(nbCarMax){
	unsigned char nbCarUnit = strlen(_unit);
	if(nbCarUnit > 3){
		Serial.println(F("Les unités doivent avoir une longueur inférieure à 3."));
	} 
	if(_decPlaces + 2 + nbCarUnit > _nbCarMax){
		Serial.println(F("Le nombre de caractère maximal pour l'affichage d'un flottant doit être supérieur(ou égale à la somme du nombre de décimals, du nombre de caractère de l'unité plus 2 (une partie entière et la virgule)."));
	}
	if(_nbCarMax < 3){
		Serial.println(F("Le nombre de caractère maximal doit au moins être égale à 3."));
	}

	if(_unit != 0){
		_nbCarMax -= strlen(_unit);
	}
}

Wrapper::Float::operator String()const{
	valueDisplayed = *_value;

	char nbCarDecAvailable = _nbCarMax;

	//On enlève le signe s'il y a lieu
	if(valueDisplayed < 0){
		nbCarDecAvailable--;
	}

	//On soustrait la partie entière
	long intPart = (long)valueDisplayed;
	while(intPart > 0){
		nbCarDecAvailable--;
		intPart /= 10;
	}

	//Si il y a assez de place pour afficher une partie décimale
	if(nbCarDecAvailable >= 2){
		//On soustrait la virgule
		nbCarDecAvailable--;

		//Si la place restante est supérieure au nombre de décimal voulu, on réduit
		if(nbCarDecAvailable > _decPlaces)
			nbCarDecAvailable = _decPlaces;
	}
	//Sinon, on n'en met pas tout simplement.
	else if (nbCarDecAvailable >= 0){
		nbCarDecAvailable = 0;
	}
	//Par contre, s'il n'y a même pas la place de mettre la partie entière (nbCarDecAvailable < 0)
	else{
		return String(F("OUT"));
	}

	String retour(valueDisplayed, nbCarDecAvailable);
	if(_unit != 0){
		retour += _unit;
	}

	return retour;
}
