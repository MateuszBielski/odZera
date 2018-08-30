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
    Zaladuj(std::make_shared<Ostroslup>());
    return 0;
}
void Renderowanie::Zaladuj(spModel wskaznikNaModel)
{
	//jakieś rzeczy, które mają ustawić cechy i parametry rysowanej rzeczy np. nazwy w openGL, może położenie w przestrzeni
    mojeModele.push_back(wskaznikNaModel);
}
