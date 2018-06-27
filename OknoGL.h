#ifndef OKNOGL_H
#define OKNOGL_H
#include <gtkmm.h>
#include <gtkglmm.h>
#include <iostream>
#include <Komunikat.h>
using namespace Gtk;

using ptrConf = Glib::RefPtr<Gdk::GL::Config>;

class EkranGL : public GL::DrawingArea
{
  public:
    EkranGL();
    virtual ~EkranGL();
    void Inicjuj();
    void invalidate() {
      get_window()->invalidate_rect(get_allocation(), false);
    }

    // Update window synchronously (fast).
    void update()
    { get_window()->process_updates(false); }
protected:
    virtual bool on_configure_event(GdkEventConfigure* event);
    virtual bool on_expose_event(GdkEventExpose* event);
    virtual void on_realize();
private:
    ptrConf glconfig;
    bool KonfiguracjaGL();
    void UstawienieSceny();
    void RysujScene();
    
};

class OknoGL :  public Window//public GL::DrawingArea,
{
public: 
   OknoGL();
    virtual ~OknoGL();
    void Inicjuj();
private:
    std::unique_ptr<EkranGL> pEkranGL;
    Gtk::VBox vBox;
};
#endif