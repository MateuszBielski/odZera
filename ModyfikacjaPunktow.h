#ifndef MODYFIKACJAPUNKTOW_H
#define MODYFIKACJAPUNKTOW_H
#include <list>
#include "WspolrzedneImacierzeSterowania.h"

/*#define WSKAZ_NOWY 10
#define DODAJ_KOLEJNY 11
#define USUN_Z_EDYTOWANYCH 12*/

class PunktModyfikowany 
{
public:
    PunktModyfikowany();
    PunktModyfikowany(float *);
    ~PunktModyfikowany();
    void PobierzIstniejaceWartosci();
    void UstawNoweWartosci();
    bool operator==(const PunktModyfikowany& rhs);
//    bool operator!=(const PunktModyfikowany& p1,const PunktModyfikowany& p2);
    void UwzglednijZmiane(float * d);
private:
    float * adresZrodla;
    float wartosciDotychczasowe[3],wartosciChwilowe[3], wartosciObliczone[3];
    //float wagaDzialania[3];
    
};
using zbiorPktMod = std::list<PunktModyfikowany>;
using it_zbiorPktMod = zbiorPktMod::iterator;
class ModyfikacjaPunktow : public WspolrzedneImacierzeSterowania
{
public:
	ModyfikacjaPunktow();
	~ModyfikacjaPunktow();
    void WyczyscIwstawJedenPunkt(float *);
    void DodajPunkt(float *);
    void UsunPunkt(float *);
    virtual void ZmienM_Pos_zgodnieZruchemKursora3D() override;
private:
    it_zbiorPktMod WyszukajWsrodPunktowWgAdresu(float *);
    zbiorPktMod mojePunkty;
};

#endif // MODYFIKACJAPUNKTOW_H
