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
    //czy któreś z poniższych funkcji mogą wyjść poza zakres klasy?
//    int WyznaczIndeksObiektuWpunkcie(int , int);
    using stos_int = std::stack<int>;
    stos_int StosNazwObiektuWpunkcie(int , int);
    unsigned WypelnijBuforZaznaczeniaWPunkcie(int,int,unsigned *);
    
    
//    int CoZaznaczono(int,unsigned  int *);//zastąpić poniższąfunkcją
    stos_int CoZaznaczono(int,unsigned  int *);
protected:
    float pozycjaZrodlaSwiatla[4];
    
private:
	virtual void UstawienieSceny();
	virtual void RysujScene();
    virtual void OswietlenieUstaw();
        
};

#endif // EKRANRYSUJACY_H
