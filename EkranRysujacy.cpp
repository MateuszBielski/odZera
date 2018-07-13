#include "EkranRysujacy.h"

EkranRysujacy::EkranRysujacy()
{
	Komunikat("konstruktor EkranRysujacy");
}

EkranRysujacy::~EkranRysujacy()
{
}
void EkranRysujacy::UstawienieSceny()
{
	Komunikat("EkranRysujacy::UstawienieSceny");
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
void EkranRysujacy::RysujScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	sTransformacja.emit(true,21);
	sRysuj.emit(true, 14);
}
void EkranRysujacy::Oswietlenie()
{
    glEnable(GL_LIGHTING);
    
    //kolormateriału (glColor uwzględniany)
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    //światło punktowe
    float kolorZrodla[] = {0.8,0.8,0.8,1.0};
    float pozycjaZrodla[] = {0.0,1.0,5.0,0.0};
    glLightfv(GL_LIGHT1,GL_POSITION,pozycjaZrodla); 
    glLightfv(GL_LIGHT1,GL_DIFFUSE,kolorZrodla);
    
    glEnable(GL_LIGHT1);
}