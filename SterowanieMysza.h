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
    bool on_button_press_eventNowe(GdkEventButton* event);
    bool on_motion_notify_event(GdkEventMotion* event);
    bool on_motion_notify_eventNowe(GdkEventMotion* event);    
    bool on_my_scroll_event(GdkEventScroll* scroll_event);
    void PobierzWspolrzedne_ix_iy(gdouble, gdouble);
    void PobierzWspolrzedneWruchu_ix_iy_x_y(gdouble, gdouble);
    void OdczytajWymiaryOkna();
    void KorekcjaOsiObrotuWybranegoModelu();
    void WybieranieModelu(unsigned int&);
    void SwiatloPozycjaOdczytaj();
    void SwiatloPozycjaZmien();
    void ObracajAktualneSterowanie();
    void PrzesuwajAktualnieSterowane();
    void OdswiezWidok();
    using spEkranRysujacy = std::shared_ptr<EkranRysujacy>;
    spEkranRysujacy ekran;
//	using spRenderowanie = std::shared_ptr<Renderowanie>;
    using spRenderowanie = std::shared_ptr<Renderowanie1>;
	spRenderowanie renderowanie;
    using spZarzadzanie = std::shared_ptr<ZarzadzanieObiektami>;
    spZarzadzanie zarzadzanieObiektami;
    int ix,iy;
    float w,h,x,y;
    
};

#endif // STEROWANIEMYSZA_H
