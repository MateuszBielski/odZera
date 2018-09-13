#include "Renderowanie.h"

Renderowanie::Renderowanie()
{
	nazwa = "renderowanie";
    Komunikat("Renderowanie");
}

Renderowanie::~Renderowanie()
{
    Komunikat("~Renderowanie");
}
void Renderowanie::RysujModele()
{
    (this->*RysujModeleOdpowiednio)();
}
void Renderowanie::UstawRysowanieZnazwami()
{
    RysujModeleOdpowiednio = &Renderowanie::JednorazowoRysujModeleZnazwami;
}

void Renderowanie::RysujModeleBezNazw()
{
    for(auto iter : mojeModele)iter->Rysuj();
}

void Renderowanie::JednorazowoRysujModeleZnazwami()
{
    int numeracja = 0;
    glPushName(321);
    glPushName(429);
    glPushName(557);//ta nazwa jest podmieniana przez funkcję glLoadName
//    g_print("\n narysowano modele z nazwami: ");
    for(auto iter : mojeModele){
        glLoadName(numeracja++);
        iter->Rysuj();
//        g_print("  %d ",numeracja-1);
    }
    glPopName();   
    RysujModeleOdpowiednio = &Renderowanie::RysujModeleBezNazw;
//    g_print("\n przywrócono RysujModeleBezNazw");
}

int Renderowanie::PolaczZkimPotrzebujeNaPoczatek()
{
    Zaladuj(std::make_shared<Kostka>());
	Zaladuj(std::make_shared<Kostka>());
    Zaladuj(std::make_shared<Ostroslup>());
    
    WskazModelSwiatla(0);
	WybierzModelOnumerze(2);
    return 0;
}
void Renderowanie::Zaladuj(spModel wskaznikNaModel)
{
	//jakieś rzeczy, które mają ustawić cechy i parametry rysowanej rzeczy np. nazwy w openGL, może położenie w przestrzeni
    mojeModele.push_back(wskaznikNaModel);
    wskaznikNaModel->JestemZaladowanyPodNumerem(ileZaladowanychModeli++);
}
void Renderowanie::WskazModelSwiatla(short numerModelu){
	modelSwiatlaMaNumer = numerModelu;
	mojeModele.at(modelSwiatlaMaNumer)->UzywajPushMatrix(true);
}
void Renderowanie::UstawPolozenieSwiatla(float* zeWskaznika)
{
    mojeModele.at(modelSwiatlaMaNumer)->UstalPolozenie3f(zeWskaznika);
}
Renderowanie::spModel Renderowanie::DajModelSwiatla()
{
	return mojeModele.at(modelSwiatlaMaNumer);
}
void Renderowanie::WybierzModelOnumerze(short tym){
	if(tym < 0)return;
	auto poprzednioWybranyModel = mojeModele.at(numerModeluWybranego);
	numerModeluWybranego = tym;
    auto wybranyModel = mojeModele.at(numerModeluWybranego);
	poprzednioWybranyModel->OddajWskaznikiNaTransformacjeIswojeWyzeruj(wybranyModel);
	wybranyModel->UzywajPushMatrix(true);
    wybranyModel->PokazujWartosci(false);
}

Renderowanie::spModel Renderowanie::DajWybranyModel()
{
	return mojeModele.at(numerModeluWybranego);
}
void Renderowanie::TransformacjaCalegoWidoku()
{
    if(przesunieciePierwotne == nullptr || przesuniecie == nullptr || przesuniecie == nullptr){
        g_print("\n nie ustawione wskaźniki na przemieszcznia i obroty całego widoku");
        return;
    }
    glTranslatef(przesunieciePierwotne[0],przesunieciePierwotne[1],przesunieciePierwotne[2]);
    glMultMatrixf(macierzObrotu);
	glTranslatef(przesuniecie[0], przesuniecie[1], przesuniecie[2]);
}
void Renderowanie::PobierzWskaznikNaWektorPrzesunieciaPierwotnego(float* adres)
{
	przesunieciePierwotne = adres;
}
void Renderowanie::PobierzWskaznikNaWektorPrzesuniecia(float* adres)
{
	przesuniecie = adres;
}

void Renderowanie::PobierzWskaznikNaMacierzObrotu(float* adres)
{
	macierzObrotu = adres;
}

