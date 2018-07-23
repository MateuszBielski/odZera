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
Modul::spModul Modul::WyszukajWDodanychModulach(std::string rodzajModulu)
{
    return (*mapaZmodulami)[rodzajModulu];
}
template<typename T>
auto& Modul::WyszkajWmodulachIzwrocWlasciwyTyp(std::string rodzajModulu)
{
    return *(std::dynamic_pointer_cast<T>(WyszukajWDodanychModulach(rodzajModulu)));
}
