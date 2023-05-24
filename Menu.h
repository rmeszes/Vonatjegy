#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <functional>

#include "memtrace.h"

#include "List.hpp"
#include "string.h"

using std::cout;
using std::cin;

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
		int choice;
		while (true) {
			std::cout << "MENU\n";
			for (size_t i = 0; i < menuItems.size(); ++i) {
				std::cout << i + 1 << ". " << menuItems[i].label << std::endl;
			}
			std::cout << "0. Kilepes" << std::endl;

			std::cout << "Valasztott menupont: ";
			std::cin >> choice;
			char ch = '\0';
			while (ch != '\n') cin.get(ch);

			if (choice < 0 || choice > menuItems.size()) {
				std::cout << "Ervenytelen valasztas" << std::endl;
				continue;
			}

			if (choice == 0) {
				break;
			}

			// Call the selected menu item's action
			menuItems[choice - 1].action();
		}
	}
};

#endif //MENU_HU