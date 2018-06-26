#ifndef KOMUNIKAT_H
#define KOMUNIKAT_H
#include <gtkmm.h>
class Komunikat
{
public:
	Komunikat();
	Komunikat(const char * k);
	~Komunikat();
	void Wypisz(const char * k);
	
	static bool czyWypisac;

};

#endif // KOMUNIKAT_H
