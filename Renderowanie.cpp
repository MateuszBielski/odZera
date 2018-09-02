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
void Renderowanie::Renderuj( bool b, int i)
{
//    g_print("\nRenderowanie::Renderuj ile modeli %d",mojeModele.size());
    for(auto iter : mojeModele)iter->Rysuj();
}
int Renderowanie::PolaczZkimPotrzebujeNaPoczatek()
{
    Zaladuj(std::make_shared<Kostka>());
    Zaladuj(std::make_shared<Ostroslup>());
    
    WskazModelSwiatla(0);
    return 0;
}
void Renderowanie::Zaladuj(spModel wskaznikNaModel)
{
	//jakieś rzeczy, które mają ustawić cechy i parametry rysowanej rzeczy np. nazwy w openGL, może położenie w przestrzeni
	wskaznikNaModel->UstawMojeFunkcjeRysujace();
    mojeModele.push_back(wskaznikNaModel);
}
void Renderowanie::WskazModelSwiatla(short numerModelu){
	modelSwiatla = numerModelu;
	mojeModele.at(modelSwiatla)->UzywajPushMatrix(true);
}
void Renderowanie::UstawPolozenieSwiatla(float* zeWskaznika)
{
    mojeModele.at(modelSwiatla)->UstalPolozenie3f(zeWskaznika);
}
Renderowanie::spModel Renderowanie::DajModelSwiatla()
{
	return mojeModele.at(modelSwiatla);
}
