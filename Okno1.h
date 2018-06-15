#ifndef OKNO1_H
#define OKNO1_H
#include <gtkmm.h>
#include <stdlib.h> 
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
protected:
    //
    void NaPrzyciskZmienRozmiar();
	virtual bool on_configure_event(GdkEventConfigure* event);
    VBox vBox;
	TextView tekst;
    Button b_ZmienRozmiar;
	Button b_UstawTekst;
	P_BuforTekstu buforTekstu;
    
};
#endif
