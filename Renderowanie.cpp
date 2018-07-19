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
//	Komunikat("Renderowanie::Renderuj()");
//    g_print(", %d, %d",i,b);
	ostroslup.RysujOstroslup();
}
int Renderowanie::PolaczZkimPorzebujeNaPoczatek()
{
    return 0;
}
