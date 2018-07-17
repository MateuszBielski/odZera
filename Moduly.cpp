#include <Moduly.h>

Moduly::Moduly()
{
}

Moduly::~Moduly()
{
}

bool Moduly::DolaczDo(spOkno1 okno)
{
    if(okno == nullptr)return false;
    oknoGlowne = okno;
    return true;
}
int Moduly::Uruchom()
{
    oknoGL = std::make_unique<OknoGL>();
    oknoGL->UstawIzainstalujPrzyciskW(oknoGlowne->refVBox());
    
    pEkranGL = std::make_shared<EkranRysujacy>();
    pEkranGL->Inicjuj();
    pEkranGL->ZainstalujSieW(oknoGL->refVBox());
    
    sterowanie = std::make_unique<SterowanieMysza>();
	sterowanie->PodlaczanieSygnalow(*pEkranGL);
	sterowanie->PodlaczSygnalPrzeksztalcenieWidoku(*pEkranGL);
    /*Wykonać  tablicę wskaźników do funkcji u uruchomic je w pętli
     * */
	renderowanie = std::make_shared<Renderowanie>();
    pEkranGL->EmitujSygnalRysuj().connect(sigc::mem_fun(*renderowanie,&Renderowanie::Renderuj));

}
/*bool Moduly::DodajModul(spModul m)
{
	modulyMoje[m->Nazwa()] = m;
    m->JestemDodanyDo(this);
	return true;
}*/
bool Moduly::DodajRefModul(Modul&& m){
//    Komunikat("początek Moduly::DodajRefModul");
    m.JestemDodanyDo(&modulyRefMoje);
    modulyRefMoje.emplace(m.Nazwa(),std::move(m));
//    modulyRefMoje.emplace(std::make_pair(m.Nazwa(),m));
//    modulyRefMoje[m.Nazwa()] = m;
//    modulyRefMoje.insert({m.Nazwa(),std::move(m)});
//    modulyRefMojeVec.push_back(std::move(m));
//    modulyRefMojeVec.emplace_back(m);
//    Komunikat("koniec Moduly::DodajRefModul");
	return true;
}
int Moduly::WszystkieDodaj()
{
	int ileModulowDodano = 0;
	//może lista inicjalizacyjna ? --{OknoGL,EkranRysujacy...}
	DodajRefModul(OknoGL());
	DodajRefModul(EkranRysujacy());
	DodajRefModul(SterowanieMysza());
	DodajRefModul(Renderowanie());
    Komunikat("koniec WszystkieDodaj");
	return ileModulowDodano;//do uzupełnienia
}
int Moduly::WszystkieWyswietlNazwy()
{
    int ile = modulyRefMojeVec.size();
	g_print("\nrozmiar modulyRefMojeVec %d",ile);
    std::string nazwa;
    for(int i = 0; i < ile ; i++){
        nazwa = modulyRefMojeVec.at(i).Nazwa();
        g_print("\n%s",nazwa.c_str());
    }
}
int Moduly::WszystkieWyswietlNazwyMap()
{
    int ile = modulyRefMoje.size();
	g_print("\nrozmiar modulyRefMoje %d",ile);
//    std::string nazwa;
    for (auto& kv : modulyRefMoje) {
        std::cout << kv.first << " has value " << kv.second.Nazwa() <<  std::endl;
    }
}
int Moduly::WszystkiePolaczJakPotrzebuja()
{
	int ilePolaczen = 0;
// modulyRefMoje.size();

    //należy wykonać polecenie: 
//    oknoGL->UstawIzainstalujPrzyciskW(oknoGlowne->refVBox());
    for(auto& m : modulyRefMoje){
        ilePolaczen += m.second.PolaczZkimPorzebujeNaPoczatek();
    }
    return ilePolaczen;
}
