#ifndef OKNO1_H
#define OKNO1_H
#include <gtkmm.h>
#include <thread>
#include <chrono>
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
	virtual bool on_configure_event(GdkEventConfigure* event);
    VBox vBox;
	TextView tekst;
    Button b_ZmienRozmiar;
	Button b_UstawTekst;
    Button b_UruchomWatek;
	P_BuforTekstu buforTekstu;
private:
    short licznik = 0;
    
};

void PokazLiczenieObiektu(Okno1*);
#endif
