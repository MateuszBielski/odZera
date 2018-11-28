#ifndef STEROWANIEMODYFIKUJPUNKTY_H
#define STEROWANIEMODYFIKUJPUNKTY_H
#include <PrzekierowanieSygnalow.h>
#include <SterowanieMysza.h>


class SterowanieModyfikujPunkty : public PrzekierowanieSygnalow
{
public:
    SterowanieModyfikujPunkty(SterowanieMyszaVar_2&);
    ~SterowanieModyfikujPunkty();
    virtual int PolaczZkimPotrzebujeNaPoczatek() override;
    virtual void UstawIzainstalujPrzyciskW(VBox&) override;
private:
    spConnection connModyfikujPunkty;
    bool sterujPunktami;
    void PrzelaczSterowanie();
    void WlaczMojeSterowanie();
    void PrzywrocPoprzednieSterowanie();
    SterowanieMyszaVar_2& mojeSterowanie;
    std::shared_ptr<SterowanieMysza> dotychczasoweSterowanie;
};
#endif // STEROWANIEMODYFIKUJPUNKTY_H