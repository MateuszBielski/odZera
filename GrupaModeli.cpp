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
    
    //tu można modyfikować środek ciężkości dla obracania grupy
}
void GrupaModeli::Rysuj()
{
    if(czyPushMatrix)glPushMatrix();
    glTranslatef(mojeWspolrzedneImacierzeSterowania->m_Pos[0],mojeWspolrzedneImacierzeSterowania->m_Pos[1],mojeWspolrzedneImacierzeSterowania->m_Pos[2]);
    glMultMatrixf(&mojeWspolrzedneImacierzeSterowania->macierzObrotu[0][0]);
    for(auto& model : mojeModele){
        model->Rysuj();
    }
    if(czyPushMatrix)glPopMatrix();
}
void GrupaModeli::RysujZnazwami()
{
    if(czyPushMatrix)glPushMatrix();
    glTranslatef(mojeWspolrzedneImacierzeSterowania->m_Pos[0],mojeWspolrzedneImacierzeSterowania->m_Pos[1],mojeWspolrzedneImacierzeSterowania->m_Pos[2]);
    glMultMatrixf(&mojeWspolrzedneImacierzeSterowania->macierzObrotu[0][0]);
    glLoadName(jestemZaladowanyPodNumerem);
    glPushName(jestemZaladowanyPodNumerem);
    g_print("\nGrupaModeli::RysujZnazwami glPushName %d",jestemZaladowanyPodNumerem);
    for(auto& model : mojeModele){
        model->RysujZnazwami();
    }
    glPopName();
    if(czyPushMatrix)glPopMatrix();
}

