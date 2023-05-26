//függvény definíciók ide
#include "Vonat.h"

Kocsi::Kocsi(int kocsi_szam, size_t helyek_szama) :kocsi_szam(kocsi_szam), helyek_szama(helyek_szama) {
	if (helyek_szama == 0) { helyek = nullptr; }
	else { helyek = new bool[helyek_szama]; }
	for (size_t i = 0; i < helyek_szama; i++) //inicializálom a tömb elemeit, hogy biztosan false legyen
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
	if (this == &k) {
		return *this;
	}
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
/// <returns>A foglalt hely száma, vagy 0, ha nincs hely</returns>
int Kocsi::getHely() const
{
	for (size_t i = 0; i < helyek_szama; i++)
	{
		if (helyek[i] == false) { //ha talál nem foglalt helyet, visszaadja
			helyek[i] = true;
			return i + 1; //hogy az első ülés száma 1 legyen és így tovább
		}
	}
	return 0;
}

Vonat::Vonat(int vonat_szam, size_t kocsik_szama, size_t helyek_szama, double ar, List<Allomas>& allomasok)
	:vonat_szam(vonat_szam), kocsik_szama(kocsik_szama), ar(ar), allomasok(allomasok), kocsik()
{
	for (size_t i = 0; i < kocsik_szama; i++) //elkészítjük a kocsikat
	{
		kocsik.push_back(Kocsi(100 + i, helyek_szama));
	}
}

Vonat::Vonat(const Vonat& original) 
	:vonat_szam(original.vonat_szam), kocsik_szama(original.kocsik_szama), ar(original.ar), allomasok(original.allomasok), kocsik(original.kocsik)
{
}

/// <summary>
/// Megpróbál helyet foglalni a vonaton
/// </summary>
/// <param name="ret">2 méretű tömb, ennek az első helyére kerül a kocsiszám, a másodikba a hely szám</param>
void Vonat::findSeat(int* ret)
{
	int hely = 0;
	auto kocsi = kocsik.begin();
	while(kocsi != kocsik.end()) {
		hely = kocsi->getHely(); //megpróbál helyet kapni egy kocsin
		if (hely != 0) break;
		++kocsi;
	}
	if (hely != 0) { //ha talált, a tömbbe teszem a kocsiszámot és hely számát
		ret[0] = kocsi->getKocsiSzam();
		ret[1] = hely;
	}
	else {
		ret[0] = 0; ret[1] = 0; //ha nem, akkor 0
	}
}
