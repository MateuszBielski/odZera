#ifndef STEROWANIEMODYFIKUJPUNKTY_H
#define STEROWANIEMODYFIKUJPUNKTY_H
#include <PrzekierowanieSygnalow.h>


class SterowanieModyfikujPunkty : public PrzekierowanieSygnalow
{
public:
    SterowanieModyfikujPunkty();
    ~SterowanieModyfikujPunkty();
    virtual int PolaczZkimPotrzebujeNaPoczatek() override;
    virtual void UstawIzainstalujPrzyciskW(VBox&) override;
private:
    spConnection connModyfikujPunkty;
    bool sterujPunktami;
    void PrzelaczSterowanie();
    void UstawSterowanie(short);
};
#endif // STEROWANIEMODYFIKUJPUNKTY_H