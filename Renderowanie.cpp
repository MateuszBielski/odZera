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
//    g_print("\nRenderowanie::Renderuj ile modeli %d",mojeModele.size());
    for(auto iter : mojeModele)iter->Rysuj();
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
	numerModeluWybranego = tym;
    auto wybranyModel = mojeModele.at(numerModeluWybranego);
	wybranyModel->UzywajPushMatrix(true);
//    wybranyModel->PokazujWartosci(true);
}

Renderowanie::spModel Renderowanie::DajWybranyModel()
{
	return mojeModele.at(numerModeluWybranego);
}
void Renderowanie::TransformacjaCalegoWidoku()
{
    glMultMatrixf(macierzObrotu);//lub &macierzObrotu[0]
	glTranslatef(przesunieciePoczatkowe[0], przesunieciePoczatkowe[1], przesunieciePoczatkowe[2]);
}
void Renderowanie::PobierzWskaznikNaWektorPrzesuniecia(float* adres)
{
	przesunieciePoczatkowe = adres;
}

void Renderowanie::PobierzWskaznikNaMacierzObrotu(float* adres)
{
	macierzObrotu = adres;
}
