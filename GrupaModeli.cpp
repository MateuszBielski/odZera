#include "GrupaModeli.h"

GrupaModeli::GrupaModeli()
{
    czyJestemGrupa = true;
}

GrupaModeli::~GrupaModeli()
{
}
void GrupaModeli::DodajDoMnie(spModel model)
{
	mojeModele.push_back(model);
}
void GrupaModeli::Rysuj()
{
    for(auto& model : mojeModele){
        model->Rysuj();
    }
}
void GrupaModeli::RysujZnazwami()
{
    glPushName(jestemZaladowanyPodNumerem);
    for(auto& model : mojeModele){
        model->RysujZnazwami();
    }
    glPopName();
}

