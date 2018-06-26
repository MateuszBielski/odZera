#ifndef OKNO1_H
#define OKNO1_H
#include <gtkmm.h>
#include <thread>
#include <chrono>
#include <OknoGL.h>
//#include <stdlib.h> 
using namespace Gtk;


using P_BuforTekstu = Glib::RefPtr<TextBuffer>;

class Okno1 : public Window
{
public:
    Okno1();
    virtual ~Okno1(){};
    bool Inicjuj();
    int PodlaczenieSygnalow();
    void ustawElementyOkna();
	void WypelnijBufor();
	void WypiszRozmiarOkna(int,int);
    void NowyWatek();
    void PokazLiczenie();
protected:
    //
    void NaPrzyciskZmienRozmiar();
    void NoweOknoGL();
	virtual bool on_configure_event(GdkEventConfigure* event);
    VBox vBox;
	TextView tekst;
    Button b_ZmienRozmiar;
	Button b_UstawTekst;
    Button b_UruchomWatek;
    Button b_NoweOknoGL;
	P_BuforTekstu buforTekstu;
private:
    short licznik = 0;
    std::thread* watek;
    std::unique_ptr<OknoGL> oknoGL;
    
};

void WatekNaZewnatrz(Okno1* w);
#endif
