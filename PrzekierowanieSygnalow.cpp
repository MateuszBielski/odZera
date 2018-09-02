#include "PrzekierowanieSygnalow.h"
#include "Sterowanie.h"

PrzekierowanieSygnalow::PrzekierowanieSygnalow()
{
    nazwa = "przekierowanieSygnalow";
    Komunikat("Przekierowanie sygnałów");
    czyWybranyObiekt = false;
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
	czyWybranyObiekt = !czyWybranyObiekt;
	UstawSterowanie(czyWybranyObiekt?WYBRANYM_OBIEKTEM:CALYM_WIDOKIEM);
}
void PrzekierowanieSygnalow::UstawSterowanie(short czym)
{
	auto sterowanie = Ptr_WyszukajWModulach<Sterowanie>("sterowanie");
    sterowanie->Steruj(czym);
}
