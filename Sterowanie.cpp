#include "Sterowanie.h"

Sterowanie::Sterowanie()
{
	nazwa = "sterowanie";
}

Sterowanie::~Sterowanie()
{
}
int Sterowanie::PodlaczanieSygnalow(Gtk::Widget& okno)
{
	int ileSygnalow = 0;
	return ileSygnalow;
}

void Sterowanie::UstawOkno(Gtk::Widget* o)
{
	oknoSterowane = o;
}
int Sterowanie::PolaczZkimPotrzebujeNaPoczatek()
{
    std::string nazwaModulu = ("ekranGL");
	DodajCoUzywam((*mapaZmodulami)[nazwaModulu]);
	
	auto& ekran = Ref_WyszukajWModulach<EkranGL>(nazwaModulu);
	PodlaczanieSygnalow(ekran);
	PodlaczSygnalPrzeksztalcenieWidoku(ekran);
    if(zablokujPolaczeniaPrzyStarcie)ZablokujPolaczenia();
    return 2;
}
