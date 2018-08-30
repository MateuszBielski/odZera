#include "PrzekierowanieSygnalow.h"
#include "PrzesuwanieWidoku.h"

PrzekierowanieSygnalow::PrzekierowanieSygnalow()
{
    nazwa = "przekierowanieSygnalow";
    Komunikat("Przekierowanie sygnałów");
    czyPrzesuwaj = false;
}

PrzekierowanieSygnalow::~PrzekierowanieSygnalow()
{
}
int PrzekierowanieSygnalow::PolaczZkimPotrzebujeNaPoczatek()
{
	 connZmianaTrybu = UtrwalPolaczenie(bObslugaTegoModulu.signal_clicked().connect(sigc::mem_fun(*this,&PrzekierowanieSygnalow::PrzelaczSterowanie)));
     DodajDoListyWskaznikPolaczenia(connZmianaTrybu);
	 
}
void PrzekierowanieSygnalow::UstawIzainstalujPrzyciskW(VBox& vbox)
{
	Komunikat("PrzekierowanieSygnalow::UstawIzainstalujPrzyciskW");
    bObslugaTegoModulu.set_label("zmień tryb sterowania");
    vbox.pack_start(bObslugaTegoModulu,Gtk::PACK_SHRINK);
    vbox.show_all();
    
}
void PrzekierowanieSygnalow::PrzelaczSterowanie()
{
	czyPrzesuwaj = !czyPrzesuwaj;
    short sterowanie;
    sterowanie = czyPrzesuwaj?PRZESUWANIE_PO_EKRANIE:OBROTY_ARCBALL;
    UstawSterowanie(sterowanie);
}
void PrzekierowanieSygnalow::UstawSterowanie(short jakie)
{
    g_print("\nustawiono sterowanie %d",jakie);
    auto przesuwanie = (*mapaZmodulami)["przesuwanieWidoku"];
    auto obroty = (*mapaZmodulami)["sterowanie"];
    switch(jakie){
        case OBROTY_ARCBALL:
            przesuwanie->ZablokujPolaczenia();
            obroty->KopiujZinnegoModulu(przesuwanie);
            obroty->OdblokujPolaczenia();
        break;
        case PRZESUWANIE_PO_EKRANIE:
            obroty->ZablokujPolaczenia();
            przesuwanie->KopiujZinnegoModulu(obroty);
            przesuwanie->OdblokujPolaczenia();
        break;
    }
}
