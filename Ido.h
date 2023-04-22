#ifndef IDO_H
#define IDO_H

#include <iostream>

class Datum 
{
	int ev;
	int honap;
	int nap;
public:
	Datum(int ev = 1900, int honap = 1, int nap = 1) :ev(ev), honap(honap), nap(nap) {
		
	}

	int getEv() const { return ev; }
	int getHo() const { return honap; }
	int getNap() const { return nap; }

	String toString() const {

	}
};

/// <summary>
/// class óra és perc kezelésére
/// </summary>
class Ido
{
	int ora;
	int perc;


};

#endif // !IDO_H