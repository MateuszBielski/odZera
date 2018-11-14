#ifndef ZARZADZANIEOBIEKTAMI_H
#define ZARZADZANIEOBIEKTAMI_H
#include <sigc++/sigc++.h>
#include <GrupaModeli.h>
#include <Modul.h>
#include <WidokCechModelu.h>
#include <LinieZnormalnych.h>

using vec_spModel = std::vector<spModel>;
class ZarzadzanieObiektami : public Modul{
public:
    ZarzadzanieObiektami();
    virtual ~ZarzadzanieObiektami();
    virtual int PolaczZkimPotrzebujeNaPoczatek() override;
    const vec_spModel& MojeModeleRef(){return mojeModele;};
    const short& NumerModeluWybranegoRef(){return numerModeluWybranego;};
    const short& ModelSwiatlaMaNumer(){return modelSwiatlaMaNumer;};
    int Zaladuj(spModel);//z
	void WybierzModelOnumerze(short int);//z
    void WybierzModelOnumerze(std::stack<int> &);//z
    void WyodrebnijZgrupy(std::stack<int> &);//z
    spModel DajWybranyModel();//z
    void WybranyModelPrzeniesDoGrupy();//z
    //światło
	void WskazModelSwiatla(short );//z
    spModel DajModelSwiatla();//z
protected:
//    using vec_spModel = std::vector<spModel>;
    vec_spModel mojeModele;//z
    using stosGrup = std::stack<spGrupaModeli>;
    stosGrup pusteGrupy;//z
    spGrupaModeli PrzydzielPustaGrupe();//z

    void UtworzTyleKostek(int);//z
    template<class T>
    void UtworzTyleModeli(int);//z
    
    unsigned ileZaladowanychModeli  = 0;//z
    
    spLinieN linieNormalnych;//z
    spWidokCech cechyWybranego;//z
    
    short modelSwiatlaMaNumer = 0;//z
	short numerModeluWybranego = 1;//z
    short numerPoprzednioWybranego = 1;//z
};

#endif // ZARZADZANIEOBIEKTAMI_H
