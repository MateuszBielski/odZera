#ifndef OKNOGL_H
#define OKNOGL_H
#include <gtkmm.h>
#include <gtkglmm.h>
//#include <memory>
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
protected:
    virtual bool on_configure_event(GdkEventConfigure* event);
private:
    ptrConf glconfig;
    bool KonfiguracjaGL();
    void UstawienieSceny();
};

class OknoGL :  public Window//public GL::DrawingArea,
{
public: 
   OknoGL();
    virtual ~OknoGL();
    void Inicjuj();
private:
    std::unique_ptr<EkranGL> pEkranGL;
};
#endif