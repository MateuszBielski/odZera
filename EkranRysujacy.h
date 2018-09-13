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
    int WyznaczIndeksObiektuWpunkcie(int , int);
    int CoZaznaczono(int,unsigned  int *);
protected:
    float pozycjaZrodlaSwiatla[4];
    
private:
	virtual void UstawienieSceny();
	virtual void RysujScene();
    virtual void OswietlenieUstaw();
        
};

#endif // EKRANRYSUJACY_H
