#ifndef PRZESUWANIEWIDOKU_H
#define PRZESUWANIEWIDOKU_H
#include <gtkmm.h>
#include <Sterowanie.h>
class PrzesuwanieWidoku : public Sterowanie
{
public:
	PrzesuwanieWidoku();
	~PrzesuwanieWidoku();
    int PodlaczanieSygnalow(Gtk::Widget& );
    virtual void PodlaczSygnalPrzeksztalcenieWidoku(EkranGL& );
	virtual void PrzeksztalcenieWidoku( bool b, int i);
private:
    bool on_button_press_event(GdkEventButton* event);
    bool on_motion_notify_event(GdkEventMotion* event);
};

#endif // PRZESUWANIEWIDOKU_H
