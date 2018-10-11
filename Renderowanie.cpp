#include "Renderowanie.h"
#include <GrupaModeli.h>
#include <random>

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
    glPushName(557);//ta nazwa jest podmieniana przez funkcję glLoadName
    for(auto iter : mojeModele){
        glLoadName(numeracja++);
        iter->Rysuj();
    }
    glPopName();   
    RysujModeleOdpowiednio = &Renderowanie::RysujModeleBezNazw;
}

int Renderowanie::PolaczZkimPotrzebujeNaPoczatek()
{
    Zaladuj(std::make_shared<Kostka>());
//	Zaladuj(std::make_shared<Kostka>());
    Zaladuj(std::make_shared<Ostroslup>());
//    Zaladuj(std::make_shared<TrzyKwadraty>());
    UtworzTyleKostek(30);
	Zaladuj(std::make_shared<GrupaModeli>());
    WskazModelSwiatla(0);
	WybierzModelOnumerze(1);
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
    mojeModele.at(modelSwiatlaMaNumer)->UstalM_Pos(zeWskaznika);
}
Renderowanie::spModel Renderowanie::DajModelSwiatla()
{
	return mojeModele.at(modelSwiatlaMaNumer);
}
void Renderowanie::WybierzModelOnumerze(short tym){
	if(tym < 0)return;
	numerModeluWybranego = tym;
    auto wybranyModel = mojeModele.at(numerModeluWybranego);
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
void Renderowanie::UtworzTyleKostek(int ile)
{
    int i = 0;
    float losowo[3];
    float przedzial[2];
    przedzial[0] = -5;
    przedzial[1] = 5;
    
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(przedzial[0],przedzial[1]);

//        std::cout << dist(mt) << "\n";
    for(i ; i < ile ; i++){
        for(int j = 0; j < 3 ; j++)losowo[j] = dist(mt);
        std::shared_ptr<Model> kostka = std::make_shared<Kostka>();
        kostka->UstalM_Pos(losowo);
        Zaladuj(kostka);
    }
}
void Renderowanie::WybranyModelPrzeniesDoGrupy()
{
    auto wybranyModel = mojeModele.at(numerModeluWybranego);
    mojeModele.at(numerModeluWybranego) = std::make_shared<ModelPusty>();
}
