#ifndef LIST_H
#define LIST_H
#include <stdexcept>
#include <iostream>
template<class T> class List
{
	struct ListElement {
		T data;
		ListElement * prev, *next;
		explicit ListElement(const T& data, ListElement* prev = nullptr, ListElement* next = nullptr) :data(data), prev(prev), next(next) {}
	};
	ListElement* sentinel_begin, *sentinel_end;
	size_t num_of_elements;
public:
	List() :sentinel_begin(nullptr), sentinel_end(nullptr), num_of_elements(0) {}

	List(const List& origin) :num_of_elements(origin.num_of_elements) {
		if (origin.sentinel_begin == nullptr) { //megnézzük, hogy az origin lista üres-e
			sentinel_begin = nullptr;
			sentinel_end = nullptr;
		}
		else {
			ListElement* from = origin.sentinel_begin; //a pointer amit végigléptetünk az original listán
			ListElement* current = new ListElement(from->data); //a pointer ami az újonnan létrehozott elemekre mutat
			sentinel_begin = current; //beállítom a sentinteleket az új elemre
			sentinel_end = current;
			while (from != origin.sentinel_end) { 
				current->next = new ListElement(from->next->data, current); //az új elem létrehozása

				from = from->next; //pointerek léptetése
				current = current->next;
			}
			sentinel_end = current; //a lista vége változik
		}
	}

	~List() {
		ListElement* p = sentinel_begin;
		while (p != nullptr) {
			ListElement* temp = p;
			p = p->next;
			delete temp;
		}
	}

	void push_back(const T& data) {
		if (sentinel_begin == nullptr) {
			sentinel_begin = sentinel_end = new ListElement(data);
		}
		else {
			sentinel_end->next = new ListElement(data, sentinel_end); //az új elemet beadja az utolsó után
			sentinel_end = sentinel_end->next; //a sentinelt az új elemre állítjuk
		}
		num_of_elements++;
	}

	bool empty() const { return(num_of_elements == 0); }

	size_t size() const { return num_of_elements; }

	T& front() {
		return sentinel_begin->data;
	}

	T& back() {
		return sentinel_end->data;
	}

	class iterator {
		ListElement *curr;
	public:
		iterator() :curr(nullptr) {}; //végére állítja az iterátort
		explicit iterator(const List& l) :curr(l.sentinel_begin) {}
		iterator& operator++() { //pre
			if (curr != nullptr) {
				curr = curr->next;
			}
			return(*this);
		}
		iterator operator++(int) { //post
			iterator tmp = *this; //eltároljuk
			operator++(); //növel
			return(tmp);
		}

		bool operator!=(const iterator& i) const {
			return curr != i.curr;
		}

		T& operator*() {
			if (curr != nullptr) return curr->data;
			else throw std::runtime_error("hibás iterátor");
		}

		T* operator->() {
			if (curr != nullptr) return &curr->data;
			else throw std::runtime_error("hibás iterátor");
		}
	};
	iterator begin() {
		return(iterator(*this));
	}

	iterator end() {
		return(iterator());
	}

	T& operator[](const size_t idx) {
		if (idx >= size()) throw std::out_of_range("index out of range");
		ListElement* it = sentinel_begin;
		for (size_t i = 0; i < idx; i++) it = it->next;
		return it->data;
	}

	T operator[](const size_t idx) const {
		if (idx >= size()) throw std::out_of_range("index out of range");
		ListElement* it = sentinel_begin;
		for (size_t i = 0; i < idx; i++) it = it->next;
		return it->data;
	}
};

#endif // !LIST_H