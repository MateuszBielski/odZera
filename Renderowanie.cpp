#include "Renderowanie.h"

Renderowanie::Renderowanie()
{
	nazwa = "renderowanie";
    Komunikat("Renderowanie");
}

Renderowanie::~Renderowanie()
{
    Komunikat("~Renderowanie");
}
void Renderowanie::Renderuj( bool b, int i)
{
	Komunikat("Renderowanie::Renderuj()");
	ostroslup.RysujOstroslup();
}
int Renderowanie::PolaczZkimPotrzebujeNaPoczatek()
{
    return 0;
}
