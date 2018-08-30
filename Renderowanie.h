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
private:
    using vec_spModel = std::vector<spModel>;
    vec_spModel mojeModele;
    
	Model ostroslup;
    
	
};

#endif // RENDEROWANIE_H
