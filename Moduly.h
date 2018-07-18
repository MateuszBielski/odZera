#ifndef MODULY_H
#define MODULY_H
#include <Okno1.h>
#include <OknoGL.h>
#include <SterowanieMysza.h>
#include <Renderowanie.h>
#include <Modul.h>
using spModul = std::shared_ptr<Modul>;
using MapaStringModul = std::map<std::string,spModul>;
<<<<<<< HEAD
using MapaStringRefModul = std::map<std::string,Modul>;
using VecRefModul = std::vector<Modul>;
=======
using MapaStringRefModul = std::map<std::string,Modul>;//--
>>>>>>> wskazModWmapie
class Moduly
{
public:
    Moduly();
    ~Moduly();
    bool DolaczDo(spOkno1);
    int Uruchom();
<<<<<<< HEAD
    int WszystkieDodaj();
    int WszystkiePolaczJakPotrzebuja();
    int WszystkieWyswietlNazwy();
    int WszystkieWyswietlNazwyMap();
//    bool DodajModul(spModul );
    bool DodajRefModul(Modul&& );
=======
	int WszystkieDodaj();
    bool DodajModul(spModul );
    bool DodajRefModul(Modul&& );//--
    template<typename T>
    spModul UtworzModulTypu();
>>>>>>> wskazModWmapie
private:
    spOkno1 oknoGlowne;
    
    upOknoGL oknoGL;
    
    /*należy sprawdzić  możliwość łatwego umieszczania obiektu sterowanie w różnych klasach okna/ekranu
     *- wypróbować, w której sprawdzi się najlepiej*/
    std::unique_ptr<Sterowanie> sterowanie;
	std::shared_ptr<Renderowanie> renderowanie;
    std::shared_ptr<EkranGL> pEkranGL;
    
    
    MapaStringModul modulyMoje;
<<<<<<< HEAD
    MapaStringRefModul modulyRefMoje;
    VecRefModul        modulyRefMojeVec;
=======
    MapaStringRefModul modulyRefMoje;//--
>>>>>>> wskazModWmapie
    
};
#endif