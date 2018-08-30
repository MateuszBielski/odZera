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
	DodajDoListyWskaznikPolaczenia(
        UtrwalPolaczenie(ekran.EmitujSygnalTransformacja().connect(sigc::mem_fun(*this,&PrzesuwanieWidoku::PrzeksztalcenieWidoku))));
}
bool PrzesuwanieWidoku::on_button_press_event(GdkEventButton* event)
{
    m_BeginX = event->x;
    m_BeginY = event->y;
    return false;
}
void PrzesuwanieWidoku::PrzeksztalcenieWidoku(bool b, int i)
{
    glTranslatef(m_Pos[0], m_Pos[1], m_Pos[2]);
    glMultMatrixf(&macierzObrotu[0][0]);
}
bool PrzesuwanieWidoku::on_motion_notify_event(GdkEventMotion* event)
{
    float nowaPozycjaX,nowaPozycjaY;
    
    nowaPozycjaX = event->x;
    nowaPozycjaY = event->y;
    m_DX = nowaPozycjaX - m_BeginX;
    m_DY = nowaPozycjaY - m_BeginY;
    m_BeginX = nowaPozycjaX;
    m_BeginY = nowaPozycjaY;
    float w = oknoSterowane->get_width();
    float h = oknoSterowane->get_height();
    m_Pos[0] += 2*m_DX/w;
    m_Pos[1] -= 2*m_DY/h;
//        std::cout << std::bitset<24>(oknoSterowane->get_events())<<std::endl;
	oknoSterowane->get_window()->invalidate_rect(oknoSterowane->get_allocation(), false);
    return true;
}
