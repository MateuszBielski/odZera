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
    glPushName(891);//liczba dowolna, bo jest podmieniana przez funkcję glLoadName
//    g_print("\n glPushName%d",891);
    for(auto iter : mojeModele){
        iter->RysujZnazwami();
    }
    RysujModeleOdpowiednio = &Renderowanie::RysujModeleBezNazw;
}

int Renderowanie::PolaczZkimPotrzebujeNaPoczatek()
{
    Zaladuj(std::make_shared<Kostka>());
//	Zaladuj(std::make_shared<Kostka>());
    Zaladuj(std::make_shared<Ostroslup>());
//    Zaladuj(std::make_shared<TrzyKwadraty>());
    UtworzTyleKostek(7);
	
    WskazModelSwiatla(0);
	WybierzModelOnumerze(1);
    return 0;
}
int Renderowanie::Zaladuj(spModel wskaznikNaModel)
{
	//jakieś rzeczy, które mają ustawić cechy i parametry rysowanej rzeczy np. nazwy w openGL, może położenie w przestrzeni
    mojeModele.push_back(wskaznikNaModel);
    wskaznikNaModel->PrzydzielenieNumeru(ileZaladowanychModeli++);
    return ileZaladowanychModeli-1;
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
	if(tym < 0 || tym > ileZaladowanychModeli)return;
    numerPoprzednioWybranego = numerModeluWybranego;
	numerModeluWybranego = tym;
//    g_print("\nRenderowanie::WybierzModelOnumerze %d",numerModeluWybranego);
    auto wybranyModel = mojeModele.at(numerModeluWybranego);
    wybranyModel->UzywajPushMatrix(true);
    wybranyModel->PokazujWartosci(false);
    wybranyModel->WlaczJednorazowoWymienneFunkcje(UTRWAL_MPOS_Z_AKTUALNEJ_MACIERZY);
	UtrwalPrzeksztalceniaWybranegoObiektu();
//	wybranyModel->WlaczJednorazowoWymienneFunkcje(ZESTAW_FUNKCJI);
}
void Renderowanie::WybierzModelOnumerze(std::stack<int> && stosNazw){
    WybierzModelOnumerze(static_cast<short int>(stosNazw.top()));
    //rozpoznać grrupę do której należy obiekt
}
void Renderowanie::UtrwalPrzeksztalceniaWybranegoObiektu()
{
	g_print("\nRenderowanie::UtrwalPrzeksztalceniaWybranegoObiektu");
	glLoadIdentity();
	mojeModele.at(numerModeluWybranego)->Rysuj();
}
Renderowanie::spModel Renderowanie::DajWybranyModel()
{
	return mojeModele.at(numerModeluWybranego);
}
void Renderowanie::TransformacjaCalegoWidoku()
{
    if(przesunieciePierwotne == nullptr || przesuniecie == nullptr){
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
    g_print("\nRenderowanie::WybranyModelPrzeniesDoGrupy poprzedni %d, terazWybrany %d",numerPoprzednioWybranego,numerModeluWybranego);
    auto wybranyModel = mojeModele.at(numerModeluWybranego);
    auto poprzednioWybrany = mojeModele.at(numerPoprzednioWybranego);
    mojeModele.at(numerModeluWybranego) = std::make_shared<ModelPusty>();
    std::shared_ptr<GrupaModeli> grupa;
    if(!poprzednioWybrany->czyJestemGrupa){
        grupa= std::make_shared<GrupaModeli>();
        grupa->DodajDoMnie(poprzednioWybrany);
        mojeModele.at(numerPoprzednioWybranego) = std::make_shared<ModelPusty>();
        numerPoprzednioWybranego = Zaladuj(std::static_pointer_cast<Model>(grupa));
//        g_print("\nnowaGrupa z numerem %d",numerPoprzednioWybranego);
        
    }else{
        grupa = std::static_pointer_cast<GrupaModeli>(poprzednioWybrany);
//        g_print("\ndodano do istniejącej grupy %d",numerPoprzednioWybranego);
    }
    grupa->DodajDoMnie(wybranyModel);
    numerModeluWybranego = numerPoprzednioWybranego;
}

