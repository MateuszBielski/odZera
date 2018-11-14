#include "WidokCechModelu.h"

WidokCechModelu::WidokCechModelu(){
}
void WidokCechModelu::RysujDla(std::shared_ptr<Model> wsk){
    if(wsk.get() == this)return;
    if(wskazywany != nullptr){
        wskazywany->UtrwalPrzeksztalcenia();
    for(int i = 0 ; i < 3 ; i++){
            wskazywany->SrodekModelu()[i] += mojeWspolrzedneImacierzeSterowania->m_Pos[i];
            mojeWspolrzedneImacierzeSterowania->m_Pos[i] = 0;
        }
//        g_print("\nSrodek poprzedniego po zmianie %2.3f,  %2.3f,  %2.3f",wskazywany->SrodekModelu()[0],wskazywany->SrodekModelu()[1],wskazywany->SrodekModelu()[2]);    
    }
    wskazywany = wsk;
    zastepczaM_Pos = wskazywany->mojeWspolrzedneImacierzeSterowania->m_Pos;
    zastepczaSrodek = wskazywany->SrodekModelu();
    g_print("\nSrodek wybranego %2.3f,  %2.3f,  %2.3f",wskazywany->SrodekModelu()[0],wskazywany->SrodekModelu()[1],wskazywany->SrodekModelu()[2]);
}
void WidokCechModelu::RysujGeometrie(){
    
    znacznik.RysujGeometrieTemplate<0,GL_LINES>();
}
void WidokCechModelu::TransformacjePrzedRysowaniem()
{
    float s[3];
    for(int i = 0 ; i < 3 ; i++){
        s[i] = zastepczaM_Pos[i]+zastepczaSrodek[i]+mojeWspolrzedneImacierzeSterowania->m_Pos[i];//
    }
    glTranslatef(s[0],s[1],s[2]);
}

