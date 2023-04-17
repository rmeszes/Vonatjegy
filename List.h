#ifndef LIST_H
#define LIST_H
template<class T> class List
{
	struct ListElement {
		T data;
		ListElement* next;
		ListElement(ListElement *p = nullptr) :next(p) {}
	};
	ListElement* start, * current;
public:
	List() { start = current = new ListElement; }
	void Add(const T& data) {
		ListElement* p;
		for (p = start; p->next != nullptr; p = p->next);
		p->next = new ListElement;
		p->next->data = data;
	}
	//bool Next(const T&);
	~List()
	{
		ListElement* p = start;
		while (p != nullptr) {
			ListElement* temp = p;
			p = p->next;
			delete temp;
		}
		start = nullptr;
		current = nullptr;
	}
	T getCurrent() {
		return current->data;
	}
};

#endif // !LIST_H