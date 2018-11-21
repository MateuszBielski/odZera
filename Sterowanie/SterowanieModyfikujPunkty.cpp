#include "SterowanieModyfikujPunkty.h"
#include "Sterowanie.h"

SterowanieModyfikujPunkty::SterowanieModyfikujPunkty()
{
    nazwa = "sterowanieModyfikujPunkty";
    Komunikat("sterowanieModyfikujPunkty");
    sterujPunktami = false;
}

SterowanieModyfikujPunkty::~SterowanieModyfikujPunkty()
{
}
int SterowanieModyfikujPunkty::PolaczZkimPotrzebujeNaPoczatek()
{
	UstawIzainstalujPrzyciskW(oknoPodstawowe->refVBox());
    connModyfikujPunkty = UtrwalPolaczenie(bObslugaTegoModulu.signal_clicked().connect(sigc::mem_fun(*this,&SterowanieModyfikujPunkty::PrzelaczSterowanie)));
     DodajDoListyWskaznikPolaczenia(connModyfikujPunkty);
	 
}
void SterowanieModyfikujPunkty::UstawIzainstalujPrzyciskW(VBox& vbox)
{
	Komunikat("SterowanieModyfikujPunkty::UstawIzainstalujPrzyciskW");
    bObslugaTegoModulu.set_label("modyfikuj punkty");
    vbox.pack_start(bObslugaTegoModulu,Gtk::PACK_SHRINK);
    vbox.show_all();
    
}
void SterowanieModyfikujPunkty::PrzelaczSterowanie()
{
    sterujPunktami = !sterujPunktami;
    Ptr_WyszukajWModulach<Renderowanie1>("renderowanie")->UstawRysowanieZwidocznymiPunktami(sterujPunktami);
}
void SterowanieModyfikujPunkty::UstawSterowanie(short czym)
{
	/*auto sterowanie = Ptr_WyszukajWModulach<Sterowanie>("sterowanie");
    sterowanie->Steruj(czym);*/
}