#ifndef PRZEKIEROWANIESYGNALOW_H
#define PRZEKIEROWANIESYGNALOW_H
#include <Modul.h>

#define OBROTY_ARCBALL 1
#define PRZESUWANIE_PO_EKRANIE 2

class PrzekierowanieSygnalow : public Modul
{
public:
	PrzekierowanieSygnalow();
	~PrzekierowanieSygnalow();
	virtual int PolaczZkimPotrzebujeNaPoczatek();
    virtual void UstawIzainstalujPrzyciskW(VBox&);
    void PrzelaczSterowanie();
    void UstawSterowanie(short);
private:
    spConnection connZmianaTrybu;
    bool czyPrzesuwaj;

};

#endif // PRZEKIEROWANIESYGNALOW_H
