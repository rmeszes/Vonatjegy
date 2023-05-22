//f�ggv�ny defin�ci�k ide
#include "Vonat.h"

Kocsi::Kocsi(int kocsi_szam = 0, size_t helyek_szama = 0) :kocsi_szam(kocsi_szam), helyek_szama(helyek_szama) {
	if (helyek_szama == 0) { helyek = nullptr; }
	else { helyek = new bool[helyek_szama]; }
	for (size_t i = 0; i < helyek_szama; i++) //inicializ�lom a t�mb elemeit, hogy biztosan false legyen
	{
		helyek[i] = false;
	}
}

Kocsi::Kocsi(const Kocsi& k) :kocsi_szam(k.kocsi_szam), helyek_szama(k.helyek_szama) {
	helyek = new bool[helyek_szama];
	for (size_t i = 0; i < helyek_szama; i++)
	{
		this->helyek[i] = k.helyek[i];
	}
}

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
/// <returns>A foglalt hely sz�ma, vagy 0, ha nincs hely</returns>
int Kocsi::getHely() const
{
	for (int i = 0; i < helyek_szama; i++)
	{
		if (helyek[i] == false) { //ha tal�l nem foglalt helyet, visszaadja
			helyek[i] = true;
			return i + 1; //hogy az els� �l�s sz�ma 1 legyen �s �gy tov�bb
		}
	}
	return 0;
}

Vonat::Vonat(int vonat_szam, size_t kocsik_szama, size_t helyek_szama, double ar, List<Allomas>& allomasok)
	:vonat_szam(vonat_szam), kocsik_szama(kocsik_szama), ar(ar), allomasok(allomasok)
{
	for (size_t i = 0; i < kocsik_szama; i++) //elk�sz�tj�k a kocsikat
	{
		kocsik.push_back(Kocsi(100 + i, helyek_szama));
	}
}

/// <summary>
/// Megpr�b�l helyet foglalni a vonaton
/// </summary>
/// <param name="ret">2 m�ret� t�mb, ennek az els� hely�re ker�l a kocsisz�m, a m�sodikba a hely sz�m</param>
void Vonat::findSeat(int* ret)
{
	List<Kocsi>::iterator it = kocsik.begin();
	int hely = 0;
	while (it != kocsik.end()) { 
		hely = it->getHely(); //megpr�b�l helyet kapni egy kocsin
		if (hely != 0) break;
		it++;
	}
	if (hely != 0) { //ha tal�lt, a t�mbbe teszem a kocsisz�mot �s hely sz�m�t
		ret[0] = it->getKocsiSzam();
		ret[1] = hely;
		std::cout << "Kiadtuk a " << it->getKocsiSzam() << ". sz�m� kocsi " << hely << ". sz�m� �l�s�t." << std::endl;
	}
	else {
		ret[0] = 0; ret[1] = 0; //ha nem, akkor 0
	}
}
