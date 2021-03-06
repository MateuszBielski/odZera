#include "Renderowanie.h"
#include <random>


Renderowanie1::Renderowanie1(ZarzadzanieObiektami& zo):mojeModele(zo.MojeModeleRef())
                                                    ,numerModeluWybranego(zo.NumerModeluWybranegoRef())
                                                    ,modelSwiatlaMaNumer(zo.ModelSwiatlaMaNumer())
{
	nazwa = "renderowanie";
    Komunikat("Renderowanie");
}

Renderowanie1::~Renderowanie1()
{
    Komunikat("~Renderowanie");
}
void Renderowanie1::RysujModele()
{
    (this->*RysujModeleOdpowiednio)();
}
void Renderowanie1::UstawRysowanieZnazwami()
{
    RysujModeleOdpowiednio = &Renderowanie1::JednorazowoRysujModeleZnazwami;
}
void Renderowanie1::UstawRysowanieTylkoPunktowZnazwami(){
    RysujModeleOdpowiednio = &Renderowanie1::JednorazowoRysujTylkoPunktyZnazwami;
}
void Renderowanie1::UstawRysowanieZwidocznymiPunktami(bool tak)
{
    g_print("\nUstawRysowanieZwidocznymiPunktami %d",tak);
    RysujModeleOdpowiednio = tak ? (&Renderowanie1::RysujZwidocznymiPunktami) : (&Renderowanie1::RysujModeleBezNazw);
}

void Renderowanie1::RysujModeleBezNazw()
{
    for(auto iter : mojeModele)iter->Rysuj(0);//Rysuj()
}
void Renderowanie1::RysujZwidocznymiPunktami()
{
    for(auto iter : mojeModele)iter->Rysuj(Z_WIDOCZNYMI_PUNKTAMI);//Z_WIDOCZNYMI_PUNKTAMI TYLKO_PUNKTY_Z_NAZWAMI
}
void Renderowanie1::JednorazowoRysujModeleZnazwami()
{
    glPushName(891);//liczba dowolna, bo jest podmieniana przez funkcję glLoadName
//    g_print("\n glPushName%d",891);
    for(auto iter : mojeModele){
        iter->Rysuj(Z_NAZWAMI_MODELI);//
    }
    RysujModeleOdpowiednio = &Renderowanie1::RysujModeleBezNazw;
}
void Renderowanie1::JednorazowoRysujTylkoPunktyZnazwami()
{
    glPushName(23);
    for(auto iter : mojeModele){
        iter->Rysuj(TYLKO_PUNKTY_Z_NAZWAMI);//RysujPunktyZnazwami();
    }
    glPopName();
    RysujModeleOdpowiednio = &Renderowanie1::RysujZwidocznymiPunktami;
}
int Renderowanie1::PolaczZkimPotrzebujeNaPoczatek()
{
//    zarzadzanie = Ref_WyszukajWModulach<ZarzadzanieObiektami>("zarzadznieObiektami");
    return 0;
}

void Renderowanie1::UstawPolozenieSwiatla(float* zeWskaznika)
{
    mojeModele.at(modelSwiatlaMaNumer)->UstalM_Pos(zeWskaznika);
}
void Renderowanie1::UtrwalPrzeksztalceniaWybranegoObiektu()
{
	g_print("\nRenderowanie1::UtrwalPrzeksztalceniaWybranegoObiektu");
	glLoadIdentity();
    
    mojeModele.at(numerModeluWybranego)->Rysuj(0);//Rysuj()
}
void Renderowanie1::UtrwalPunktyWybranegoObiektu(){
    g_print("\nRenderowanie1::UtrwalPunktyWybranegoObiektu");
	glLoadIdentity();
    auto wybrany = mojeModele.at(numerModeluWybranego);
    wybrany->WlaczJednorazowoWymienneFunkcje(UTRWAL_PUNKTY_NORMALNE_SRODEK);
	//rysowanie wszystkich obiektów
	wybrany->Rysuj(0);//Rysuj()
    wybrany->mojeWspolrzedneImacierzeSterowania->UstawWartosciStartowe();
}
void Renderowanie1::UtrwalPrzeksztalceniaModelu(spModel model){
    g_print("\nRenderowanie1::UtrwalPrzeksztalceniaModelu");
	glLoadIdentity();
    model->Rysuj(0);//Rysuj()
}

void Renderowanie1::TransformacjaCalegoWidoku()
{
    if(przesunieciePierwotne == nullptr || przesuniecie == nullptr){
        g_print("\n nie ustawione wskaźniki na przemieszcznia i obroty całego widoku");
        return;
    }
    glTranslatef(przesunieciePierwotne[0],przesunieciePierwotne[1],przesunieciePierwotne[2]);
    glMultMatrixf(macierzObrotu);
	glTranslatef(przesuniecie[0], przesuniecie[1], przesuniecie[2]);
}
void Renderowanie1::PobierzWskaznikNaWektorPrzesunieciaPierwotnego(float* adres)
{
	przesunieciePierwotne = adres;
}
void Renderowanie1::PobierzWskaznikNaWektorPrzesuniecia(float* adres)
{
	przesuniecie = adres;
}

void Renderowanie1::PobierzWskaznikNaMacierzObrotu(float* adres)
{
	macierzObrotu = adres;
}


