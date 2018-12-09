#ifndef RENDEROWANIE_H
#define RENDEROWANIE_H
#include <Komunikat.h>
#include <sigc++/sigc++.h>
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
    void UstawRysowanieZnazwami();
    void UstawRysowanieZwidocznymiPunktami(bool tak);
    void UstawRysowanieTylkoPunktowZnazwami();
	void UtrwalPrzeksztalceniaWybranegoObiektu();
    void UtrwalPunktyWybranegoObiektu();
	void UtrwalPrzeksztalceniaModelu(spModel);
    
    void UstawPolozenieSwiatla(float *);
private:
    void RysujModeleBezNazw();
    void RysujZwidocznymiPunktami();
    void JednorazowoRysujModeleZnazwami();
    using Ptr_F_void_void = void(Renderowanie1::*)();
    Ptr_F_void_void RysujModeleOdpowiednio = &Renderowanie1::RysujModeleBezNazw;
    
	float* przesuniecie = nullptr;
    float* przesunieciePierwotne = nullptr;
	float* macierzObrotu = nullptr;
	
//    ZarzadzanieObiektami zarzadzanie;
    const vec_spModel& mojeModele;
    const short& numerModeluWybranego;
    const short& modelSwiatlaMaNumer;
};

#endif // RENDEROWANIE_H
