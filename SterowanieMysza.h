#ifndef STEROWANIEMYSZA_H
#define STEROWANIEMYSZA_H
#include <gtkmm.h>
#include <Sterowanie.h>
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
    virtual int PodlaczanieSygnalow(Gtk::Widget& okno);
	virtual void PodlaczSygnalPrzeksztalcenieWidoku(EkranGL& );
	virtual void PrzeksztalcenieWidoku( bool b, int i);
private:
//	void WyswietlMacierz();
    bool on_button_press_event(GdkEventButton* event);
    bool on_motion_notify_event(GdkEventMotion* event);
    float m_QuatDiff[4];
    float m_BeginX;
    float m_BeginY;
    float m_Pos[3];
    float m_Quat[4];
    float m_DX;
    float m_DY;

};

#endif // STEROWANIEMYSZA_H
