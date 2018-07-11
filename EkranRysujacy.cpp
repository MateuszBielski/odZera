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
	Komunikat("EkranRysujacy::RysujScene przed sRysuj.emit()");
    m_signal_something.emit(false, 12);
//	sRysuj.emit(12,true);
}
