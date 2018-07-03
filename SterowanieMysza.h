#ifndef STEROWANIEMYSZA_H
#define STEROWANIEMYSZA_H
#include <gtkmm.h>
/*klasa sterowanieMysza ma przechowywać:
 * pozycję myszy
 * wskaźnik na obsługiwane okno
 * wykonać obliczenia przy pomocy trackball
 * być może wywołać funkcje okna jak odświeżenie sceny, przerysowanie okna, czy inne*/

class SterowanieMysza : public Sterowanie
{
public:
	SterowanieMysza();
	~SterowanieMysza();
    virtual int PodlaczanieSygnalow(Widget& okno);
private:
    bool on_button_press_event(GdkEventButton* event);
    bool on_motion_notify_event(GdkEventMotion* event);

};

#endif // STEROWANIEMYSZA_H
