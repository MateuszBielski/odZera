#include "Renderowanie.h"
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
//    Zaladuj(std::make_shared<Kostka>());
//	Zaladuj(std::make_shared<Kostka>());
    Zaladuj(std::make_shared<Czworoscian>());
    Zaladuj(std::make_shared<Ostroslup>());
//    Zaladuj(std::make_shared<TrzyKwadraty>());
    UtworzTyleKostek(10);
	
    linieNormalnych = std::make_shared<LinieZnormalnych>();
    cechyWybranego = std::make_shared<WidokCechModelu>();
    Zaladuj(linieNormalnych);
    Zaladuj(cechyWybranego);
    WskazModelSwiatla(0);
	WybierzModelOnumerze(5);
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
    g_print("\nRenderowanie::WybierzModelOnumerze %d",numerModeluWybranego);
    auto wybranyModel = mojeModele.at(numerModeluWybranego);
    wybranyModel->UzywajPushMatrix(true);
    wybranyModel->PokazujWartosci(false);
    linieNormalnych->RysujDla(wybranyModel);
    cechyWybranego->RysujDla(wybranyModel);
    
//	wybranyModel->WlaczJednorazowoWymienneFunkcje(ZESTAW_FUNKCJI);
}
void Renderowanie::WybierzModelOnumerze(std::stack<int> & stosNazw){
    WybierzModelOnumerze(static_cast<short int>(stosNazw.top()));
    //rozpoznać grrupę do której należy obiekt
}
void Renderowanie::WyodrebnijZgrupy(std::stack<int> & stosNazw){
//    g_print("\nWyodrebnijZgrupy na stosie jest %d",stosNazw.top());
    auto nrGrupy = stosNazw.top();
    stosNazw.pop();
    if(stosNazw.empty())return;
    auto wybranaGrupa = std::static_pointer_cast<GrupaModeli>(mojeModele.at(nrGrupy));
    auto nrObiektuWydzielanego = stosNazw.top();
    auto& doPrzywrocenia = mojeModele.at(static_cast<short int>(nrObiektuWydzielanego));
//    g_print("\nWyodrebnijZgrupy przed WydzielZeMnieKorzystajac");
    wybranaGrupa->UtrwalPrzeksztalcenia();
    doPrzywrocenia = wybranaGrupa->WydzielZeMnieKorzystajac(doPrzywrocenia);
    WybierzModelOnumerze(nrObiektuWydzielanego);
    if(!wybranaGrupa->IleMamModeli())pusteGrupy.push(wybranaGrupa);
}
void Renderowanie::UtrwalPrzeksztalceniaWybranegoObiektu()
{
	g_print("\nRenderowanie::UtrwalPrzeksztalceniaWybranegoObiektu");
	glLoadIdentity();
    
    mojeModele.at(numerModeluWybranego)->Rysuj();
}
void Renderowanie::UtrwalPunktyWybranegoObiektu(){
    g_print("\nRenderowanie::UtrwalPunktyWybranegoObiektu");
	glLoadIdentity();
    auto wybrany = mojeModele.at(numerModeluWybranego);
    wybrany->WlaczJednorazowoWymienneFunkcje(PRZELICZ_PUNKTY);
	//rysowanie wszystkich obiektów
	wybrany->Rysuj();
    wybrany->mojeWspolrzedneImacierzeSterowania->UstawWartosciStartowe();
}
void Renderowanie::UtrwalPrzeksztalceniaModelu(spModel model){
    g_print("\nRenderowanie::UtrwalPrzeksztalceniaModelu");
	glLoadIdentity();
    model->Rysuj();
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
        std::shared_ptr<Model> kostka = std::make_shared<Kostka>(losowo);
        Zaladuj(kostka);
    }
}
spGrupaModeli Renderowanie::PrzydzielPustaGrupe()
{
	if(pusteGrupy.empty())return std::make_shared<GrupaModeli>();
    else{
        auto doZwrotu = pusteGrupy.top();
        pusteGrupy.pop();
        return doZwrotu;
    }
}
void Renderowanie::WybranyModelPrzeniesDoGrupy()
{
    auto poprzednioWybrany = mojeModele.at(numerPoprzednioWybranego);
    std::shared_ptr<GrupaModeli> grupa;
    if(!poprzednioWybrany->czyJestemGrupa){
        grupa = PrzydzielPustaGrupe();
        auto dokadMnieWstawiono = grupa->DodajDoMnie(poprzednioWybrany);
        mojeModele.at(numerPoprzednioWybranego) = std::make_shared<ModelPusty>(dokadMnieWstawiono);
        numerPoprzednioWybranego = Zaladuj(std::static_pointer_cast<Model>(grupa));
//        g_print("\nnowaGrupa z numerem %d",numerPoprzednioWybranego);
        
    }else{
        grupa = std::static_pointer_cast<GrupaModeli>(poprzednioWybrany);
//        g_print("\ndodano do istniejącej grupy %d",numerPoprzednioWybranego);
    }
	grupa->UtrwalPrzeksztalcenia();
    
    auto wybranyModel = mojeModele.at(numerModeluWybranego);
    auto dokadMnieWstawiono = grupa->DodajDoMnie(wybranyModel);
    mojeModele.at(numerModeluWybranego) = std::make_shared<ModelPusty>(dokadMnieWstawiono);
    g_print("\nRenderowanie::WybranyModelPrzeniesDoGrupy przeniesiono %d",numerModeluWybranego);
    numerModeluWybranego = numerPoprzednioWybranego;
}


