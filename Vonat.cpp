#include "Vonat.h"

//�rt�kad� op.
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
/// K�r egy helyet a kocsiban
/// </summary>
/// <returns>Visszat�r a foglalt hely sz�m�val, vagy 0-val, ha nincs hely</returns>
unsigned int Kocsi::getHely() const
{
	for (size_t i = 0; i < helyek_szama; i++)
	{
		if (helyek[i] == false) { //ha tal�l nem foglalt helyet, visszaadja
			helyek[i] = true;
			return i + 1; //hogy az els� �l�s sz�ma 1 legyen �s �gy tov�bb
		}
	}
	return 0;
}


/// <summary>
/// Megpr�b�l helyet foglalni a vonaton
/// </summary>
/// <param name="ret">2 m�ret� t�mb, ennek az els� hely�re ker�l a kocsisz�m, a m�sodikba a hely sz�m</param>
void Vonat::findSeat(unsigned int* ret)
{
	Kocsi *temp = kocsik[0];
	unsigned int hely = 0;
	for(size_t i = 0; i < kocsik_szama; i++) {
		temp = kocsik[i]; //megpr�b�l helyet kapni egy kocsin
		hely = temp->getHely();
		if (hely != 0) break;
	}
	if (hely != 0) { //ha tal�lt, a t�mbbe teszem a kocsisz�mot �s hely sz�m�t
		ret[0] = temp->getKocsiSzam();
		ret[1] = hely;
		std::cout << "Kiadtuk a " << temp->getKocsiSzam() << ". sz�m� kocsi " << hely << ". sz�m� �l�s�t." << std::endl;
	}
	else {
		ret[0] = 0; ret[1] = 0; //ha nem, akkor 0
	}
}