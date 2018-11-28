#include "SterowanieModyfikujPunkty.h"
#include "Sterowanie.h"
/****dziedziczy po przekierowanie sygnałów a nie sterowanie*******/
SterowanieModyfikujPunkty::SterowanieModyfikujPunkty(SterowanieMyszaVar_2& m_ster):mojeSterowanie(m_ster)
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
	auto& oknoSterowane = Ref_WyszukajWModulach<EkranGL>("ekranGL");
    sterujPunktami ? WlaczMojeSterowanie() : PrzywrocPoprzednieSterowanie();
    oknoSterowane.get_window()->invalidate_rect(oknoSterowane.get_allocation(), false);
    //zawiesić połączenia dotychczasowego sterowania a włączyć uruchomić dla nowego
    //nowe sterowanie czyli Var2 - załadować w modułach, ale na początku wyłączyć jego połączenia
    //dodać pole dotychczasowe sterowanie
    //może konstruktor zrobić inicjowany nowym sterowaniem Var2, i stosować referencję.
}
void  SterowanieModyfikujPunkty::WlaczMojeSterowanie(){
    dotychczasoweSterowanie = Ptr_WyszukajWModulach<SterowanieMysza>("SterowanieMysza");
    dotychczasoweSterowanie->ZablokujPolaczenia();
    mojeSterowanie.KopiujZinnegoModulu(*dotychczasoweSterowanie);
    mojeSterowanie.OdblokujPolaczenia();
}
void  SterowanieModyfikujPunkty::PrzywrocPoprzednieSterowanie(){
    mojeSterowanie.ZablokujPolaczenia();
    dotychczasoweSterowanie->OdblokujPolaczenia();
}