#ifndef OKNOGL_H
#define OKNOGL_H
#include <EkranRysujacy.h>

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