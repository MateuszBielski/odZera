#ifndef MODULY_H
#define MODULY_H
#include <Okno1.h>
#include <OknoGL.h>
#include <SterowanieMysza.h>
#include <Renderowanie.h>
#include <Modul.h>
using spModul = std::shared_ptr<Modul>;
using MapaStringModul = std::map<std::string,spModul>;
using MapaStringRefModul = std::map<std::string,Modul>;//--
class Moduly
{
public:
    Moduly();
    ~Moduly();
    bool DolaczDo(spOkno1);
    int Uruchom();
	int WszystkieDodaj();
    int WszystkiePolaczJakPotrzebuja();
    int WszystkieWyswietlNazwyMap();
    bool DodajModul(spModul );
//    bool DodajRefModul(Modul&& );//--
    template<typename T>
    spModul UtworzModulTypu();
private:
    spOkno1 oknoGlowne;
    
    upOknoGL oknoGL;
    
    /*należy sprawdzić  możliwość łatwego umieszczania obiektu sterowanie w różnych klasach okna/ekranu
     *- wypróbować, w której sprawdzi się najlepiej*/
    std::unique_ptr<Sterowanie> sterowanie;
	std::shared_ptr<Renderowanie> renderowanie;
    std::shared_ptr<EkranGL> pEkranGL;
    
    
    MapaStringModul modulyMoje;
    MapaStringRefModul modulyRefMoje;//--
//    VecRefModul        modulyRefMojeVec;
};
#endif