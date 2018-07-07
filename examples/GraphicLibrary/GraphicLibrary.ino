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

#include "Editable.h"
#include "GenEditable.h"
#include "Gage.h"
#include "GraphicContainer.h"
#include "DynamicLabel.h"
#include "GridLayout.h"
#include "MenuItem.h"
#include "Label.h"
#include "GLCDWrapper.h"
#include "ScreenFactory.h"
#include "Utils.h"
#include "Integer.h"
#include "Float.h"
#include "Compass.h"
#include "Graph.h"
#include <Arduino.h>

using namespace uilib;

#define ledPin 4

//Pour le bouton poussoir
#define PIN_BUTTON1 22
//Pour le bouton poussoir
#define PIN_BUTTON2 23
//Pour le bouton poussoir
#define PIN_BUTTON3 24
//Pour le bouton poussoir
#define PIN_BUTTON4 25

int freeRam = Utils::FreeRam();

int currentFreeRam;
Wrapper::Integer<int> wrapperFreeRam(&currentFreeRam, "o");

int cpt = 0;
Wrapper::Integer<int> wrapperCpt(&cpt);
HistoData<unsigned char>* _histoCpt = 0;

float redrawTime;
Wrapper::Float wrapperRedrawTime(&redrawTime, 2, 6, "ms");

GLCDWrapper* myGLCD = 0;

GraphicContainer* screen= 0;
GenGridLayout<MenuItem<int, const __FlashStringHelper *> >* menu = 0;

int brg = 270;
Wrapper::Integer<int> brgWrapped(&brg, "°");
int brgDest = 280;
Wrapper::Integer<int> brgDestWrapped(&brgDest, "°");


void menuT(const uilib::Editable& menu){
	Serial.println("La valeur du menuT a changé.");
}

void menuP(const uilib::Editable& menu){
	Serial.println("La valeur du menuP a changé.");
}

void menuM(const uilib::Editable& menu){
	Serial.println("La valeur du menuM a changé.");
}

void menuON(const uilib::Editable& menu){
	Serial.println("La valeur du menuON a changé.");
}

