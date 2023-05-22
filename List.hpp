#ifndef LIST_H
#define LIST_H
#include <stdexcept>
#include <iostream>
template<class T> class List
{
	struct ListElement {
		T data;
		ListElement *next, *prev;
		ListElement(const T& data, ListElement* prev = nullptr, ListElement* next = nullptr) :data(data), prev(prev), next(next) {}
	};
    ListElement* sentinel_begin, *sentinel_end;
public:
    List() :sentinel_begin(nullptr), sentinel_end(nullptr) {}

    List(const List& origin) {
        if (origin.sentinel_begin == nullptr) { //megn�zz�k, hogy az origin lista �res-e
            sentinel_begin = nullptr;
            sentinel_end = nullptr;
        }
        else {
            ListElement* from = origin.sentinel_begin; //a pointer amit v�gigl�ptet�nk az original list�n
            ListElement* current = new ListElement(from->data); //a pointer ami az �jonnan l�trehozott elemekre mutat
            sentinel_begin = current; //be�ll�tom a sentinteleket az �j elemre
            sentinel_end = current;
            while (from != origin.sentinel_end) { 
                current->next = new ListElement(from->next->data, current); //az �j elem l�trehoz�sa

                from = from->next; //pointerek l�ptet�se
                current = current->next;
            }
            sentinel_end = current; //a lista v�ge v�ltozik
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
            sentinel_end->next = new ListElement(data, sentinel_end); //az �j elemet beadja az utols� ut�n
            sentinel_end = sentinel_end->next; //a sentinelt az �j elemre �ll�tjuk
        }
    }

    void push_front(const T& data) {
        if (sentinel_begin == nullptr) {
            sentinel_begin = sentinel_end = new ListElement(data);
        }
        else {
            sentinel_begin->prev = new ListElement(data, nullptr, sentinel_begin); //az �j elemet beadja az utols� ut�n
            sentinel_begin = sentinel_begin->prev; //a sentinelt az �j elemre �ll�tjuk
        }
    }

    bool empty() const { return(sentinel_begin == nullptr); }

    class iterator {
        ListElement *curr;
    public:
        iterator() :curr(nullptr) {}; //v�g�re �ll�tja az iter�tort
        iterator(const List& l) :curr(l.sentinel_begin) {}
        iterator& operator++() { //pre
            if (curr != nullptr) {
                curr = curr->next;
            }
            return(*this);
        }
        iterator operator++(int) { //post
            iterator tmp = *this; //elt�roljuk
            operator++(); //n�vel
            return(tmp);
        }

        iterator& operator--() { //pre
            if (curr != nullptr) {
                curr = curr->prev;
            }
            return(*this);
        }
        iterator operator--(int) { //post
            iterator tmp = *this; //elt�roljuk
            operator--(); //n�vel
            return(tmp);
        }

        bool operator!=(const iterator& i) const {
            return curr != i.curr;
        }

        T& operator*() {
            if (curr != nullptr) return curr->data;
            else throw std::runtime_error("hib�s iter�tor");
        }

        T* operator->() {
            if (curr != nullptr) return &curr->data;
            else throw std::runtime_error("hib�s iter�tor");
        }
    };
    iterator begin() {
        return(iterator(*this));
    }

    iterator end() {
        return(iterator());
    }
};

#endif // !LIST_H