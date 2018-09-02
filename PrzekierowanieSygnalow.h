#ifndef PRZEKIEROWANIESYGNALOW_H
#define PRZEKIEROWANIESYGNALOW_H
#include <Modul.h>

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
    bool czyWybranyObiekt;

};

#endif // PRZEKIEROWANIESYGNALOW_H
