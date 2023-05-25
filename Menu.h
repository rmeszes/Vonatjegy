#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <functional>

#include "memtrace.h"

#include "List.hpp"
#include "string.h"

using std::cout;
using std::cin;


size_t getnum(const char* bekert_adat, size_t max = SIZE_MAX, size_t min = 0);
class Menu
{
	struct MenuItem { // 2 elem összekötésére szolgál csak
		String label;
		std::function<void()> action;
	};

	List<MenuItem> menuItems;
public:
	void addItem(const String& label, std::function<void()> action) {
		menuItems.push_back({ label,action });
	}

	void display();
};

#endif //MENU_HU