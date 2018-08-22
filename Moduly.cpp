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
	return true;
}

int Moduly::WszystkieDodaj()
{
	int ileModulowDodano = 0;
	//może lista inicjalizacyjna ? --{OknoGL,EkranRysujacy...}
    DodajModul(UtworzModulTypu<OknoGL>());
    DodajModul(UtworzModulTypu<EkranRysujacy>());
    DodajModul(UtworzModulTypu<SterowanieMysza>());
    DodajModul(UtworzModulTypu<Renderowanie>());
    DodajModul(UtworzModulTypu<PrzekierowanieSygnalow>());
    DodajModul(UtworzModulTypu<PrzesuwanieWidoku>());
    return ileModulowDodano;//do uzupełnienia
}
int Moduly::WszystkiePolaczJakPotrzebuja()
{
	int ilePolaczen = 0;

    modulyMoje["oknoGL"]->UstawIzainstalujPrzyciskW(oknoGlowne->refVBox());
    modulyMoje["przekierowanieSygnalow"]->UstawIzainstalujPrzyciskW(oknoGlowne->refVBox());
    for(auto& m : modulyMoje){
        ilePolaczen += m.second->PolaczZkimPotrzebujeNaPoczatek();
    }
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

