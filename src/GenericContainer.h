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

#ifndef genericcontainer_h
#define genericcontainer_h

#include "Arduino.h"

namespace Generic_Container{
template<class V, class T> class Pair{
	T _data;
	V _value;
public :
	Pair(V value, T dat):_data(dat), _value(value){}
	V getValue(){return _value;}
	T getData(){return _data;}
	T setData(T data){
		T previous = _data;
		_data = data;
		return previous;
	}
};

template<class T> class Fifo {
	struct Link {
		T* data;
		Link* next;
		Link(T* dat, Link* nxt) : data(dat), next(nxt) {}
	};

	Link* _first;
	Link* _last;

	Fifo(const Fifo<T>& cp);
public:
	Fifo() : _first(0), _last(0) {}
	~Fifo();

	bool isEmpty(){
		return _first == 0;
	}

	bool contains(T* dat);

	void add(T* dat);

	T* peek() const {
		return _last ? _last->data : 0;
	}

	T* pop();

	T* remove(T* dat){
		Link* prec = 0;
		Link* lk = _first;

		while(lk != 0){
			if(lk->data == dat){
				if(lk == _last)
					_last = prec;
				if(prec == 0){
					_first = lk->next;
					delete lk;
					return dat;
				}
				else{
					prec->next = lk->next;
					delete lk;
					return dat;
				}
			}

			prec = lk;
			lk = lk->next;
		}
		return 0;
	}

	// Classe iterator imbriquée :
	class iterator; // Déclaration requise
	friend class iterator; // En fait un friend
	class iterator { // Le définit maintenant
		Fifo::Link* p;
		public:
		iterator(Fifo::Link* lk) : p(lk) {}
		iterator(const Fifo<T>& tl) : p(tl._first) {}
		// Constructeur par recopie :
		iterator(const iterator& tl) : p(tl.p) {}
		// Itérateur sentinelle de fin :
		iterator() : p(0) {}

		// operator++ retourne un booléen indiquant la fin :
		bool operator++() {
			if(p != 0 && p->next)
				p = p->next;
			else p = 0; // Indique la fin de la liste
			return bool(p);
		}
		
		bool operator++(int) { return operator++(); }
		T* current() const {
			if(!p) return 0;
			return p->data;
		}

		// opérateur de déréférencement de pointeur :
		T* operator->() const {
			return current();
		}
		
		T* operator*() const { return current(); }

		// Conversion en bool pour test conditionnel :
		operator bool() const { return bool(p); }

		// Comparaison pour tester la fin :
		bool operator==(const iterator& it) const {
			return p == it.p;
		}

		bool operator!=(const iterator& it) const {
			return p != it.p;
		}
	};

	iterator begin() const {
		return iterator(*this);
	}

	iterator last() const {
		return iterator(_last);
	}

	iterator end() const { return iterator(); }
};


template<class T> Fifo<T>::~Fifo(){
	while(_first)
		delete pop();
}

template<class T> bool Fifo<T>::contains(T* dat){
	for(Fifo<T>::iterator it = begin(); it != end(); it++){
		if(*it == dat)return true;
	}
	return false;
}

template<class T> void Fifo<T>::add(T* dat) {
	Link* lk = new Link(dat, 0);
	if(_first == 0){
		_first = lk;
	}
	if(_last != 0){
		_last->next = lk;
	}
	_last = lk;
}


template<class T> T* Fifo<T>::pop(){
	if(_first == 0) return 0;
	T* result = _first->data;
	Link* oldfirst = _first;
	_first = _first->next;
	delete oldfirst;
	return result;
}


//Table avec itérateur circulaire
template<class T> class TabPtr{
	T** _tab;
	byte _capacity;
	byte _nbElem;
public:
	TabPtr(byte capacity);
	~TabPtr();

	bool isEmpty(){
		return _capacity == 0;
	}

	int add(T *cp);

	T* operator[](byte index)const;

	// Classe iterator imbriquée :
	class circularIterator; // Déclaration requise
	friend class circularIterator; // En fait un friend
	class circularIterator { // Le définit maintenant
		const TabPtr<T>* _tab;
		byte _currIndex;
	public:
		circularIterator():_tab(0), _currIndex(0){}
		circularIterator(const TabPtr<T>* tab):_tab(tab), _currIndex(0){}
		// Constructeur par recopie :
		circularIterator(const circularIterator& tl) :_tab(tl._tab), _currIndex(tl._currIndex) {}
		
		circularIterator& operator= (const circularIterator& it);

		void operator++();
		void operator++(int) { return operator++(); }

		void operator--();
		void operator--(int) { return operator--(); }

		T* current() const;

		// opérateur de déréférencement de pointeur :
		T* operator->() const;
		T* operator*() const { return current(); }

		// Conversion en bool pour test conditionnel :
		operator bool() const { return bool(current()); }

		// Comparaison
		bool operator==(const circularIterator& it) const {
			return current == it.current();
		}

		bool operator!=(const circularIterator& it) const {
			return current() != it.current();
		}
	};

	circularIterator begin() const {
		return circularIterator(this);
	}
};

template<class T> TabPtr<T>::TabPtr(byte capacity):_capacity(capacity), _nbElem(0){
	if(_capacity == 0){
		Serial.println(F("TabPtr::TabPtr() : La capacité ne peut-être égale à 0."));
		_capacity = 1;
	}

	_tab = new T*[_capacity];
	for(int i = 0; i < _capacity; i++){
		_tab[i] = 0;
	}
}
template<class T> TabPtr<T>::~TabPtr(){
	for(int i = 0; i < _nbElem; i++){
		delete _tab[i];
	}
	delete []_tab;
}

template<class T> int TabPtr<T>::add(T *cp){
	if(_capacity > _nbElem){
		_tab[_nbElem++] = cp;
		return (int)(_nbElem - 1);
	}
	else{
		Serial.println(F("TabPtr::add : Dépassement de la capacité."));
		return -1;
	}
}

template<class T> T* TabPtr<T>::operator[](byte index)const{
	if(index >= _capacity){
		Serial.println(F("TabPtr::operator[] :index supérieur à la capacité."));
		return 0;
	}
	else{
		return _tab[index];
	}
}

template<class T> typename TabPtr<T>::circularIterator::circularIterator& TabPtr<T>::circularIterator::operator= (const circularIterator& it){
	this->_tab = it._tab;
	this->_currIndex = it._currIndex;

	return *this;
}

template<class T> void TabPtr<T>::circularIterator::operator++() {
	_currIndex++;
	if(_currIndex >= _tab->_nbElem){
		_currIndex = 0;
	}
}

template<class T> void TabPtr<T>::circularIterator::operator--() {
	if(_currIndex == 0){
		if(_tab->_nbElem != 0)
			_currIndex = _tab->_nbElem - 1;
		else
			_currIndex = 0;
	}
	else{
		_currIndex--;
	}
}

template<class T> T* TabPtr<T>::circularIterator::current() const {
	return (*_tab)[_currIndex];
}

// opérateur de déréférencement de pointeur :
template<class T> T* TabPtr<T>::circularIterator::operator->() const {
	T* pt = current();
	if(pt == 0){
		Serial.println(F("TabPtr::circularIterator::operator->() : Déréférencement d'une pointeur null ..."));
	}
	return pt;
}


//FILO
template<class T> class List {
	struct Link {
		T* data;
		Link* next;
		Link* previous;
		Link(T* dat, Link* prv, Link*nxt) : data(dat), next(nxt), previous(prv) {}
	};
	Link* first;

	T* deleteLink(Link* elmt){
		T* retour = 0;
		if(elmt != 0){
			Link* previous = elmt->previous;
			Link* next = elmt->next;
			if(previous != 0){
				previous->next = next;
			}
			if(next != 0){
				next->previous = previous;
			}
			if(elmt == first){
				first = next;
			}

			retour = elmt->data;
			delete elmt;
		}

		return retour;
	}
	
	List(const List<T>& cp);
public:
	List() : first(0){}
	~List();

	bool isEmpty()const{
		return first == 0;
	}

	unsigned int size(){
		unsigned int size = 0;
		for(iterator it = begin(); it != end(); it++){
			size++;
		}
		return size;
	}

	void add(T* dat);

	bool insert(T* dat, unsigned int index);

	T* removeAt(unsigned int index);

	T* remove(T* dat);

	T* firstElement() const{
		return first ? first->data : 0;
	}

	T* elementAt(int index);

	// Classe iterator imbriquée :
	class iterator; // Déclaration requise
	friend class iterator; // En fait un friend
	class iterator { // Le définit maintenant
		List::Link* p;
		public:
		iterator(const List<T>& tl) : p(tl.first) {}
		// Constructeur par recopie :
		iterator(const iterator& tl) : p(tl.p) {}
		// Itérateur sentinelle de fin :
		iterator() : p(0) {}

		// operator++ retourne un booléen indiquant la fin :
		bool operator++() {
			if(p != 0 && p->next)
				p = p->next;
			else p = 0; // Indique la fin de la liste
				
			return bool(p);
		}
		
		bool operator++(int) { return operator++(); }

		// operator++ retourne un booléen indiquant la fin :
		bool operator--() {
			if(p != 0 && p->previous)
				p = p->previous;
			else p = 0; // Indique la fin de la liste
				
			return bool(p);
		}
		
		bool operator--(int) { return operator--(); }

		T* current() const {
			if(!p) return 0;
			return p->data;
		}

		// opérateur de déréférencement de pointeur :
		T* operator->() const {
			return current();
		}
		
		T* operator*() const { return current(); }

		// Conversion en bool pour test conditionnel :
		operator bool() const { return bool(p); }

		// Comparaison
		bool operator==(const iterator& it) const {
			return p == it.p;
		}

		bool operator!=(const iterator& it) const {
			return p != it.p;
		}
	};

	iterator begin() const {
		return iterator(*this);
	}

	iterator end() const { return iterator(); }
};

template<class T> List<T>::~List(){
	while(first)
		delete removeAt(0);
}

template<class T> T* List<T>::removeAt(unsigned int index){
	Link* elmt = first;
	unsigned int i = 0;
	while(i < index){
		if(elmt != 0){
			elmt = elmt->next;
			i++;
		}
		else{
			Serial.println(F("List::removeAt index out of range."));
		}
	}

	return deleteLink(elmt);
}

template<class T> T* List<T>::remove(T* dat){
	Link* elmt = first;
	while(elmt != 0 && elmt->data != dat){
		elmt = elmt->next;
	}

	return deleteLink(elmt);
}

template<class T> bool List<T>::insert(T* dat, unsigned int index) {
	Link* elmt = first;
	unsigned int i = 0;
	while(i < index){
		if(elmt != 0){
			elmt = elmt->next;
			i++;
		}
		else{
			Serial.println(F("List::insert index out of range."));
			return false;
		}
	}

	if(elmt != 0){
		Link* previous = elmt;
		Link* next = elmt ? elmt->next : 0;
		Link* newElem = new Link(dat, previous, next);

		if(previous == 0){
			first = newElem;
		}
	}
}

template<class T> void List<T>::add(T* dat) {
	Link* newFirst = new Link(dat, 0, first);
	if(first != 0){
		first->previous = newFirst;
	}
	first = newFirst;
}

template<class T> T* List<T>::elementAt(int index){
	Link elmt = first;
	int i = 0;
	while(i < index && elmt != 0){
		elmt = elmt->next;
		i++;
	}

	return elmt ? elmt->data : 0;
}

//Le type V doit implémenter l'opérateur ==
//Le type T doit être un pointeur.
template <class V, class T> class Map{
private:
	typedef Pair<V, T> P;
	List<P> _list;
public:
	bool isEmpty(){
		return _list.isEmpty();
	}

	unsigned int size(){
		return _list.size();
	}

	T operator[](const V& value)const{
		for(typename List<P>::iterator it = _list.begin(); it != _list.end(); it++){
			if(it->getValue() == value)return it->getData();
		}
		return 0;
	}

	T setData(const V& value, T data){
		for(typename List<P>::iterator it = _list.begin(); it != _list.end(); it++){
			if(it->getValue() == value)
				return it->setData(data);
		}

		P* p = new P(value, data);
		_list.add(p);
		return 0;
	}

	typename List<P>::iterator begin(){return _list.begin();}
	typename List<P>::iterator end(){return _list.end();}
};

}

#endif
