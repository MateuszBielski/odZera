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
bool Moduly::DodajModul(spModul m)
{
	modulyMoje[m->Nazwa()] = m;
    m->JestemDodanyDo(this);
//    g_print("dodano %s",m->Nazwa().c_str());
	return true;
}
bool Moduly::DodajRefModul(Modul&& m){
    modulyRefMoje.emplace(m.Nazwa(),m);
    m.JestemDodanyDo(&modulyRefMoje);
	return true;
}
int Moduly::WszystkieDodaj()
{
	int ileModulowDodano = 0;
	//może lista inicjalizacyjna ? --{OknoGL,EkranRysujacy...}
//	DodajRefModul(OknoGL());
//	DodajRefModul(EkranRysujacy());
//	DodajRefModul(SterowanieMysza());
//	DodajRefModul(Renderowanie());
    typename obiekt[] = ({OknoGL,EkranRysujacy});
    DodajModul(UtworzModulTypu<OknoGL>());
	return ileModulowDodano;//do uzupełnienia
}
template <typename T>
spModul Moduly::UtworzModulTypu()
{
	return std::make_shared<T>();
}
