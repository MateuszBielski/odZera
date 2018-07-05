#ifndef OKNOGL_H
#define OKNOGL_H
#include <EkranRysujacy.h>
#include <SterowanieMysza.h>

class OknoGL :  public Window//public GL::DrawingArea,
{
public: 
   OknoGL();
    virtual ~OknoGL();
    void Inicjuj();
private:
    std::unique_ptr<EkranGL> pEkranGL;
    
    /*należy sprawdzić  możliwość łatwego umieszczania obiektu sterowanie w różnych klasach okna/ekranu
     *- wypróbować, w której sprawdzi się najlepiej*/
    std::unique_ptr<Sterowanie> sterowanie;
    
    Gtk::VBox vBox;
};
#endif