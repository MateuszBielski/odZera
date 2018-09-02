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
	okno.set_events(Gdk::BUTTON1_MOTION_MASK|Gdk::BUTTON_PRESS_MASK);
    DodajDoListyWskaznikPolaczenia(
        UtrwalPolaczenie(okno.signal_button_press_event().connect(sigc::mem_fun(*this,&PrzesuwanieWidoku::on_button_press_event))));
    DodajDoListyWskaznikPolaczenia(
        UtrwalPolaczenie(okno.signal_motion_notify_event().connect(sigc::mem_fun(*this,&PrzesuwanieWidoku::on_motion_notify_event))));
    return 3;
}
void PrzesuwanieWidoku::PodlaczSygnalPrzeksztalcenieWidoku(EkranGL& ekran)
{
}
bool PrzesuwanieWidoku::on_button_press_event(GdkEventButton* event)
{
    aktualneSterowanie->m_BeginX = event->x;
    aktualneSterowanie->m_BeginY = event->y;
    return false;
}
void PrzesuwanieWidoku::PrzeksztalcenieWidoku(bool b, int i)
{
    glTranslatef(aktualneSterowanie->m_Pos[0],aktualneSterowanie->m_Pos[1],aktualneSterowanie->m_Pos[2]);
    glMultMatrixf(&aktualneSterowanie->macierzObrotu[0][0]);
}
bool PrzesuwanieWidoku::on_motion_notify_event(GdkEventMotion* event)
{
    float nowaPozycjaX,nowaPozycjaY;
    
    nowaPozycjaX = event->x;
    nowaPozycjaY = event->y;
    aktualneSterowanie->m_DX = nowaPozycjaX - aktualneSterowanie->m_BeginX;
    aktualneSterowanie->m_DY = nowaPozycjaY - aktualneSterowanie->m_BeginY;
    aktualneSterowanie->m_BeginX = nowaPozycjaX;
    aktualneSterowanie->m_BeginY = nowaPozycjaY;
    float w = oknoSterowane->get_width();
    float h = oknoSterowane->get_height();
    aktualneSterowanie->m_Pos[0] += 2*aktualneSterowanie->m_DX/w;
    aktualneSterowanie->m_Pos[1] -= 2*aktualneSterowanie->m_DY/h;
//        std::cout << std::bitset<24>(oknoSterowane->get_events())<<std::endl;
	oknoSterowane->get_window()->invalidate_rect(oknoSterowane->get_allocation(), false);
    return true;
}
