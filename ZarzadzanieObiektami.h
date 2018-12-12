#ifndef ZARZADZANIEOBIEKTAMI_H
#define ZARZADZANIEOBIEKTAMI_H
#include <sigc++/sigc++.h>
#include <GrupaModeli.h>
#include <Modul.h>
#include <WidokCechModelu.h>
#include <LinieZnormalnych.h>
#include <ModyfikacjaPunktow.h>

using vec_spModel = std::vector<spModel>;
class ZarzadzanieObiektami : public Modul{
public:
    ZarzadzanieObiektami();
    virtual ~ZarzadzanieObiektami();
    virtual int PolaczZkimPotrzebujeNaPoczatek() override;
    const vec_spModel& MojeModeleRef(){return mojeModele;};
    const short& NumerModeluWybranegoRef(){return numerModeluWybranego;};
    const short& ModelSwiatlaMaNumer(){return modelSwiatlaMaNumer;};
    int Zaladuj(spModel);
	void WybierzModelOnumerze(short int);
    void WybierzModelOnumerze(std::stack<int> &);
    void WyodrebnijZgrupy(std::stack<int> &);
    spModel DajWybranyModel();
    void WybranyModelPrzeniesDoGrupy();
//    void EdycjaPunktuOnumerze(std::stack<int> &,int jakEdytowac);
    //światło
	void WskazModelSwiatla(short );
    spModel DajModelSwiatla();
protected:
//    using vec_spModel = std::vector<spModel>;
    vec_spModel mojeModele;
    using stosGrup = std::stack<spGrupaModeli>;
    stosGrup pusteGrupy;
    spGrupaModeli PrzydzielPustaGrupe();

    void UtworzTyleKostek(int);
    template<class T>
    void UtworzTyleModeli(int);
    
    unsigned ileZaladowanychModeli  = 0;
    
    spLinieN linieNormalnych;
    spWidokCech cechyWybranego;
    
    
    short modelSwiatlaMaNumer = 0;
	short numerModeluWybranego = 1;
    short numerPoprzednioWybranego = 1;
};

#endif // ZARZADZANIEOBIEKTAMI_H
