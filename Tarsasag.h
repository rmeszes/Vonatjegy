#ifndef TARSASAG_H
#define TARSASAG_H

#include "memtrace.h"
#include "string.h"
#include "Vonat.h"
#include "Jegy.h"

class Tarsasag {
	int jegyszam;
	int vonatszam;
	List<Vonat> vonatok;
	List<std::shared_ptr<Jegy>> eladott_jegyek;

	Vonat& findVonat();
public:
	Tarsasag() :jegyszam(1000000), vonatszam(1000) {}

	/// <summary>
	/// Bekéri a felhasználótól a szükséges adatokat, majd hozzáad egy vonatot a társasághoz
	/// </summary>
	void addVonat();

	/// <summary>
	/// A felhasználótól addig kér be vonatszámot, amíg nem ír be egy létezőt
	/// </summary>
	/// <returns>A megfelelő vonat referenciája</returns>
	void listVonatok(std::ostream& os = std::cout); 

	/// <summary>
	/// Bekéri a felhasználótól a szükséges adatokat egy jegy vásárlásához, majd a jegyet elkészíti
	/// és hozzáadja az eladott_jegyek listájához
	/// </summary>
	void buyTicket();

	/// <summary>
	/// Bekéri a felhasználótól a szükséges adatokat egy diákjegy vásárlásához, majd a jegyet elkészíti
	/// és hozzáadja az eladott_jegyek listájához
	/// </summary>
	void buyStudentTicket();


	/// <summary>
	/// Kiírja az összes ezen társaság által eladott jegyet.
	/// </summary>
	/// <param name="os">A cél ostream</param>
	void eladottJegyek(std::ostream& os = std::cout);
};

#endif