int step = 0;
void initGraphics(){
	Serial.print(F("initGraphics step num"));Serial.println(step);

	screen = new GraphicContainer();

	if(step == 0){
		GridLayout* gridLayoutForLabel = new GridLayout(2, 3, myGLCD->get_W_SCREEN() / 2, myGLCD->get_H_SF(), 0, 0);
		screen->addGraphic(gridLayoutForLabel);

		uilib::Label<int&>* labelInt = new uilib::Label<int&>(freeRam);
		gridLayoutForLabel->addGraphic(labelInt);

		DynamicLabel<Wrapper::Integer<int> &> *labelCurrentFreeRam = new DynamicLabel<Wrapper::Integer<int> &>(wrapperFreeRam);
		labelCurrentFreeRam->setWidth(myGLCD->get_W_SCREEN()/2);
		labelCurrentFreeRam->setCentered(true);
		gridLayoutForLabel->addGraphic(labelCurrentFreeRam);

		uilib::Label<const __FlashStringHelper *>* label = new uilib::Label<const __FlashStringHelper *>(F("Counter :"));
		gridLayoutForLabel->addGraphic(label);

		DynamicLabel<Wrapper::Integer<int> &> *labelCpt = new DynamicLabel<Wrapper::Integer<int> &>(wrapperCpt);
		labelCpt->setWidth(myGLCD->get_W_SCREEN()/2);
		gridLayoutForLabel->addGraphic(labelCpt);

		label = new uilib::Label<const __FlashStringHelper *>(F("Redraw time"));
		gridLayoutForLabel->addGraphic(label);

		DynamicLabel<Wrapper::Float &> *redrawTimeLbl = new DynamicLabel<Wrapper::Float &>(wrapperRedrawTime);
		redrawTimeLbl->setWidth(myGLCD->get_W_SCREEN() / 2);
		gridLayoutForLabel->addGraphic(redrawTimeLbl);

		Gage* mgage = new Gage(wrapperCpt, true, 0, 100, myGLCD->get_W_SCREEN(), 10);
		mgage->setXY(0, 3 * myGLCD->get_H_SF() + 2);
		screen->addGraphic(mgage);

		menu = new GenGridLayout<MenuItem<int, const __FlashStringHelper *> >(4, 1, 32, myGLCD->get_H_SF() + 4, 0, 3 * myGLCD->get_H_SF() + 13);
		screen->addGraphic(menu);

		MenuItem<int, const __FlashStringHelper *>* myMenuItem = new MenuItem<int, const __FlashStringHelper *>(4, 4);
		myMenuItem->addValue(0, F("TITI"));
		myMenuItem->addValue(1, F("TUTU"));
		myMenuItem->addValue(2, F("TOTO"));
		myMenuItem->addValue(3, F("TATA"));
		myMenuItem->setEnable(false);
		myMenuItem->registerOnValueChange(menuT);
		menu->addGraphic(myMenuItem);

		myMenuItem = new MenuItem<int, const __FlashStringHelper *>(4, 4);
		myMenuItem->addValue(0, F("PIPI"));
		myMenuItem->addValue(1, F("PUPU"));
		myMenuItem->addValue(2, F("POPO"));
		myMenuItem->addValue(3, F("PAPA"));
		myMenuItem->registerOnValueChange(menuP);
		menu->addGraphic(myMenuItem);

		myMenuItem = new MenuItem<int, const __FlashStringHelper *>(4, 4);
		myMenuItem->addValue(0, F("MIMI"));
		myMenuItem->addValue(1, F("MOMO"));
		myMenuItem->addValue(2, F("MAMA"));
		myMenuItem->addValue(3, F("MEME"));
		myMenuItem->registerOnValueChange(menuM);
		menu->addGraphic(myMenuItem);

		myMenuItem = new MenuItem<int, const __FlashStringHelper *>(3, 4, ColorManager::BLACK, ColorManager::RED);
		myMenuItem->addValue(0, F(" ON "));
		myMenuItem->addValue(1, F("OFF "));
		myMenuItem->addValue(2, F(" NA "));
		myMenuItem->registerOnValueChange(menuON);
		menu->addGraphic(myMenuItem);
	}
	else if(step == 1){
		GridLayout* gridLayoutForLabel = new GridLayout(1, 3, myGLCD->get_W_SCREEN() / 2, myGLCD->get_H_SF(), 0, 0);
		screen->addGraphic(gridLayoutForLabel);

		uilib::Label<int&>* labelInt = new uilib::Label<int&>(freeRam);
		gridLayoutForLabel->addGraphic(labelInt);

		DynamicLabel<Wrapper::Integer<int> &> *labelCurrentFreeRam = new DynamicLabel<Wrapper::Integer<int> &>(wrapperFreeRam);
		labelCurrentFreeRam->setWidth(myGLCD->get_W_SCREEN()/2);
		gridLayoutForLabel->addGraphic(labelCurrentFreeRam);

		DynamicLabel<Wrapper::Float &> *redrawTimeLbl = new DynamicLabel<Wrapper::Float &>(wrapperRedrawTime);
		redrawTimeLbl->setWidth(myGLCD->get_W_SCREEN()/2);
		gridLayoutForLabel->addGraphic(redrawTimeLbl);

		Compass* compass = new Compass(brgWrapped, brgDestWrapped,
										64, 33,30);
		compass->setDimDestTriangle(5);
		compass->setDimensionCardinal(5);
		compass->setFontType(GLCDWrapper::TypeSmallFont);
		compass->setDimDir(2);

		screen->addGraphic(compass);
	}
	else if(step == 2){
		_histoCpt = new HistoData<unsigned char>(128, 1, 0, 100);

		GridLayout* gridLayoutForLabel = new GridLayout(3, 1, myGLCD->get_W_SCREEN() / 3, myGLCD->get_H_SF(), 0, 0);
		screen->addGraphic(gridLayoutForLabel);

		uilib::Label<int&>* labelInt = new uilib::Label<int&>(freeRam);
		gridLayoutForLabel->addGraphic(labelInt);

		DynamicLabel<Wrapper::Integer<int> &> *labelCurrentFreeRam = new DynamicLabel<Wrapper::Integer<int> &>(wrapperFreeRam);
		labelCurrentFreeRam->setWidth(myGLCD->get_W_SCREEN()/3);
		gridLayoutForLabel->addGraphic(labelCurrentFreeRam);

		DynamicLabel<Wrapper::Float &> *redrawTimeLbl = new DynamicLabel<Wrapper::Float &>(wrapperRedrawTime);
		redrawTimeLbl->setWidth(myGLCD->get_W_SCREEN()/3);
		gridLayoutForLabel->addGraphic(redrawTimeLbl);

		Graph* graph = new Graph(*_histoCpt,
				0, 100,
				"Na", 0,
				0, myGLCD->get_H_SF(), myGLCD->get_W_SCREEN(), myGLCD->get_H_SCREEN() - myGLCD->get_H_SF(), 3, false,
				ColorManager::DEFAULTBACKCOLOR, ColorManager::DEFAULTFORECOLOR, ColorManager::DEFAULTENABLECOLOR);

		screen->addGraphic(graph);
	}
}

