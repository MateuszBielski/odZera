#include <random>
#include "ZarzadzanieObiektami.h"
#include "Kostka.h"
#include "StareRysowanie.h"



ZarzadzanieObiektami::ZarzadzanieObiektami()
{
	nazwa = "zarzadznieObiektami";
    Komunikat("zarzadznieObiektami");
}

ZarzadzanieObiektami::~ZarzadzanieObiektami()
{
    Komunikat("~zarzadznieObiektami");
}
int ZarzadzanieObiektami::PolaczZkimPotrzebujeNaPoczatek()
{
    g_print("\nZarzadzanieObiektami::PolaczZkimPotrzebujeNaPoczatek");
    //    Zaladuj(std::make_shared<Kostka>());
	Zaladuj(std::make_shared<Kostka>());
    Zaladuj(std::make_shared<Czworoscian>());
    Zaladuj(std::make_shared<Ostroslup>());
//    Zaladuj(std::make_shared<TrzyKwadraty>());
    UtworzTyleKostek(10);
    UtworzTyleModeli<Czworoscian>(5);
	
    linieNormalnych = std::make_shared<LinieZnormalnych>();
    cechyWybranego = std::make_shared<WidokCechModelu>();
    Zaladuj(linieNormalnych);
    Zaladuj(cechyWybranego);
    WskazModelSwiatla(0);
	WybierzModelOnumerze(5);
    return 0;
}
int ZarzadzanieObiektami::Zaladuj(spModel wskaznikNaModel)
{
	//jakieś rzeczy, które mają ustawić cechy i parametry rysowanej rzeczy np. nazwy w openGL, może położenie w przestrzeni
    mojeModele.push_back(wskaznikNaModel);
    wskaznikNaModel->PrzydzielenieNumeru(ileZaladowanychModeli++);
    return ileZaladowanychModeli-1;
}
void ZarzadzanieObiektami::WskazModelSwiatla(short numerModelu){
	modelSwiatlaMaNumer = numerModelu;
	mojeModele.at(modelSwiatlaMaNumer)->UzywajPushMatrix(true);
}

spModel ZarzadzanieObiektami::DajModelSwiatla()
{
	return mojeModele.at(modelSwiatlaMaNumer);
}
void ZarzadzanieObiektami::WybierzModelOnumerze(short tym){
	if(tym < 0 || tym > ileZaladowanychModeli)return;
    numerPoprzednioWybranego = numerModeluWybranego;
	numerModeluWybranego = tym;
    g_print("\nZarzadzanieObiektami::WybierzModelOnumerze %d",numerModeluWybranego);
    auto wybranyModel = mojeModele.at(numerModeluWybranego);
    wybranyModel->UzywajPushMatrix(true);
    wybranyModel->PokazujWartosci(false);
    linieNormalnych->RysujDla(wybranyModel);
    cechyWybranego->RysujDla(wybranyModel);//tu następuje też utrwalenie poprzednio wskazywanego modelu
    
    float * n = wybranyModel->normalne;
}
void ZarzadzanieObiektami::WybierzModelOnumerze(std::stack<int> & stosNazw){
    WybierzModelOnumerze(static_cast<short int>(stosNazw.top()));
}
void ZarzadzanieObiektami::WyodrebnijZgrupy(std::stack<int> & stosNazw){
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

spModel ZarzadzanieObiektami::DajWybranyModel()
{
	try{
        return mojeModele.at(numerModeluWybranego);
    }catch(std::exception& e){
        if(!mojeModele.size())g_print("\nnie ma załadowanych modeli");
        g_print("\nBrak Wybranego Modelu ");
        return nullptr;
    }
}
/*void ZarzadzanieObiektami::EdycjaPunktuOnumerze(std::stack<int> & stosNazw,int sposobEdycji)
{
    if(stosNazw.top() == -1)return;
    unsigned nrPunktu = stosNazw.top();
    float * adrPunktu = (float *)nrPunktu;
    g_print("\nWskazDoEdycjiPunktOnumerze %d jego współrz: %2.3f %2.3f %2.3f"
    ,nrPunktu,adrPunktu[0],adrPunktu[1],adrPunktu[2]);
    switch(sposobEdycji){
        case WSKAZ_NOWY:
        modyfikacjaPunktow.WstawDoWyczyszczonegoJedenPunkt(adrPunktu);
        break;
        case DODAJ_KOLEJNY:
        modyfikacjaPunktow.DodajPunkt(adrPunktu);
        break;
        case USUN_Z_EDYTOWANYCH:
        modyfikacjaPunktow.UsunPunkt(adrPunktu);
        break;
    }
}*/
void ZarzadzanieObiektami::UtworzTyleKostek(int ile)
{
    UtworzTyleModeli<Kostka>(ile);
}
template<class T>
void ZarzadzanieObiektami::UtworzTyleModeli(int ile)
{
    int i = 0;
    float losowo[3],losowoKolor[3];
    float przedzial[2];
    przedzial[0] = -5;
    przedzial[1] = 5;
    
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(przedzial[0],przedzial[1]);
    std::uniform_real_distribution<float> distKolor(0.0f,1.0f);
//        std::cout << dist(mt) << "\n";
    for(i ; i < ile ; i++){
        for(int j = 0; j < 3 ; j++){
            losowo[j] = dist(mt);
            losowoKolor[j] = distKolor(mt);
        }
//        std::shared_ptr<Model> kostka = std::make_shared<Kostka>(losowo);
        Zaladuj(std::make_shared<T>(losowo,losowoKolor));
    }
}
spGrupaModeli ZarzadzanieObiektami::PrzydzielPustaGrupe()
{
	if(pusteGrupy.empty())return std::make_shared<GrupaModeli>();
    else{
        auto doZwrotu = pusteGrupy.top();
        pusteGrupy.pop();
        return doZwrotu;
    }
}
void ZarzadzanieObiektami::WybranyModelPrzeniesDoGrupy()
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
    g_print("\nZarzadzanieObiektami::WybranyModelPrzeniesDoGrupy przeniesiono %d",numerModeluWybranego);
    numerModeluWybranego = numerPoprzednioWybranego;
}


