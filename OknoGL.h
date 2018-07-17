#ifndef OKNOGL_H
#define OKNOGL_H
#include <EkranRysujacy.h>
#include <Modul.h>



using namespace Gtk;


class OknoGL :  public Window, public Modul
{
public: 
   OknoGL();
    virtual ~OknoGL();
    void Inicjuj();
    void UstawIzainstalujPrzyciskW(VBox&);
	virtual bool on_my_delete_event(GdkEventAny* any_event);
	void Pokaz();
	void Ukryj();
	virtual int PolaczZkimPorzebujeNaPoczatek();
    VBox& refVBox(){return vBox;};
private:
	using pfVoid = void (OknoGL::*)();
    void PrzestawDzialanieButtObsluga(const char * etykieta, pfVoid func );
    VBox vBox;
    Button bObslugaTegoOkna;
	sigc::connection connectionButton;
};
using upOknoGL = std::unique_ptr<OknoGL>;
#endif