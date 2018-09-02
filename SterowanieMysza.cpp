#include "SterowanieMysza.h"
#include <trackball.h>
#define DIG_2_RAD (G_PI / 180.0)
#define RAD_2_DIG (180.0 / G_PI)

SterowanieMysza::SterowanieMysza()
{
	Komunikat("SterowanieMysza");
	aktualneSterowanie->m_Pos[0] = 0.0;
    aktualneSterowanie->m_Pos[1] = 0.0;
    aktualneSterowanie->m_Pos[2] = -10.0;

    float sine = sin(0.5 * 0.0 * DIG_2_RAD);
    aktualneSterowanie->m_Quat[0] = sine;
    aktualneSterowanie->m_Quat[1] = 0;
    aktualneSterowanie->m_Quat[2] = 0;
    aktualneSterowanie->m_Quat[3] = cos(0.5 * 0.0 * DIG_2_RAD);
	aktualneSterowanie->m_QuatDiff[0] = 0.0;
    aktualneSterowanie->m_QuatDiff[1] = 0.0;
    aktualneSterowanie->m_QuatDiff[2] = 0.0;
    aktualneSterowanie->m_QuatDiff[3] = 1.0;
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

void SterowanieMysza::WyszukujeIustawiamWskaznikiDoInnychModulow(){
	ekran = Ptr_WyszukajWModulach<EkranRysujacy>("ekranGL");
	renderowanie =  Ptr_WyszukajWModulach<Renderowanie>("renderowanie");
	renderowanie->PobierzWskaznikNaWektorPrzesuniecia(&calegoWidoku.m_Pos[0]);
	renderowanie->PobierzWskaznikNaMacierzObrotu(&calegoWidoku.macierzObrotu[0][0]);
	renderowanie->DajWybranyModel()->PobierzWskaznikNaMacierzObrotu(&wybranegoObiektu.macierzObrotu[0][0]);
}
bool SterowanieMysza::on_button_press_event(GdkEventButton* event)
{
    aktualneSterowanie->m_QuatDiff[0] = 0.0;
    aktualneSterowanie->m_QuatDiff[1] = 0.0;
    aktualneSterowanie->m_QuatDiff[2] = 0.0;
    aktualneSterowanie->m_QuatDiff[3] = 1.0;
    
    aktualneSterowanie->m_BeginX = event->x;
    aktualneSterowanie->m_BeginY = event->y;
    //prawy przycisk
    if (event->button == 3){
        float pozycja[4];
        ekran->PodajPozycjeZrodlaSwiatla(pozycja);
       
        float w = oknoSterowane->get_width();
        float h = oknoSterowane->get_height();
        pozycja[0]=2*(2.0 * aktualneSterowanie->m_BeginX - w) / w;
        pozycja[1]=2*(h - 2.0 * aktualneSterowanie->m_BeginY) / h;
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
    aktualneSterowanie->m_DX = x - aktualneSterowanie->m_BeginX;
    aktualneSterowanie->m_DY = y - aktualneSterowanie->m_BeginY;
    if (event->state & GDK_BUTTON1_MASK) {
      Trackball::trackball(aktualneSterowanie->m_QuatDiff,
                           (2.0 * aktualneSterowanie->m_BeginX - w) / w,
                           (h - 2.0 * aktualneSterowanie->m_BeginY) / h,
                           (2.0 * x - w) / w,
                           (h - 2.0 * y) / h);
		Trackball::add_quats(aktualneSterowanie->m_QuatDiff, aktualneSterowanie->m_Quat, aktualneSterowanie->m_Quat);
		Trackball::build_rotmatrix(aktualneSterowanie->macierzObrotu, aktualneSterowanie->m_Quat);

    }
    if (event->state & GDK_BUTTON2_MASK){
        aktualneSterowanie->m_Pos[0] += 2*aktualneSterowanie->m_DX/w;
        aktualneSterowanie->m_Pos[1] -= 2*aktualneSterowanie->m_DY/h;
        
    }
    if (event->state & GDK_BUTTON3_MASK){
        float pozycja[4];
        ekran->PodajPozycjeZrodlaSwiatla(pozycja);
        pozycja[0]+=4*aktualneSterowanie->m_DX/w;
        pozycja[1]-=4*aktualneSterowanie->m_DY/h;
        ekran->UstawPozycjeZrodlaSwiatla(pozycja);
    }
	aktualneSterowanie->m_BeginX = x;
    aktualneSterowanie->m_BeginY = y;
//        std::cout << std::bitset<24>(oknoSterowane->get_events())<<std::endl;
	oknoSterowane->get_window()->invalidate_rect(oknoSterowane->get_allocation(), false);
    //nie może być false bo przekazuje jakby jeszcze kilka razy do obsługi i nie pozwala przeliczyć sie macierzom
    return true;
}

bool SterowanieMysza::on_my_scroll_event(GdkEventScroll* scroll_event)
{
    if (!scroll_event->direction){//GDK_SCROLL_UP
        aktualneSterowanie->m_Pos[2] *=0.9;
    }
    if (scroll_event->direction){//GDK_SCROLL_DOWN
        aktualneSterowanie->m_Pos[2] /=0.9;
    }
    oknoSterowane->get_window()->invalidate_rect(oknoSterowane->get_allocation(), false);
    return true;
}

