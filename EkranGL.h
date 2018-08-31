#ifndef EKRANGL_H
#define EKRANGL_H
#include <gtkmm.h>
#include <gtkglmm.h>
#include <iostream>
#include <Komunikat.h>
#include <sigc++/sigc++.h>
#include <Modul.h>
#include <OknoGL.h>
#include <Renderowanie.h>

using namespace Gtk;

using ptrConf = Glib::RefPtr<Gdk::GL::Config>;
using SygnalRysuj = sigc::signal<void, bool, int>;
using SygnalUstaw3f = sigc::signal<void, float *>;
class EkranGL : public GL::DrawingArea, public Modul
{
  public:
    EkranGL();
    virtual ~EkranGL();
    void Inicjuj();
    void ZainstalujSieW(VBox&);
    void invalidate(){get_window()->invalidate_rect(get_allocation(), false);}
    void update(){ get_window()->process_updates(false); }
    virtual int PolaczZkimPotrzebujeNaPoczatek();
    
    SygnalRysuj EmitujSygnalRysuj();
	SygnalRysuj EmitujSygnalTransformacja();
    SygnalUstaw3f EmitujSygnalPolozenieSwiatla();
protected:
    virtual bool on_configure_event(GdkEventConfigure* event);
    virtual bool on_expose_event(GdkEventExpose* event);
    virtual void on_realize();
    virtual void UstawienieSceny();
    virtual void RysujScene();
    virtual void OswietlenieUstaw();
	
    SygnalRysuj sTransformacja;
    SygnalRysuj sRysuj;
    SygnalUstaw3f sPolozenieSwiatla;
private:
    ptrConf glconfig;
    bool KonfiguracjaGL();
    
};
#endif // EKRANGL_H
