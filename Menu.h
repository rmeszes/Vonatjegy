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

	void display() {
		size_t choice;
		while (true) {
			std::cout << "MENU\n";
			for (size_t i = 0; i < menuItems.size(); ++i) {
				std::cout << i + 1 << ". " << menuItems[i].label << std::endl;
			}
			std::cout << (menuItems.size() + 1) << ". Kilepes" << std::endl;

			choice = getnum("Valasztott menupont: ", (menuItems.size() + 1));

			if (choice < 0 || choice > (menuItems.size() + 1)) {
				std::cout << "Ervenytelen valasztas" << std::endl;
				continue;
			}

			if (choice == (menuItems.size() + 1)) {
				break;
			}

			// Call the selected menu item's action
			menuItems[choice - 1].action();
		}
	}
};

#endif //MENU_HU