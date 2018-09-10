#ifndef STEROWANIEMYSZA_H
#define STEROWANIEMYSZA_H
#include <gtkmm.h>

#include <Sterowanie.h>
#include <EkranRysujacy.h>
#include <FunkcjeIstruktury.h>

class SterowanieMysza : public Sterowanie
{
public:
	SterowanieMysza();
	~SterowanieMysza();
    virtual int PodlaczanieSygnalow(Gtk::Widget& okno);
    virtual void WyszukujeIustawiamWskaznikiDoInnychModulow() override;
    
    
private:
    bool on_button_press_event(GdkEventButton* event);
    bool on_motion_notify_event(GdkEventMotion* event);
    bool on_my_scroll_event(GdkEventScroll* scroll_event);
    void KorekcjaOsiObrotuWybranegoModelu();
    

    using spEkranRysujacy = std::shared_ptr<EkranRysujacy>;
    spEkranRysujacy ekran;
	using spRenderowanie = std::shared_ptr<Renderowanie>;
	spRenderowanie renderowanie;
    
};

#endif // STEROWANIEMYSZA_H
