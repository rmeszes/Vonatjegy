#ifndef LISTA_H
#define LISTA_H
template<class T> class List
{
	struct ListElement {
		T data;
		ListElement* next;
		ListElement(ListElement *p = NULL) :next(p) {}
	};
	ListElement* start, * current;
public:
	List() { start = current = new ListElement; }
	void Add(const T& dat);
	bool Next(const T& dat);
};

#endif // !VONAT_H