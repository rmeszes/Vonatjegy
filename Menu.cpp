#include "Menu.h"


/// <summary>
/// Egy pozitív egész szám bekérésére szolgál ami > 0
/// </summary>
/// <param name="bekert_adat">A felhasználónak segítség, hogy mit írjon be</param>
/// <param name="max">A maximum elfogadott szám. (nem kötelező)</param>
/// <param name="min">A minimum elfogadott szám. (nem kötelező)</param>
/// <returns>A sikeresen bekért szám</returns>
size_t getnum(const char* bekert_adat, size_t max = SIZE_MAX, size_t min = 0);


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