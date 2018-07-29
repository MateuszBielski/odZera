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
Modul::DodajCoUzywam(spModul m)
{
	auto dodanoCoUzywam = coUzywam.emplace(m);
	auto dodanoCoMnieUzywa = m->coMnieUzywa.emplace(spModul(this));
	if (dodanoCoUzywam.second) g_print("\ndodano %s używam: %s",this->Nazwa().c_str(),m->Nazwa().c_str());
	if (dodanoCoMnieUzywa.second) g_print("\ndodano %s co mnie używa: %s",m->Nazwa().c_str(),this->Nazwa().c_str());
}
Modul::AktualizujPolaczeniaModulowZaleznych()
{
	/*Na początek wypisać zawartość:
	 * coUzywam
	 * coMnieUzywa
	 * następnie dla obu w pętli wywołać:
	 * PolaczZkimPotrzeba (różni się od PolaczZkimPotrzebaNaPoczatek - nie dodaje coUzywam i coMnieUzywa
	 * */
}
