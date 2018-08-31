#ifndef EKRANRYSUJACY_H
#define EKRANRYSUJACY_H
#include <EkranGL.h>
class EkranRysujacy : public EkranGL
{
public:
	EkranRysujacy();
	~EkranRysujacy();
    void UstawPozycjeZrodlaSwiatla(float *) ;
    void PodajPozycjeZrodlaSwiatla(float *);
    virtual void WyszukujeIustawiamWskaznikiDoInnychModulow() override;
protected:
    float pozycjaZrodlaSwiatla[4];
    
private:
	virtual void UstawienieSceny();
	virtual void RysujScene();
    virtual void OswietlenieUstaw();
        
};

#endif // EKRANRYSUJACY_H
