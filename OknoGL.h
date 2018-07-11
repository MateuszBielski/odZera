#ifndef OKNOGL_H
#define OKNOGL_H
#include <EkranRysujacy.h>



using namespace Gtk;

class OknoGL :  public Window
{
public: 
   OknoGL();
    virtual ~OknoGL();
    void Inicjuj();
    void UstawIzainstalujPrzyciskW(VBox&);
	virtual bool on_my_delete_event(GdkEventAny* any_event);
    VBox& refVBox(){return vBox;};
private:
    
    VBox vBox;
    Button b_NoweOknoGL;
};
using upOknoGL = std::unique_ptr<OknoGL>;
#endif