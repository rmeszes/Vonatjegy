#ifndef VONAT_H
#define VONAT_H

class Vonat
{
	int szam;
public:
	Vonat(int szam = 0) :szam(szam) {}
	int getSzam() const { return szam; }
	Vonat(Vonat&);
	Vonat& operator=(const Vonat&);
	void setSzam(const int i) { szam = i; }
};
#endif // !VONAT_H