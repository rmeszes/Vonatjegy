#ifndef LIST_H
#define LIST_H
#include <stdexcept>
template<class T> class List
{
	struct ListElement {
		T data;
		ListElement* next;
		ListElement(T data, ListElement* p = nullptr) :next(p), data(data) {}
	};
	ListElement* start, * current;
public:
    List() :start(nullptr), current(nullptr) {}
    List(const T& data) : start(new ListElement(data)), current(start) {}
    void Add(const T& data) {
        ListElement* newElement = new ListElement(data);
        if (start == nullptr) {
            start = current = newElement;
        }
        else {
            current->next = newElement;
            current = newElement;
        }
    }
    bool Next(T& data) {
        if (current->next == nullptr) {
            current = start;
            return false;
        }
        data = current->data;
        current = current->next;
        return true;
    }
    ~List() {
        ListElement* p = start;
        while (p != nullptr) {
            ListElement* temp = p;
            p = p->next;
            delete temp;
        }
        start = nullptr;
        current = nullptr;
    }
    T getCurrent() const {
        return current->data;
    }
    T& operator[](size_t i) { //indexel� op., �rhat�an adja vissza az adat pointer�t
        ListElement* p = start;
        for (size_t j = 0; j < i; j++) {
            p = p->next;
            if (p == nullptr) {
                throw std::out_of_range("List_out_of_bound"); //TODO catch, teszt
            }
        }
        return p->data;
    }
};

#endif // !LIST_H