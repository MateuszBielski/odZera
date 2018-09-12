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
	void TransformacjaCalegoWidoku();
    void PobierzWskaznikNaWektorPrzesunieciaPierwotnego(float * );
	void PobierzWskaznikNaWektorPrzesuniecia(float * );
	void PobierzWskaznikNaMacierzObrotu(float *);
	void RysujModele();
    virtual int PolaczZkimPotrzebujeNaPoczatek(); 
    using spModel = std::shared_ptr<Model>;
    void Zaladuj(spModel);
	void WybierzModelOnumerze(short);
    void ZaznaczModelWedlugIndeksu(int i){};
	spModel DajWybranyModel();
	
    //światło
	void WskazModelSwiatla(short );
    spModel DajModelSwiatla();
    void UstawPolozenieSwiatla(float *);
private:
    using vec_spModel = std::vector<spModel>;
    vec_spModel mojeModele;
    
	Model ostroslup;
    short modelSwiatlaMaNumer = 0;
	short numerModeluWybranego = 1;
	float* przesuniecie = nullptr;
    float* przesunieciePierwotne = nullptr;
	float* macierzObrotu = nullptr;
	
};

#endif // RENDEROWANIE_H
