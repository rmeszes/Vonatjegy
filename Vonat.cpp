#include "Vonat.h"

Vonat::Vonat(Vonat& v) :szam(v.szam)
{}

Vonat& Vonat::operator=(const Vonat& v)
{
	szam = v.szam;
	return *this;
}

