#ifndef MODULY_H
#define MODULY_H
#include <Okno1.h>
#include <Modul.h>
#include <OknoGL.h>
#include <EkranRysujacy.h>
#include <SterowanieMysza.h>
#include <Renderowanie.h>
using spModul = std::shared_ptr<Modul>;
using MapaStringModul = std::map<std::string,spModul>;
using MapaStringRefModul = std::map<std::string,Modul>;//--
class Moduly
{
public:
    Moduly();
    ~Moduly();
    bool DolaczDo(spOkno1);
	int WszystkieDodaj();
    int WszystkiePolaczJakPotrzebuja();
    int WszystkieNazwyWyswietl();
    bool DodajModul(spModul );
    template<typename T>
    spModul UtworzModulTypu();
private:
    spOkno1 oknoGlowne;
    MapaStringModul modulyMoje;
    
    
    
};
#endif