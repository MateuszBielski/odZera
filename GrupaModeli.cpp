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
    SrodekModeluZmodeliWylicz();
    return --mojeModele.end();//ostatni iterator, czyli dotyczący wstawionego obiektu
}
void GrupaModeli::TransformacjePrzedRysowaniem()
{
    glTranslatef(mojeWspolrzedneImacierzeSterowania->m_Pos[0],mojeWspolrzedneImacierzeSterowania->m_Pos[1],mojeWspolrzedneImacierzeSterowania->m_Pos[2]);
    glTranslatef(srodekModelu[0],srodekModelu[1],srodekModelu[2]);
    glMultMatrixf(&mojeWspolrzedneImacierzeSterowania->macierzObrotu[0][0]);
    glTranslatef(-srodekModelu[0],-srodekModelu[1],-srodekModelu[2]);
}
template<int flagi>
void GrupaModeli::GrupaRysujTemplate(){
    if(czyPushMatrix)glPushMatrix();
    TransformacjePrzedRysowaniem();
    (this->*FunkcjaWymienna)();
    if constexpr (flagi & Z_NAZWAMI_MODELI){
        glLoadName(jestemZaladowanyPodNumerem);
        glPushName(jestemZaladowanyPodNumerem);
    }
    if constexpr (flagi == 0) (this->*FunkcjaWymienna)();
    for(auto& model : mojeModele){
        if constexpr (flagi == 0)model->Rysuj();
        else if constexpr (flagi & Z_NAZWAMI_MODELI)model->RysujZnazwami();
    }
    if constexpr (flagi & Z_NAZWAMI_MODELI) glPopName();
    if(czyPushMatrix)glPopMatrix();
}
void GrupaModeli::Rysuj()
{
    GrupaRysujTemplate<0>();
}
void GrupaModeli::RysujZnazwami()
{
    GrupaRysujTemplate<Z_NAZWAMI_MODELI>();
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
void GrupaModeli::SrodekModeluZmodeliWylicz(){
    float ileModeli = 0;
    for(int j = 0; j < 3 ; j++)srodekModelu[j] = 0;
    for(auto& model : mojeModele){
        for(int j = 0; j < 3 ; j++)srodekModelu[j] += model->SrodekModelu()[j];
        ileModeli += 1.0;
    }
    for(int j = 0; j < 3 ; j++)srodekModelu[j] /= ileModeli;
}
void GrupaModeli::UtrwalPrzeksztalcenia()
{
    g_print("\nGrupaModeli::UtrwalPrzeksztalceniaModeliWgrupie");
	glLoadIdentity();
	this->WlaczJednorazowoWymienneFunkcje(UTRWAL_SRODEK);
    for(auto& model : mojeModele){
        model->WlaczJednorazowoWymienneFunkcje(UTRWAL_PUNKTY_NORMALNE_SRODEK);
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
spModel GrupaModeli::WydzielZeMnieKorzystajac(spModel model)
{
    std::shared_ptr<ModelPusty> pusty = std::static_pointer_cast<ModelPusty>(model);
    itLspModel iterator = (pusty->AdresPelnegoObiektu());
    spModel przwrocony =  *iterator;
    mojeModele.erase(iterator);
    return przwrocony;
}
int GrupaModeli::IleMamModeli()
{
	return mojeModele.size();
}
