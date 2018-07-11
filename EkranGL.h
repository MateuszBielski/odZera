#ifndef EKRANGL_H
#define EKRANGL_H
#include <gtkmm.h>
#include <gtkglmm.h>
#include <iostream>
#include <Komunikat.h>
#include <sigc++/sigc++.h>

using namespace Gtk;

using ptrConf = Glib::RefPtr<Gdk::GL::Config>;
//using SygnalRysuj = sigc::signal<void, int, bool>;
typedef sigc::signal<void,int, bool> SygnalRysuj;
class EkranGL : public GL::DrawingArea
{
  public:
    EkranGL();
    virtual ~EkranGL();
    void Inicjuj();
    void ZainstalujSieW(VBox&);
    void invalidate(){get_window()->invalidate_rect(get_allocation(), false);}
    void update(){ get_window()->process_updates(false); }
	SygnalRysuj sRysuj;
    
    void do_something();
  //signal accessor:
  typedef sigc::signal<void, bool, int> type_signal_something;
  type_signal_something signal_something();
protected:
    virtual bool on_configure_event(GdkEventConfigure* event);
    virtual bool on_expose_event(GdkEventExpose* event);
    virtual void on_realize();
    virtual void UstawienieSceny();
    virtual void RysujScene();
    
    type_signal_something m_signal_something;
private:
    ptrConf glconfig;
    bool KonfiguracjaGL();
    
};
#endif // EKRANGL_H
