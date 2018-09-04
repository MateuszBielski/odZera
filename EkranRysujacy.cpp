#include "EkranRysujacy.h"
#include "FunkcjeIstruktury.h"
EkranRysujacy::EkranRysujacy()
{
	Komunikat("EkranRysujacy");

}

EkranRysujacy::~EkranRysujacy()
{
	Komunikat("~EkranRysujacy");
}
void EkranRysujacy::UstawienieSceny()
{
//	Komunikat("EkranRysujacy::UstawienieSceny");
	int w,h;
	w = get_width();
	h = get_height();
	glViewport(0, 0, w, h);
    glShadeModel(GL_SMOOTH);//cieniowanie kolorem GK_SMOOTH, GL_FLAT
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_BLEND);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (w > h) {
      float aspect = static_cast<float>(w) / static_cast<float>(h);
      glFrustum(-aspect, aspect, -1.0, 1.0, 5.0, 60.0);
    } else {
      float aspect = static_cast<float>(h) / static_cast<float>(w);
      glFrustum(-1.0, 1.0, -aspect, aspect, 5.0, 60.0);
    }

    glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void EkranRysujacy::OswietlenieUstaw()
{
    glEnable(GL_LIGHTING);
    
    //kolormateriału (glColor uwzględniany)
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    //światło punktowe
    float kolorZrodla[] = {0.8,0.8,0.8,1.0};
    float temp[] = {0.0,1.0,3.0,0.0};
    memcpy(pozycjaZrodlaSwiatla,temp,4*sizeof(float));
    glLightfv(GL_LIGHT1,GL_POSITION,pozycjaZrodlaSwiatla); 
    glLightfv(GL_LIGHT1,GL_DIFFUSE,kolorZrodla);
    glEnable(GL_LIGHT1);
}
void EkranRysujacy::RysujScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	
    renderowanie->TransformacjaCalegoWidoku(); 
	glLightfv(GL_LIGHT1,GL_POSITION,pozycjaZrodlaSwiatla);
    renderowanie->RysujModele();
    
    /*float macierzModelWidok[16];
    glGetFloatv(GL_MODELVIEW_MATRIX,macierzModelWidok);
    WyswietlWartosciMacierzy4x4(macierzModelWidok);
    float punkt3D[3];
    TransformujPikselDoPrzestrzeniSceny(300,300,punkt3D);*/
}

void EkranRysujacy::PodajPozycjeZrodlaSwiatla(float * tutaj){
    memcpy(tutaj,pozycjaZrodlaSwiatla,4*sizeof(float));
}
void EkranRysujacy::UstawPozycjeZrodlaSwiatla(float * wedlugParametrow){
    memcpy(pozycjaZrodlaSwiatla,wedlugParametrow,4*sizeof(float));
   
    sPolozenieSwiatla.emit(wedlugParametrow);//odbiera renderowanie dla modelu symbolizującego światło .
}
