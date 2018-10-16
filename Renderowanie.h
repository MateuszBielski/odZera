#ifndef RENDEROWANIE_H
#define RENDEROWANIE_H
#include <Komunikat.h>
#include <Model.h>
#include <sigc++/sigc++.h>
#include <Modul.h>

class Renderowanie : public Modul, public sigc::trackable  
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
    using spModel = std::shared_ptr<Model>;
    spModel Zaladuj(spModel);//wrócić do void
	void WybierzModelOnumerze(short int);
    void WybierzModelOnumerze(std::stack<int> &&);
    void UstawRysowanieZnazwami();
	spModel DajWybranyModel();
    void WybranyModelPrzeniesDoGrupy();
	
    //światło
	void WskazModelSwiatla(short );
    spModel DajModelSwiatla();
    void UstawPolozenieSwiatla(float *);
private:
    using vec_spModel = std::vector<spModel>;
    vec_spModel mojeModele;
    unsigned ileZaladowanychModeli  = 0;
    
    void RysujModeleBezNazw();
    void JednorazowoRysujModeleZnazwami();
    using Ptr_F_void_void = void(Renderowanie::*)();
    Ptr_F_void_void RysujModeleOdpowiednio = &Renderowanie::RysujModeleBezNazw;
    
    void UtworzTyleKostek(int);
	Model ostroslup;
    short modelSwiatlaMaNumer = 0;
	short numerModeluWybranego = 1;
	float* przesuniecie = nullptr;
    float* przesunieciePierwotne = nullptr;
	float* macierzObrotu = nullptr;
	
};

#endif // RENDEROWANIE_H
