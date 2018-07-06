#ifndef OKNOGL_H
#define OKNOGL_H
#include <EkranRysujacy.h>

class OknoGL :  public Window//public GL::DrawingArea,
{
public: 
   OknoGL();
    virtual ~OknoGL();
    void Inicjuj();
    //Button& ButtonNoweOkno(){return b_NoweOknoGL;};
    void UstawIzainstalujPrzyciskW(Gtk::VBox&);
private:
    std::unique_ptr<EkranGL> pEkranGL;
    Gtk::VBox vBox;
    Gtk::Button b_NoweOknoGL;
};
#endif