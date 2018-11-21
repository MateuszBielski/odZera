#ifndef ZMIENTRYBSTEROWANIA_H
#define ZMIENTRYBSTEROWANIA_H
#include <PrzekierowanieSygnalow.h>


class ZmienTrybSterowania : public PrzekierowanieSygnalow
{
public:
    ZmienTrybSterowania();
    ~ZmienTrybSterowania();
    virtual int PolaczZkimPotrzebujeNaPoczatek() override;
    virtual void UstawIzainstalujPrzyciskW(VBox&) override;
private:
    spConnection connZmianaTrybu;
    bool czyWybranyObiekt;
    void PrzelaczSterowanie();
    void UstawSterowanie(short);
};
#endif // ZMIENTRYBSTEROWANIA_H