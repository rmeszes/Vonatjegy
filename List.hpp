#ifndef LIST_H
#define LIST_H
#include <stdexcept>
#include <iostream>
template<class T> class List
{
	struct ListElement {
		T data;
		ListElement* next;
		ListElement(ListElement* p = nullptr) :next(p) {}
	};
    ListElement* start;
public:
    List() {
        start = new ListElement(); //strázsa
    }

    class iterator;
    List(const List& l) :List() {
        iterator first = l.begin();
        iterator last = l.end();
        while (first != last) {
            this->Add(*first++);
        }
    }
    ~List() {
        ListElement* p = start;
        while (p != nullptr) {
            ListElement* temp = p;
            p = p->next;
            delete temp;
        }
        start = nullptr;
    }

    void Add(const T& data) {
        ListElement* p = new ListElement(start);
        p->data = data;
        start = p;
    }

    iterator begin() {
        return(iterator(*this));
    }

    iterator end() {
        return(iterator());
    }

    class iterator {
        ListElement *curr;
    public:
        iterator() :curr(nullptr) {}; //végére állítja az iterátort
        iterator(const List& l) :curr(l.start) {
            if (curr->next == nullptr) curr = nullptr; //strázsa miatt
        }
        iterator& operator++() { //pre
            if (curr != nullptr) {
                curr = curr->next;
                if (curr->next == nullptr) curr = nullptr;
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
            else throw std::out_of_range("hibás iterátor");
        }

        T* operator->() {
            if (curr != nullptr) return &curr->data;
            else throw std::out_of_range("hibás iterátor");
        }
    };
};

#endif // !LIST_H