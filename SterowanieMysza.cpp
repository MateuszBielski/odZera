#include "SterowanieMysza.h"
#include <trackball.h>
#define DIG_2_RAD (G_PI / 180.0)
#define RAD_2_DIG (180.0 / G_PI)

SterowanieMysza::SterowanieMysza()
{
	Komunikat("SterowanieMysza");
	m_Pos[0] = 0.0;
    m_Pos[1] = 0.0;
    m_Pos[2] = -10.0;

    float sine = sin(0.5 * 0.0 * DIG_2_RAD);
    m_Quat[0] = sine;
    m_Quat[1] = 0;
    m_Quat[2] = 0;
    m_Quat[3] = cos(0.5 * 0.0 * DIG_2_RAD);
	m_QuatDiff[0] = 0.0;
    m_QuatDiff[1] = 0.0;
    m_QuatDiff[2] = 0.0;
    m_QuatDiff[3] = 1.0;
}

SterowanieMysza::~SterowanieMysza()
{
	Komunikat("~SterowanieMysza");
}

int SterowanieMysza::PodlaczanieSygnalow(Gtk::Widget& okno)
{
    UstawOkno(&okno);
	okno.set_events(Gdk::BUTTON1_MOTION_MASK|Gdk::BUTTON_PRESS_MASK|Gdk::SCROLL_MASK|Gdk::BUTTON2_MOTION_MASK|Gdk::BUTTON3_MOTION_MASK);
    DodajDoListyWskaznikPolaczenia(
        UtrwalPolaczenie(okno.signal_button_press_event().connect(sigc::mem_fun(*this,&SterowanieMysza::on_button_press_event))));
    DodajDoListyWskaznikPolaczenia(
        UtrwalPolaczenie(okno.signal_motion_notify_event().connect(sigc::mem_fun(*this,&SterowanieMysza::on_motion_notify_event))));
    DodajDoListyWskaznikPolaczenia(
        UtrwalPolaczenie(okno.signal_scroll_event().connect(sigc::mem_fun(*this,&SterowanieMysza::on_my_scroll_event))));
   return 3;
}
void SterowanieMysza::PodlaczSygnalPrzeksztalcenieWidoku(EkranGL& ekran)
{
	DodajDoListyWskaznikPolaczenia(
        UtrwalPolaczenie(ekran.EmitujSygnalTransformacja().connect(sigc::mem_fun(*this,&SterowanieMysza::PrzeksztalcenieWidoku))));
    
}
void SterowanieMysza::WyszukujeIustawiamWskaznikiDoInnychModulow(){
    ekran = Ptr_WyszukajWModulach<EkranRysujacy>("ekranGL");
    
}
bool SterowanieMysza::on_button_press_event(GdkEventButton* event)
{
    m_QuatDiff[0] = 0.0;
    m_QuatDiff[1] = 0.0;
    m_QuatDiff[2] = 0.0;
    m_QuatDiff[3] = 1.0;
    
    m_BeginX = event->x;
    m_BeginY = event->y;
    //prawy przycisk
    if (event->button == 3){
        float pozycja[4];
        ekran->PodajPozycjeZrodlaSwiatla(pozycja);
       
        float w = oknoSterowane->get_width();
        float h = oknoSterowane->get_height();
        pozycja[0]=2*(2.0 * m_BeginX - w) / w;
        pozycja[1]=2*(h - 2.0 * m_BeginY) / h;
        ekran->UstawPozycjeZrodlaSwiatla(pozycja);
    }
    oknoSterowane->get_window()->invalidate_rect(oknoSterowane->get_allocation(), false);
    return true;
}

bool SterowanieMysza::on_motion_notify_event(GdkEventMotion* event)
{
    float w = oknoSterowane->get_width();
    float h = oknoSterowane->get_height();
    float x = event->x;
    float y = event->y;
    m_DX = x - m_BeginX;
    m_DY = y - m_BeginY;
    if (event->state & GDK_BUTTON1_MASK) {
      Trackball::trackball(m_QuatDiff,
                           (2.0 * m_BeginX - w) / w,
                           (h - 2.0 * m_BeginY) / h,
                           (2.0 * x - w) / w,
                           (h - 2.0 * y) / h);

    }
    if (event->state & GDK_BUTTON2_MASK){
        m_Pos[0] += 2*m_DX/w;
        m_Pos[1] -= 2*m_DY/h;
        
    }
    if (event->state & GDK_BUTTON3_MASK){
        float pozycja[4];
        ekran->PodajPozycjeZrodlaSwiatla(pozycja);
        pozycja[0]+=4*m_DX/w;
        pozycja[1]-=4*m_DY/h;
        ekran->UstawPozycjeZrodlaSwiatla(pozycja);
    }
	m_BeginX = x;
    m_BeginY = y;
//        std::cout << std::bitset<24>(oknoSterowane->get_events())<<std::endl;
	oknoSterowane->get_window()->invalidate_rect(oknoSterowane->get_allocation(), false);
    //nie może być false bo przekazuje jakby jeszcze kilka razy do obsługi i nie pozwala przeliczyć sie macierzom
    return true;
}
void SterowanieMysza::PrzeksztalcenieWidoku(bool b, int i)
{
	glTranslatef(m_Pos[0], m_Pos[1], m_Pos[2]);
	
	
	Trackball::add_quats(m_QuatDiff, m_Quat, m_Quat);
    Trackball::build_rotmatrix(macierzObrotu, m_Quat);
    glMultMatrixf(&macierzObrotu[0][0]);
}
bool SterowanieMysza::on_my_scroll_event(GdkEventScroll* scroll_event)
{
    if (!scroll_event->direction){//GDK_SCROLL_UP
        m_Pos[2] *=0.9;
    }
    if (scroll_event->direction){//GDK_SCROLL_DOWN
        m_Pos[2] /=0.9;
    }
    oknoSterowane->get_window()->invalidate_rect(oknoSterowane->get_allocation(), false);
    return true;
}

