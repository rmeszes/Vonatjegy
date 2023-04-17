#ifndef VONAT_H
#define VONAT_H

class Vonat
{
	int szam;
public:
	Vonat(int szam = 1) :szam(szam) {}
	int getSzam() { return szam; }
};
#endif // !VONAT_H