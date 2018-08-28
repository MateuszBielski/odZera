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
void Sterowanie::KopiujZinnegoModulu(spModul zDanymi)
{
	auto wskaznikNaWlasciwyTyp = std::dynamic_pointer_cast<Sterowanie>(zDanymi);
    KopiujParametrySterowania(*wskaznikNaWlasciwyTyp);
}
void Sterowanie::KopiujParametrySterowania(Sterowanie& doSkopiowania)
{
    m_BeginX = doSkopiowania.m_BeginX;
    m_BeginY = doSkopiowania.m_BeginY;
    m_DX = doSkopiowania.m_DX;
    m_DY = doSkopiowania.m_DY;
    for(short i =0 ; i < 3; i++)m_Pos[i] = doSkopiowania.m_Pos[i];
    g_print("\nSterowanie::KopiujParametrySterowania");
}

