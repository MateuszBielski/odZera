#include "GrupaModeli.h"

GrupaModeli::GrupaModeli()
{
    czyJestemGrupa = true;
    for(int i= 0 ;i < 3; i++){
        srodekCiezkosci[i] = 0;
    }
}

GrupaModeli::~GrupaModeli()
{
}
itLspModel GrupaModeli::DodajDoMnie(spModel model)
{
	mojeModele.push_back(model);
    WyliczSrodekCiezkosci();
    return mojeModele.rbegin();//ostatni iterator, czyli dotyczący wstawionego obiektu
}
void GrupaModeli::TransformacjePrzedRysowaniem()
{
    glTranslatef(mojeWspolrzedneImacierzeSterowania->m_Pos[0],mojeWspolrzedneImacierzeSterowania->m_Pos[1],mojeWspolrzedneImacierzeSterowania->m_Pos[2]);
    glTranslatef(srodekCiezkosci[0],srodekCiezkosci[1],srodekCiezkosci[2]);
    glMultMatrixf(&mojeWspolrzedneImacierzeSterowania->macierzObrotu[0][0]);
    glTranslatef(-srodekCiezkosci[0],-srodekCiezkosci[1],-srodekCiezkosci[2]);
}
void GrupaModeli::Rysuj()
{
    if(czyPushMatrix)glPushMatrix();
    TransformacjePrzedRysowaniem();
	(this->*FunkcjaWymienna)();
   for(auto& model : mojeModele){
        model->Rysuj();
    }
    if(czyPushMatrix)glPopMatrix();
}
void GrupaModeli::RysujZnazwami()
{
    if(czyPushMatrix)glPushMatrix();
    TransformacjePrzedRysowaniem();
    glLoadName(jestemZaladowanyPodNumerem);
    glPushName(jestemZaladowanyPodNumerem);
//    g_print("\nGrupaModeli::RysujZnazwami glPushName %d",jestemZaladowanyPodNumerem);
    for(auto& model : mojeModele){
        model->RysujZnazwami();
    }
    glPopName();
    if(czyPushMatrix)glPopMatrix();
}
void GrupaModeli::WyliczSrodekCiezkosci()
{   
    float ileModeli = 0;
    for(int j = 0; j < 3 ; j++)srodekCiezkosci[j] = 0;
    for(auto& model : mojeModele){
        for(int j = 0; j < 3 ; j++)srodekCiezkosci[j] += model->SrodekModelu()[j];
        ileModeli += 1.0;
    }
    for(int j = 0; j < 3 ; j++)srodekCiezkosci[j] /= ileModeli;
//    g_print("\nsrodekCiezkosci: %2.2f, %2.2f, %2.2f",srodekCiezkosci[0],srodekCiezkosci[1],srodekCiezkosci[2]);
}
void GrupaModeli::UtrwalPrzeksztalceniaMoichModeli()
{
    g_print("\nGrupaModeli::UtrwalPrzeksztalceniaModeliWgrupie");
	glLoadIdentity();
//	this->WlaczJednorazowoWymienneFunkcje(UTRWAL_MPOS_Z_AKTUALNEJ_MACIERZY);
    for(auto& model : mojeModele){
        model->WlaczJednorazowoWymienneFunkcje(PRZELICZ_PUNKTY);
    }
    Rysuj();
    for(auto& model : mojeModele){
        model->mojeWspolrzedneImacierzeSterowania->UstawWartosciStartowe();
    }
    this->mojeWspolrzedneImacierzeSterowania->UstawWartosciStartowe();
}
void GrupaModeli::WlaczJednorazowoWymienneFunkcje(int jakieFunkcjeFlagi)
{
	for(auto& model : mojeModele){
        model->WlaczJednorazowoWymienneFunkcje(jakieFunkcjeFlagi);
    }
}
