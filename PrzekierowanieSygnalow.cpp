#include "PrzekierowanieSygnalow.h"

PrzekierowanieSygnalow::PrzekierowanieSygnalow()
{
}

PrzekierowanieSygnalow::~PrzekierowanieSygnalow()
{
}
int PrzekierowanieSygnalow::PolaczZkimPorzebujeNaPoczatek()
{
	/******************
	 * emisja sygnału : gdzieś wybrany (np przycisk) połączyć trzeba z funkcją 
	 * np. wybranie trybu przesuwania widoku wywołuje (connect) funkcję PrzekierowanieSygnalow::UstawSterowanie(string "przesuwanieWidoku")
	 * w którymś miejscu należy wywołać funkcję, która doda do modułów przesuwanie widoku lub też od razu podmieni:
	 * sterowanie = przesuwanie widoku , przechowalnia obiektu = Sterowanie myszą
	 * następnie przeprowadzić aktualizację połączeń modułów zależnych od podmienianego, czyli tych, których on używa, lub które uzywają jego*/
	 
	 
}
