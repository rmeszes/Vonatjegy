#ifndef VONAT_H
#define VONAT_H

#include "List.hpp"

class Vonat
{
	int vonatSzam;
	size_t kocsik_szama;
	size_t ulesek_per_kocsi;
	struct Kocsi {
		int kocsiSzam;
		struct Ules {
			int ulesSzam;
			bool foglalt = false;
		public:
			Ules(int ulesSzam = 0) :ulesSzam(ulesSzam) {}
		};
		List<Ules> ulesek;
	public:
		Kocsi(size_t ulesek_szama,int kocsiSzam = 0);
	};
	List<Kocsi> kocsik;
public:
	Vonat(int vonatSzam, size_t kocsik_szama, size_t ules_per_kocsi);

	size_t kocsikSzama() const { return kocsik_szama; }
	size_t ulesek() const { return ulesek_per_kocsi; }

	int kocsiSzamAt(size_t i);
};
#endif // !VONAT_H