void setup() {
	//Les ports série
  	Serial.begin(115200);

  	pinMode(ledPin, OUTPUT);
  	analogWrite(ledPin, 0);

  	pinMode(PIN_BUTTON1, INPUT_PULLUP);           // set pin to input with pullup
  	pinMode(PIN_BUTTON2, INPUT_PULLUP);           // set pin to input with pullup
  	pinMode(PIN_BUTTON3, INPUT_PULLUP);           // set pin to input with pullup
  	pinMode(PIN_BUTTON4, INPUT_PULLUP);

  	myGLCD = ScreenFactory::buildScreen(ScreenFactory::ST7920);
  	AbstractGraphic::initAbstractGraphicClass(myGLCD);

	initGraphics();

}

#define KEY_NONE 0


uint8_t uiKeyCode = KEY_NONE;
uint8_t last_key_code = KEY_NONE;

void uiStep(void) {
  if ( digitalRead(PIN_BUTTON1) == LOW )
	  uiKeyCode = PIN_BUTTON1;
  else if ( digitalRead(PIN_BUTTON2) == LOW )
	  uiKeyCode = PIN_BUTTON2;
  else if ( digitalRead(PIN_BUTTON3) == LOW )
	  uiKeyCode = PIN_BUTTON3;
  else if ( digitalRead(PIN_BUTTON4) == LOW )
	  uiKeyCode = PIN_BUTTON4;
  else
    uiKeyCode = KEY_NONE;


}

void updateMenu(void) {
  if ( uiKeyCode != KEY_NONE && last_key_code == uiKeyCode ) {
    return;
  }
  last_key_code = uiKeyCode;

  MenuItem<int, const __FlashStringHelper* >* selection = 0;
  switch ( uiKeyCode ) {
    case PIN_BUTTON1:
    	if(menu != 0)
    		menu->changeSelection();
    	break;
    case PIN_BUTTON2:
    	if(menu != 0){
    		selection = menu->getSelection();
    		if(selection != 0)
    			selection->increase();
    	}
      break;
    case PIN_BUTTON3:
    	if(menu != 0){
    		selection = menu->getSelection();
    		if(selection != 0)
    			selection->decrease();
    	}
       break;
    case PIN_BUTTON4:
    	delete screen;
    	screen = 0;
    	//Not necessary to delete menu because it has been deleted in the screen's destructor
    	menu = 0;

    	if(_histoCpt != 0){
    		delete _histoCpt;
    		_histoCpt = 0;
  	  	}

    	freeRam = Utils::FreeRam();

    	step++;

    	if(step == 3)
    		step = 0;

    	initGraphics();
    	break;

  }
}

void loop() {
	uiStep();

	currentFreeRam = Utils::FreeRam();

	if(step == 0){
		cpt++;
		if(cpt == 101)
			cpt = 0;
	}
	else if(step == 1){
		brg++;
		if(brg == 360)
			brg = 0;
	}
	else if(step == 2){
		brg++;
		if(brg == 360)
			brg = 0;

		cpt = 50 * fastmath::isin(brg) + 50;
		_histoCpt->addValue(cpt, 0);
	}

	unsigned long begin = millis();
	if(screen->hasToBeRefreshed()){
		myGLCD->startRendering();
		do{
			screen->redraw();
		}while(myGLCD->keepRendering());
	}
	begin = millis() - begin;
	redrawTime = (float)begin;

	updateMenu();

}


