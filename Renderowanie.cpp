#include "Renderowanie.h"

Renderowanie::Renderowanie()
{
}

Renderowanie::~Renderowanie()
{
}
void Renderowanie::Renderuj( bool b, int i)
{
	Komunikat("Renderowanie::Renderuj()");
	ostroslup.RysujOstroslup();
}
