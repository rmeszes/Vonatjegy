#include "Menu.h"

void Menu::display() {
	 while (true) {
		 size_t choice;
		 std::cout << "MENU\n";
		 for (size_t i = 0; i < menuItems.size(); ++i) {
			 std::cout << i + 1 << ". " << menuItems[i].label << std::endl;
		 }
		 std::cout << (menuItems.size() + 1) << ". Kilepes" << std::endl;

		 choice = getnum("Valasztott menupont: ", (menuItems.size() + 1));

		 if (choice == (menuItems.size() + 1)) {
			 break;
		 }

		 // Call the selected menu item's action
		 menuItems[choice - 1].action();
	 }
}