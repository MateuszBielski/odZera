#include <Modul.h>
Modul::Modul()
{
//	Komunikat("Modul konstruktor");
}
Modul::~Modul()
{
//	Komunikat("Moduł destruktor");
}
void Modul::JestemDodanyDo(MapaStrModul* mapa)
{
	mapaZmodulami = mapa;
}
Modul* Modul::WyszukajWDodanychModulach(std::string rodzajModulu)
{
	auto modul = (*mapaZmodulami)[rodzajModulu];
    return &modul;
}
