#ifndef RENDEROWANIE_H
#define RENDEROWANIE_H
#include <Komunikat.h>
#include <EkranGL.h>
#include <Model.h>
#include <sigc++/sigc++.h>
#include <Modul.h>

class Renderowanie : public Modul, public sigc::trackable  
{
public:
	Renderowanie();
	~Renderowanie();
	void Renderuj( bool b, int i);
    virtual int PolaczZkimPotrzebujeNaPoczatek(); 
    using spModel = std::shared_ptr<Model>;
    void Zaladuj(spModel);
    //światło
    spModel DajModelSwiatla();
    void UstawPolozenieSwiatla(float *);
private:
    using vec_spModel = std::vector<spModel>;
    vec_spModel mojeModele;
    
	Model ostroslup;
    short modelSwiatla = 0;
	
};

#endif // RENDEROWANIE_H
