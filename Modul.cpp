#include <Modul.h>

Modul::Modul()
{
//	Komunikat("Modul konstruktor");
}
Modul::~Modul()
{
//	Komunikat("Moduł destruktor");
}
void Modul::JestemDodanyDo(MapaStringModul* mapa)
{
	mapaZmodulami = mapa;
}
