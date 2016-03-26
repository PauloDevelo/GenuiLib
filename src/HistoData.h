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

#ifndef HISTODATA_H_
#define HISTODATA_H_

#include "IHistoDataListener.h"
#include "MyMath.h"

//#define HISTODATA_H_DEBUG 1

template <class T> class HistoData{
private:
	//Memory block of data that will contain the history
	T* _histo;
	//Contains the position of the last data for each scales
	unsigned int* _starts;

	//Size of the memory block
	const unsigned int _size;
	//Number of scales
	const unsigned char _nbScale;

	//Min and max values of the data.
	const long _MIN;
	const long _MAX;

	//Min and max of the stored data
	T _min;
	T _max;

	T MAX_T;

	mutable IHistoDataListener* _listener;

	bool readData(unsigned int i, unsigned char scale, long& value)const{
		if(_histo[(int)scale * (int)_size + (int)i] == 0){
			return false;
		}

		value = fastmath::roundedmap(_histo[(unsigned int)scale * _size + i], 1, MAX_T, _MIN, _MAX);
		return true;
	}

public:
	/**
	 * unsigned char size : Number of data to store in the history
	 * unsigned char nbScale : Number of time scales
	 * int MIN Minimum value of the data
	 * int MAX Maximum value of the data
	 * unsigned int resolution Number maximum of different values. The resolution will define the number of bit to store the data
	 */
	HistoData(unsigned int size, unsigned char nbScale, long MIN, long MAX):
		_size(size), _nbScale(nbScale),
		_MIN(MIN), _MAX(MAX), _listener(0){

		MAX_T = 1;
		for(unsigned int i = 0; i < sizeof(T); i++){
			MAX_T *= 255;
		}

		_min = MAX_T;
		_max = 1;

		_histo = new T[size * nbScale];
		for(unsigned int i = 0; i < (unsigned int)(nbScale * size); i++){
			_histo[i] = 0;
		}

		_starts = new unsigned int[nbScale];
		for(unsigned int scale = 0; scale < nbScale; scale++){
			_starts[scale] = 0;
		}
	}
	~HistoData(){
		delete[] _histo;
		delete[] _starts;
	}

	void addListener(IHistoDataListener* listener)const{
		_listener = listener;
	}

	void addValue(long value, unsigned char scale){
		#ifdef HISTODATA_H_DEBUG
		Serial.print("addValue-->");Serial.print(value);Serial.print(", ");Serial.println(scale);
		#endif

		unsigned int ind = (unsigned int)scale * _size + _starts[(unsigned int)scale]++;

		bool findNewMin = false;
		if(_histo[ind] == _min){
			findNewMin = true;
		}

		bool findNewMax = false;
		if(_histo[ind] == _max){
			findNewMax = true;
		}

		_histo[ind] = fastmath::roundedmap(value, _MIN, _MAX, 1, MAX_T);

		if(_histo[ind] > _max){
			_max = _histo[ind];
		}
		else if(findNewMax){
			_max = 1;
			for(int i = 0; i < (int)getSize() * (int)getNbScale(); i++)
				if(_max < _histo[i])
					_max = _histo[i];

		}

		if(_histo[ind] < _min){
			_min = _histo[ind];
		}
		else if(findNewMin){
			_min = MAX_T;
			for(int i = 0; i < (int)getSize() * (int)getNbScale(); i++)
				if(_min > _histo[i] && _histo[i] != 0)
					_min = _histo[i];
		}

		if(_starts[scale] == _size){
			_starts[scale] = 0;
		}

		if(_listener != 0){
			_listener->onHistoDataModified();
		}

		#ifdef HISTODATA_H_DEBUG
		Serial.print("<--addValue ");Serial.print(ind);Serial.print(", ");Serial.println(_histo[ind]);
		#endif
	}

	long get_max() const{
		return fastmath::roundedmap(_max, 1, MAX_T, _MIN, _MAX);
	}

	long get_min() const{
		return fastmath::roundedmap(_min, 1, MAX_T, _MIN, _MAX);
	}

	unsigned char getSize() const{
		return _size;
	}

	/**
	 * Permet d'obtenir la valeur dans l'historique de la donnée située en position i pour l'échelle scale.
	 * i = 0, correspond à la donnée la plus fraiche.
	 * This function is deprecated. Use an iterator.
	 */
	bool getValue(unsigned int i, unsigned char scale, long& value)const{
		#ifdef HISTODATA_H_DEBUG
		Serial.print("getValue-->");Serial.print(i);Serial.print(", ");Serial.println(scale);
		#endif

		bool r;
		if(_starts[scale] >= 1 + i)
			r = readData(_starts[scale] - 1 - i, scale, value);
		else
			r = readData(_size + _starts[scale] - 1 - i, scale, value);

		#ifdef HISTODATA_H_DEBUG
		Serial.print("<--getValue ");Serial.print(value);Serial.print(", ");Serial.println(r);
		#endif

		return r;
	}

	unsigned char getNbScale()const{return _nbScale;}

	// Classe iterator imbriquÃ©e :
	class iterator; // DÃ©claration requise
	friend class iterator; // En fait un friend

	class iterator { // Le dÃ©finit maintenant
		const HistoData* _h;
		signed int _i;
		const unsigned char _scale;

		public:
		iterator(const HistoData* h, unsigned char scale, signed char i) : _h(h), _i(i), _scale(scale) {}
		iterator(const HistoData* h, unsigned char scale) : _h(h), _i((int)h->_starts[scale] - 1), _scale(scale) {}
		// Constructeur par recopie :
		iterator(const iterator& tl) : _h(tl._h), _i(tl._i), _scale(tl._scale) {}



		// operator++ retourne un boolÃ©en indiquant la fin :
		bool operator++() {
			if(_i == -1)
				return false;
			else if((unsigned int)_i == _h->_starts[_scale]){
				_i = -1;
				return false;
			}
			else{
				_i--;
				if(_i == -1){
					_i = _h->_size - 1;
				}
				return true;
			}
		}

		bool operator++(int) { return operator++(); }

		long current() const {
			long value;
			_h->readData(_i, _scale, value);

			return value;
		}

		long operator*() const { return current(); }

		// Conversion en bool pour test conditionnel :
		operator bool() const { return bool(_i != -1); }

		// Comparaison pour tester l'égalité :
		bool operator==(const iterator& it) const {
			return _h == it._h && _scale == it._scale && _i == it._i;
		}

		bool operator!=(const iterator& it) const {
			return !(*this == it);
		}
	};

	iterator begin(unsigned int scale) const {
		return iterator(this, scale);
	}

	iterator end(unsigned int scale) const { return iterator(this, scale, -1); }
};




#endif /* HISTODATA_H_ */
