#include "Vonat.h"

//Értékadó op.
Kocsi& Kocsi::operator=(const Kocsi& k)
{
	kocsi_szam = k.kocsi_szam;
	helyek_szama = k.helyek_szama;
	if (helyek != nullptr) delete[] helyek;
	helyek = new bool[helyek_szama];
	for (size_t i = 0; i < helyek_szama; i++)
	{
		this->helyek[i] = k.helyek[i];
	}
	return *this;
}

/// <summary>
/// Kér egy helyet a kocsiban
/// </summary>
/// <returns>Visszatér a foglalt hely számával, vagy 0-val, ha nincs hely</returns>
unsigned int Kocsi::getHely() const
{
	for (size_t i = 0; i < helyek_szama; i++)
	{
		if (helyek[i] == false) { //ha talál nem foglalt helyet, visszaadja
			helyek[i] = true;
			return i + 1; //hogy az elsõ ülés száma 1 legyen és így tovább
		}
	}
	return 0;
}


/// <summary>
/// Megpróbál helyet foglalni a vonaton
/// </summary>
/// <param name="ret">2 méretû tömb, ennek az elsõ helyére kerül a kocsiszám, a másodikba a hely szám</param>
void Vonat::findSeat(unsigned int* ret)
{
	Kocsi *temp = kocsik[0];
	unsigned int hely = 0;
	for(size_t i = 0; i < kocsik_szama; i++) {
		temp = kocsik[i]; //megpróbál helyet kapni egy kocsin
		hely = temp->getHely();
		if (hely != 0) break;
	}
	if (hely != 0) { //ha talált, a tömbbe teszem a kocsiszámot és hely számát
		ret[0] = temp->getKocsiSzam();
		ret[1] = hely;
		std::cout << "Kiadtuk a " << temp->getKocsiSzam() << ". számú kocsi " << hely << ". számú ülését." << std::endl;
	}
	else {
		ret[0] = 0; ret[1] = 0; //ha nem, akkor 0
	}
}