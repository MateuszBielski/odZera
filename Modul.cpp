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
std::shared_ptr<Modul> Modul::WyszukajWDodanychModulach(std::string rodzajModulu)
{
    return (*mapaZmodulami)[rodzajModulu];
}
template<typename T>
T& Modul::WyszkajWmodulachIzwrocWlasciwyTyp(std::string rodzajModulu)
{
    auto wskTyp = std::dynamic_pointer_cast<T>(WyszukajWDodanychModulach(rodzajModulu));
    return *wskTyp;
}

