#include <Modul.h>

Modul::Modul()
{
//	Komunikat("Modul konstruktor");
}
Modul::~Modul()
{
//	Komunikat("Moduł destruktor");
}
void Modul::JestemDodanyDo(MapaStringModul* mapa)
{
	mapaZmodulami = mapa;
}
void Modul::DodajCoUzywam(spModul m)
{
	auto dodanoCoUzywam = coUzywam.insert(m);
	auto dodanoCoMnieUzywa = m->coMnieUzywa.insert(shared_from_this());
//	if (dodanoCoUzywam.second) g_print("\ndodano %s używam: %s",this->Nazwa().c_str(),m->Nazwa().c_str());
//	if (dodanoCoMnieUzywa.second) g_print("\ndodano %s co mnie używa: %s",m->Nazwa().c_str(),this->Nazwa().c_str());
}
void Modul::AktualizujPolaczeniaModulowZaleznych()
{
	/*Na początek wypisać zawartość:
	 * coUzywam
	 * coMnieUzywa
	 * następnie dla obu w pętli wywołać:
	 * PolaczZkimPotrzeba (różni się od PolaczZkimPotrzebaNaPoczatek - nie dodaje coUzywam i coMnieUzywa
	 * */
}
bool Modul::CzyJestModul(std::string rodzaj)
{
    return mapaZmodulami->count(rodzaj);
}
void Modul::DodajDoListyWskaznikPolaczenia(spConnection polaczenie)
{
    mojePolaczenia.push_back(polaczenie);
}
void Modul::ZablokujPolaczenia()
{
    if(!mojePolaczenia.size())return;
    auto iter = mojePolaczenia.begin();
    auto koniec = mojePolaczenia.end();
    auto polaczenie = *iter;
    int ile = 0;
    while(iter != koniec){
        polaczenie = *iter++;
        if(!polaczenie->blocked())polaczenie->block();
        ile++;
    }
    g_print("\nzablokowano %d połączeń w %s",ile,Nazwa().c_str());
}
void Modul::OdblokujPolaczenia()
{
    if(!mojePolaczenia.size())return;
    auto iter = mojePolaczenia.begin();
    auto koniec = mojePolaczenia.end();
    auto polaczenie = *iter;
    int ile = 0;
    while(iter != koniec){
        polaczenie = *iter++;
        if(polaczenie->blocked())polaczenie->unblock();
        ile++;
    }
    g_print("\nodblokowano %d połączeń w %s",ile,Nazwa().c_str());
}
Modul::spConnection Modul::UtrwalPolaczenie(sigc::connection&& polaczenie)
{
	auto wskaznik = std::make_shared<sigc::connection>();
    *wskaznik = polaczenie;
    return wskaznik;
}

