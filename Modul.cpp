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
	coUzywam.push_back(m);
	m->coMnieUzywa.push_back(spModul(this));
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
