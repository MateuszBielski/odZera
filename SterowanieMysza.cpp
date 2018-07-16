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
	okno.add_events(Gdk::BUTTON1_MOTION_MASK|Gdk::BUTTON_PRESS_MASK);
    okno.signal_button_press_event().connect(sigc::mem_fun(*this,&SterowanieMysza::on_button_press_event));//może *this zamiast *okno?
    okno.signal_motion_notify_event().connect(sigc::mem_fun(*this,&SterowanieMysza::on_motion_notify_event));
    return 3;
}
void SterowanieMysza::PodlaczSygnalPrzeksztalcenieWidoku(EkranGL& ekran)
{
	ekran.EmitujSygnalTransformacja().connect(sigc::mem_fun(*this,&SterowanieMysza::PrzeksztalcenieWidoku));
}


bool SterowanieMysza::on_button_press_event(GdkEventButton* event)
{
    Komunikat("SterowanieMysza::on_button_press_event");
    m_QuatDiff[0] = 0.0;
    m_QuatDiff[1] = 0.0;
    m_QuatDiff[2] = 0.0;
    m_QuatDiff[3] = 1.0;
    
    m_BeginX = event->x;
    m_BeginY = event->y;
    return false;
}

bool SterowanieMysza::on_motion_notify_event(GdkEventMotion* event)
{
    Komunikat("on_motion_notify_event");
    float w = oknoSterowane->get_width();
    float h = oknoSterowane->get_height();
    float x = event->x;
    float y = event->y;
    if (event->state & GDK_BUTTON1_MASK) {
      Trackball::trackball(m_QuatDiff,
                           (2.0 * m_BeginX - w) / w,
                           (h - 2.0 * m_BeginY) / h,
                           (2.0 * x - w) / w,
                           (h - 2.0 * y) / h);

      m_DX = x - m_BeginX;
      m_DY = y - m_BeginY;

    }
	m_BeginX = x;
    m_BeginY = y;

	oknoSterowane->get_window()->invalidate_rect(oknoSterowane->get_allocation(), false);
    //nie może być false bo przekazuje jakby jeszcze kilka razy do obsługi i nie pozwala przeliczyć sie macierzom
    return true;
}
void SterowanieMysza::PrzeksztalcenieWidoku(bool b, int i)
{
	Komunikat("SterowanieMysza::przekształcenie widoku");
	glTranslatef(m_Pos[0], m_Pos[1], m_Pos[2]);
	float m[4][4];
	
	Trackball::add_quats(m_QuatDiff, m_Quat, m_Quat);
    Trackball::build_rotmatrix(m, m_Quat);
    glMultMatrixf(&m[0][0]);
}
