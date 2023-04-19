#ifndef VONAT_H
#define VONAT_H

#include "List.hpp"

class Vonat {
public:
	struct Hely {
		int helySzam;
		bool foglalt;
		Hely(int helySzam) :helySzam(helySzam), foglalt(false) {}
	};

	class Kocsi {
		List<Hely> helyek;
		int kocsiSzam;
	public:
		Kocsi(int kocsiSzam, int helyekSzama) :kocsiSzam(kocsiSzam) {
			for (int i = 0; i < helyekSzama; i++) {
				helyek.Add(Hely(i + 1));
			}
		}

		const List<Hely>& getHelyek() const { return helyek; }
		int getKocsiSzam() const { return kocsiSzam; }
	}; //kocsi vége

private: // Vonat
	List<Kocsi> kocsik;
	int vonatSzam;
public:
	Vonat(int vonatSzam, int kocsikSzama, int hely_per_kocsi) :vonatSzam(vonatSzam) {
		for (int i = 0; i < kocsikSzama; i++)
		{
			kocsik.Add(Kocsi(i + 1, hely_per_kocsi));
		}
	}
	const List<Kocsi>& getKocsik() const { return kocsik; }
	int getVonatSzam() const { return vonatSzam; }
};
#endif // !VONAT_H