#include <ZmienTrybSterowania.h>
#include "Sterowanie.h"

ZmienTrybSterowania::ZmienTrybSterowania()
{
    nazwa = "zmienTrybSterowania";
    Komunikat("zmienTrybSterowania");
    czyWybranyObiekt = false;
}

ZmienTrybSterowania::~ZmienTrybSterowania()
{
}
int ZmienTrybSterowania::PolaczZkimPotrzebujeNaPoczatek()
{
	UstawIzainstalujPrzyciskW(oknoPodstawowe->refVBox());
    connZmianaTrybu = UtrwalPolaczenie(bObslugaTegoModulu.signal_clicked().connect(sigc::mem_fun(*this,&ZmienTrybSterowania::PrzelaczSterowanie)));
     DodajDoListyWskaznikPolaczenia(connZmianaTrybu);
	 
}
void ZmienTrybSterowania::UstawIzainstalujPrzyciskW(VBox& vbox)
{
	Komunikat("ZmienTrybSterowania::UstawIzainstalujPrzyciskW");
    bObslugaTegoModulu.set_label("zmień tryb sterowania");
    vbox.pack_start(bObslugaTegoModulu,Gtk::PACK_SHRINK);
    vbox.show_all();
    
}
void ZmienTrybSterowania::PrzelaczSterowanie()
{
	czyWybranyObiekt = !czyWybranyObiekt;
	UstawSterowanie(czyWybranyObiekt?WYBRANYM_OBIEKTEM:CALYM_WIDOKIEM);
}
void ZmienTrybSterowania::UstawSterowanie(short czym)
{
	auto sterowanie = Ptr_WyszukajWModulach<Sterowanie>("sterowanie");
    sterowanie->Steruj(czym);
}