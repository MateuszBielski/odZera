#include "SterowanieMysza.h"

SterowanieMysza::SterowanieMysza()
{
}

SterowanieMysza::~SterowanieMysza()
{
}

int SterowanieMysza::PodlaczanieSygnalow(Widget& okno)
{
    //sprawdzić skąd pochodzą te sygnały - wydaje się, że z okna, które ma być obsługiwane
    //można użyć czegoś takiego jak kontener zawierający funkcje i je wywoływać wszystkie.
    okno->add_events(Gdk::BUTTON1_MOTION_MASK|Gdk::BUTTON_PRESS_MASK);
    okno->signal_button_press_event().connect(sigc::mem_fun(*okno,&SterowanieMysza::on_button_press_event));//może *this zamiast *okno?
    okno->signal_motion_notify_event().connect(sigc::mem_fun(*okno,&SterowanieMysza::on_motion_notify_event));
    
}

bool SterowanieMysza::on_button_press_event(GdkEventButton* event)
{
    Komunikat("SterowanieMysza::on_button_press_event");
}

bool SterowanieMysza::on_motion_notify_event(GdkEventMotion* event)
{
    Komunikat("on_motion_notify_event");
}
