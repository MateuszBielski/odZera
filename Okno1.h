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
    bool Inicjuj();//virtual?
    VBox& refVBox() {return vBox;};
protected:
    virtual void NowyWatek();
    virtual int PodlaczenieSygnalow();
    virtual void ustawElementyOkna();
	virtual void UstawieniaKlasyDziedziczacej(){};
    //
	virtual bool on_configure_event(GdkEventConfigure* event);
    VBox vBox;

    
};

void WatekNaZewnatrz(Okno1* w);

using upOkno1 =  std::unique_ptr<Okno1>;
using spOkno1 =  std::shared_ptr<Okno1>;
#endif
