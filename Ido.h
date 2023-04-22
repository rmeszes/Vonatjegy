#ifndef IDO_H
#define IDO_H

#include <iostream>

/// <summary>
/// Class dátum tárolására
/// </summary>
class Datum 
{
	int ev;
	int honap;
	int nap;
public:
	Datum(int ev = 1900, int honap = 1, int nap = 1) :ev(ev), honap(honap), nap(nap) {
		if (ev < 1900 || ev > 9999 || honap < 1 || honap > 12 || nap < 1 || nap > 31) {
			ev = 1900;
			honap = 1;
			nap = 1;
			throw "Invalid date";
		}
	}

	virtual int getEv() const { return ev; }
	virtual int getHo() const { return honap; }
	virtual int getNap() const { return nap; }

	virtual String toString() const {
		String ret;
		return ret + String(ev) + ". " + String(honap) + ". " + String(nap) + ".";
	}
};

/// <summary>
/// Class óra és perc tárolására dátumhoz kötve.
/// </summary>
class Ido :public Datum
{
	int ora;
	int perc;
public:
	Ido(int ev = 1900, int honap = 1, int nap = 1, int ora = 0, int perc = 0) :Datum(ev, honap, nap), ora(ora), perc(perc) {
		if (ora < 0 || ora > 24 || perc < 0 || perc > 59) {
			ora = 0;
			perc = 0;
			throw "Invalid time!";
		}
	}

	int getOra() const { return ora; }
	int getPerc() const { return perc; }

	String toString() const {
		String ret;
		return ret + String(ora) + ':' + String(perc);
	}
};

#endif // !IDO_H