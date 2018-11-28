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

bool Moduly::DodajModul(spModul m)
{
	modulyMoje[m->Nazwa()] = m;
    m->JestemDodanyDo(&modulyMoje);
    m->BioreWskaznikDo(oknoGlowne);
	return true;
}

int Moduly::WszystkieDodaj()
{
	int ileModulowDodano = 0;
	//może lista inicjalizacyjna ? --{OknoGL,EkranRysujacy...}
    DodajModul(UtworzModulTypu<OknoGL>());
    DodajModul(UtworzModulTypu<EkranRysujacy>());
    auto zarzadzanieObiektami = std::make_shared<ZarzadzanieObiektami>();
    auto renderowanie = std::make_shared<Renderowanie1>(*zarzadzanieObiektami);
    DodajModul(zarzadzanieObiektami);
    DodajModul(renderowanie);
    DodajModul(UtworzModulTypu<SterowanieMyszaVar_1>());//SterowanieMysza
    DodajModul(UtworzModulTypu<ZmienTrybSterowania>());
    auto sterowanieMysza_2 = std::make_shared<SterowanieMyszaVar_1>();
    auto sterModPunkty = std::make_shared<SterowanieModyfikujPunkty>(sterowanieMysza_2);
    DodajModul(sterowanieMysza_2);
    
    return ileModulowDodano;//do uzupełnienia
}
int Moduly::WszystkiePolaczJakPotrzebuja()
{
	int ilePolaczen = 0;
    for(auto& m : modulyMoje){
        ilePolaczen += m.second->PolaczZkimPotrzebujeNaPoczatek();
//        std::cout << m.first << " ma wartosc: " << m.second->Nazwa() <<  std::endl;
    }
//    Komunikat("koniec Moduly::WszystkiePolaczJakPotrzebuja");
    return ilePolaczen;
}
template <typename T>
spModul Moduly::UtworzModulTypu()
{
	return std::make_shared<T>();
}

int Moduly::WszystkieNazwyWyswietl()
{
    int ile = modulyMoje.size();
	g_print("\nrozmiar modulyRefMoje %d",ile);
    for (auto& kv : modulyMoje) {
        std::cout << kv.first << " has value " << kv.second->Nazwa() <<  std::endl;
    }
}

