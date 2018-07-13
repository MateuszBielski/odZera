#include "SterowanieMysza.h"
#include <trackball.h>

SterowanieMysza::SterowanieMysza()
{
}

SterowanieMysza::~SterowanieMysza()
{
}

int SterowanieMysza::PodlaczanieSygnalow(Gtk::Widget& okno)
{
    okno.add_events(Gdk::BUTTON1_MOTION_MASK|Gdk::BUTTON_PRESS_MASK);
    okno.signal_button_press_event().connect(sigc::mem_fun(*this,&SterowanieMysza::on_button_press_event));//może *this zamiast *okno?
    okno.signal_motion_notify_event().connect(sigc::mem_fun(*this,&SterowanieMysza::on_motion_notify_event));
    return 3;
}


bool SterowanieMysza::on_button_press_event(GdkEventButton* event)
{
//    Komunikat("SterowanieMysza::on_button_press_event");
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
//    Komunikat("on_motion_notify_event");
    float w = get_width();
    float h = get_height();
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

    invalidate();

    //nie może być false bo przekazuje jakby jeszcze kilka razy do obsługi i nie pozwala przeliczyć sie macierzom
    return true;
}
