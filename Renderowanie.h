#ifndef RENDEROWANIE_H
#define RENDEROWANIE_H
#include <Komunikat.h>
//#include <Model.h>
#include <sigc++/sigc++.h>
//#include <GrupaModeli.h>
#include <Modul.h>
#include <ZarzadzanieObiektami.h>

class Renderowanie1 : public Modul, public sigc::trackable  
{
public:
	Renderowanie1(ZarzadzanieObiektami&);
	~Renderowanie1();
    virtual int PolaczZkimPotrzebujeNaPoczatek(); 
	void TransformacjaCalegoWidoku();
    void PobierzWskaznikNaWektorPrzesunieciaPierwotnego(float * );
	void PobierzWskaznikNaWektorPrzesuniecia(float * );
	void PobierzWskaznikNaMacierzObrotu(float *);
	void RysujModele();
//    using spModel = std::shared_ptr<Model>;
    void UstawRysowanieZnazwami();
	void UtrwalPrzeksztalceniaWybranegoObiektu();
    void UtrwalPunktyWybranegoObiektu();
	void UtrwalPrzeksztalceniaModelu(spModel);
    
    void UstawPolozenieSwiatla(float *);
private:
    void RysujModeleBezNazw();
    void JednorazowoRysujModeleZnazwami();
    using Ptr_F_void_void = void(Renderowanie1::*)();
    Ptr_F_void_void RysujModeleOdpowiednio = &Renderowanie1::RysujModeleBezNazw;
    
//	Model ostroslup;
    
	float* przesuniecie = nullptr;
    float* przesunieciePierwotne = nullptr;
	float* macierzObrotu = nullptr;
	
//    ZarzadzanieObiektami zarzadzanie;
    const vec_spModel& mojeModele;
    const short& numerModeluWybranego;
    const short& modelSwiatlaMaNumer;
};

#endif // RENDEROWANIE_H
/*class Renderowanie : public Modul, public sigc::trackable  
{
public:
	Renderowanie();
	~Renderowanie();
    virtual int PolaczZkimPotrzebujeNaPoczatek(); 
	void TransformacjaCalegoWidoku();
    void PobierzWskaznikNaWektorPrzesunieciaPierwotnego(float * );
	void PobierzWskaznikNaWektorPrzesuniecia(float * );
	void PobierzWskaznikNaMacierzObrotu(float *);
	void RysujModele();
//    using spModel = std::shared_ptr<Model>;
    int Zaladuj(spModel);//z
	void WybierzModelOnumerze(short int);//z
    void WybierzModelOnumerze(std::stack<int> &);//z
    void WyodrebnijZgrupy(std::stack<int> &);//z
    void UstawRysowanieZnazwami();
	spModel DajWybranyModel();//z
    void WybranyModelPrzeniesDoGrupy();//z
	void UtrwalPrzeksztalceniaWybranegoObiektu();
    void UtrwalPunktyWybranegoObiektu();
	void UtrwalPrzeksztalceniaModelu(spModel);
    
    //światło
	void WskazModelSwiatla(short );//z
    spModel DajModelSwiatla();//z
    void UstawPolozenieSwiatla(float *);//z
private:
    
    vec_spModel mojeModele;//z
    using stosGrup = std::stack<spGrupaModeli>;
    stosGrup pusteGrupy;//z
    spGrupaModeli PrzydzielPustaGrupe();//z
    
    unsigned ileZaladowanychModeli  = 0;//z
    
    spLinieN linieNormalnych;//z
    spWidokCech cechyWybranego;//z
    
    void RysujModeleBezNazw();
    void JednorazowoRysujModeleZnazwami();
    using Ptr_F_void_void = void(Renderowanie::*)();
    Ptr_F_void_void RysujModeleOdpowiednio = &Renderowanie::RysujModeleBezNazw;
    
    void UtworzTyleKostek(int);//z
    template<class T>
    void UtworzTyleModeli(int);//z
	Model ostroslup;
    short modelSwiatlaMaNumer = 0;//
	short numerModeluWybranego = 1;//
    short numerPoprzednioWybranego = 1;//
	float* przesuniecie = nullptr;
    float* przesunieciePierwotne = nullptr;
	float* macierzObrotu = nullptr;
	
};*/