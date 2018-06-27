#include "EkranGL.h"

EkranGL::EkranGL()
{
}

EkranGL::~EkranGL()
{
    Komunikat("destruktor EkranGL");
}
bool EkranGL::KonfiguracjaGL()
{
    glconfig = Gdk::GL::Config::create(Gdk::GL::MODE_RGB|Gdk::GL::MODE_DEPTH|Gdk::GL::MODE_DOUBLE);
    if (!glconfig) {
      std::cerr << "*** Cannot find the double-buffered visual.\n"
                << "*** Trying single-buffered visual.\n";

      // Try single-buffered visual
      glconfig = Gdk::GL::Config::create(Gdk::GL::MODE_RGB   |
                                         Gdk::GL::MODE_DEPTH);
        return true;
      if (!glconfig) {
        std::cerr << "*** Cannot find any OpenGL-capable visual.\n";
        return false;
      }
    }
    return true;
}
void EkranGL::Inicjuj()
{
	if(!KonfiguracjaGL()) return;
    set_gl_capability(glconfig);
    add_events(Gdk::BUTTON1_MOTION_MASK|Gdk::BUTTON_PRESS_MASK); 
}

bool EkranGL::on_configure_event(GdkEventConfigure* event)
{
    auto gldrawable = get_gl_drawable();
	if (!gldrawable->gl_begin(get_gl_context()))
    return false;
	UstawienieSceny();
	invalidate();
	//Oswietlenie();
	gldrawable->gl_end();
    return true;
}

void EkranGL::UstawienieSceny()
{
    Komunikat("ustawienie sceny");
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
}
bool EkranGL::on_expose_event(GdkEventExpose* event)
{
	auto gldrawable = get_gl_drawable();
    if (!gldrawable->gl_begin(get_gl_context()))
      return false;

	RysujScene();
    
	if (gldrawable->is_double_buffered())
      gldrawable->swap_buffers();
    else
      glFlush();

	gldrawable->gl_end();
	return true;
}
void EkranGL::on_realize()
{
	Gtk::DrawingArea::on_realize();
}
void EkranGL::RysujScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
}
