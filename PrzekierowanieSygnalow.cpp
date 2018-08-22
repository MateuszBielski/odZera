#include "PrzekierowanieSygnalow.h"
#include "PrzesuwanieWidoku.h"

PrzekierowanieSygnalow::PrzekierowanieSygnalow()
{
    nazwa = "przekierowanieSygnalow";
    Komunikat("Przekierowanie sygnałów");
    czyPrzesuwaj = false;
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
	 connZmianaTrybu = UtrwalPolaczenie(bObslugaTegoModulu.signal_clicked().connect(sigc::mem_fun(*this,&PrzekierowanieSygnalow::PrzelaczSterowanie)));
     DodajDoListyWskaznikPolaczenia(connZmianaTrybu);
	 
}
void PrzekierowanieSygnalow::UstawIzainstalujPrzyciskW(VBox& vbox)
{
	Komunikat("PrzekierowanieSygnalow::UstawIzainstalujPrzyciskW");
    bObslugaTegoModulu.set_label("zmień tryb sterowania");
    vbox.pack_start(bObslugaTegoModulu,Gtk::PACK_SHRINK);
    vbox.show_all();
    
}
void PrzekierowanieSygnalow::PrzelaczSterowanie()
{
	czyPrzesuwaj = !czyPrzesuwaj;
    short sterowanie;
    sterowanie = czyPrzesuwaj?PRZESUWANIE_PO_EKRANIE:OBROTY_ARCBALL;
    UstawSterowanie(sterowanie);
}
void PrzekierowanieSygnalow::UstawSterowanie(short jakie)
{
    g_print("\nustawiono sterowanie %d",jakie);
    
    switch(jakie){
        case OBROTY_ARCBALL:
            (*mapaZmodulami)["sterowanie"]->OdblokujPolaczenia();
        break;
        case PRZESUWANIE_PO_EKRANIE:
            (*mapaZmodulami)["sterowanie"]->ZablokujPolaczenia();
            
            if(!mapaZmodulami->count("przesuwanieWidoku")){
                (*mapaZmodulami)["przesuwanieWidoku"] = std::make_shared<PrzesuwanieWidoku>();
                Komunikat("dodano moduł przesuwanie widoku");
            }
            
            
        break;
    }
}
