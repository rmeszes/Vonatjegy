#include "Vonat.h"
#include <iostream>

Vonat::Vonat(int vonatSzam, size_t kocsik_szama, size_t ules_per_kocsi) :vonatSzam(vonatSzam), kocsik_szama(kocsik_szama), ulesek_per_kocsi(ules_per_kocsi)
{
	for (size_t i = 0; i < kocsik_szama; i++)
	{
		kocsik.Add(Kocsi(100 + i)); //a kocsik száma 100-tõl kezdõdik
	}
}

int Vonat::kocsiSzamAt(size_t i)
{
	return kocsik[i].kocsiSzam;
}

Vonat::Kocsi::Kocsi(size_t ulesek_szama, int kocsiSzam) :kocsiSzam(kocsiSzam)
{
	for (size_t i = 0; i < ulesek_szama; i++) {
		ulesek.Add(Ules(i + 1));
	}
}
