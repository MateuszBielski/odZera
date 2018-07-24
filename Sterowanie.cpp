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
int Sterowanie::PolaczZkimPorzebujeNaPoczatek()
{
    auto& ekran = Ref_WyszukajWModulach<EkranGL>("ekranGL");
    PodlaczanieSygnalow(ekran);
	PodlaczSygnalPrzeksztalcenieWidoku(ekran);
    return 2;
}
