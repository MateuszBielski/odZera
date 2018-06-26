#include "Komunikat.h"

Komunikat::Komunikat()
{
}

Komunikat::~Komunikat()
{
}
void Komunikat::Wypisz(const char* k)
{
	if(czyWypisac)g_print("\n%s",k);
}
Komunikat::Komunikat(const char* k)
{
	Wypisz(k);
}
bool Komunikat::czyWypisac = true;