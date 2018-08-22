#include "PrzesuwanieWidoku.h"

PrzesuwanieWidoku::PrzesuwanieWidoku()
{
    nazwa = "przesuwanieWidoku";
    zablokujPolaczeniaPrzyStarcie = true;
}

PrzesuwanieWidoku::~PrzesuwanieWidoku()
{
}
int PrzesuwanieWidoku::PodlaczanieSygnalow(Gtk::Widget& okno)
{
    UstawOkno(&okno);
	okno.add_events(Gdk::BUTTON1_MOTION_MASK|Gdk::BUTTON_PRESS_MASK);
    DodajDoListyWskaznikPolaczenia(
        UtrwalPolaczenie(okno.signal_button_press_event().connect(sigc::mem_fun(*this,&PrzesuwanieWidoku::on_button_press_event))));
    DodajDoListyWskaznikPolaczenia(
        UtrwalPolaczenie(okno.signal_motion_notify_event().connect(sigc::mem_fun(*this,&PrzesuwanieWidoku::on_motion_notify_event))));
    Komunikat("PrzesuwanieWidoku::PodlaczanieSygnalow");
    return 3;
}
void PrzesuwanieWidoku::PodlaczSygnalPrzeksztalcenieWidoku(EkranGL& ekran)
{
	DodajDoListyWskaznikPolaczenia(
        UtrwalPolaczenie(ekran.EmitujSygnalTransformacja().connect(sigc::mem_fun(*this,&PrzesuwanieWidoku::PrzeksztalcenieWidoku))));
}
bool PrzesuwanieWidoku::on_button_press_event(GdkEventButton* event)
{

}
void PrzesuwanieWidoku::PrzeksztalcenieWidoku(bool b, int i)
{
    
}
bool PrzesuwanieWidoku::on_motion_notify_event(GdkEventMotion* event)
{
    Komunikat("PrzesuwanieWidoku::on_motion_notify_event");
}
