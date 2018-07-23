#include "EkranGL.h"

EkranGL::EkranGL()
{
	nazwa = "ekranGL";
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
    Komunikat("EkranGL::on_configure_event");
	auto gldrawable = get_gl_drawable();
	if (!gldrawable->gl_begin(get_gl_context()))
    return false;
	UstawienieSceny();
	invalidate();
	Oswietlenie();
	//RysujScene();
	if (gldrawable->is_double_buffered())
      gldrawable->swap_buffers();
    else
      glFlush();
	gldrawable->gl_end();
    return true;
}

void EkranGL::UstawienieSceny()
{
    Komunikat("EkranGL::UstawienieSceny");
    
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
	Komunikat("EkranGL::RysujScene");
	
}
SygnalRysuj EkranGL::EmitujSygnalRysuj() 
{
	return sRysuj;
}
SygnalRysuj EkranGL::EmitujSygnalTransformacja()
{
	return sTransformacja;
}
void EkranGL::ZainstalujSieW(VBox& vbox)
{
	vbox.pack_start(*this);
    vbox.show_all();
}
void EkranGL::Oswietlenie()
{
	Komunikat("EkranGL::Oswietlenie");
}
int EkranGL::PolaczZkimPorzebujeNaPoczatek()
{
	auto znalezionyModul = WyszukajWModulach_Ref<Renderowanie>("renderowanie",*mapaZmodulami);
    
    auto oknoGL =std::dynamic_pointer_cast<OknoGL>(WyszukajWDodanychModulach("oknoGL"));
    Inicjuj();
    ZainstalujSieW(oknoGL->refVBox());
    
    auto renderowanie =std::dynamic_pointer_cast<Renderowanie>(WyszukajWDodanychModulach("renderowanie"));
    EmitujSygnalRysuj().connect(sigc::mem_fun(*renderowanie,&Renderowanie::Renderuj));
    return 2;
}
