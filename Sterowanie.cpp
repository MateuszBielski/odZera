#include "Sterowanie.h"

Sterowanie::Sterowanie()
{
	nazwa = "sterowanie";
	Steruj(CALYM_WIDOKIEM);
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
    WyszukujeIustawiamWskaznikiDoInnychModulow();
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
    aktualneSterowanie->m_BeginX = doSkopiowania.aktualneSterowanie->m_BeginX;
    aktualneSterowanie->m_BeginY = doSkopiowania.aktualneSterowanie->m_BeginY;
    aktualneSterowanie->m_DX = doSkopiowania.aktualneSterowanie->m_DX;
    aktualneSterowanie->m_DY = doSkopiowania.aktualneSterowanie->m_DY;
    for(short i =0 ; i < 3; i++)aktualneSterowanie->m_Pos[i] = doSkopiowania.aktualneSterowanie->m_Pos[i];
    for(short i =0 ; i < 4; i++){
        for(short j =0 ; j < 4; j++){
            aktualneSterowanie->macierzObrotu[i][j] = doSkopiowania.aktualneSterowanie->macierzObrotu[i][j];
        }
    }
        
    g_print("\nSterowanie::KopiujParametrySterowania");
}
void Sterowanie::Steruj(int czym)
{
	switch (czym){
		case CALYM_WIDOKIEM : 
			aktualneSterowanie = &calegoWidoku;
			break;
		case WYBRANYM_OBIEKTEM : 
			aktualneSterowanie = &wybranegoObiektu;
			break;
	}
}
