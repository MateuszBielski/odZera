#include <Modul.h>
template<typename T>
std::shared_ptr<T> WyszukajWModulach_Ptr(std::string rodzajModulu, Modul::MapaStringModul& moduly)
{
    return std::dynamic_pointer_cast<T>(moduly[rodzajModulu]);
}
template<typename T>
T& WyszukajWModulach_Ref(std::string rodzajModulu, Modul::MapaStringModul& moduly)
{
    return *(WyszukajWModulach_Ptr<T>(rodzajModulu,moduly));
}
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
