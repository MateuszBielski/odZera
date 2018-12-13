#ifndef STEROWANIEMYSZA_H
#define STEROWANIEMYSZA_H
#include <gtkmm.h>

#include <Sterowanie.h>
#include <EkranRysujacy.h>
#include <FunkcjeIstruktury.h>
#include <ModyfikacjaPunktow.h>

class SterowanieMysza : public Sterowanie
{
public:
	SterowanieMysza();
	virtual ~SterowanieMysza();
    virtual int PodlaczanieSygnalow(Gtk::Widget& okno);
    void PrzejmijSterowanieOd(SterowanieMysza &);
    
protected:
    bool on_button_press_event(GdkEventButton* event);
    bool on_motion_notify_event(GdkEventMotion* event);
    bool on_my_scroll_event(GdkEventScroll* scroll_event);
    
    virtual void V_NaPrzyciskMyszaZmienne(GdkEventButton* event) = 0;
    virtual void V_NaRuchMyszaZmienne(GdkEventMotion* event) = 0;
    
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
    using spRenderowanie = std::shared_ptr<Renderowanie1>;
	spRenderowanie renderowanie;
    using spZarzadzanie = std::shared_ptr<ZarzadzanieObiektami>;
    spZarzadzanie zarzadzanieObiektami;
    int ix,iy;
    float w,h,x,y;
    
};
class SterowanieMyszaVar_1 : public SterowanieMysza
{
public:
    SterowanieMyszaVar_1();
    ~SterowanieMyszaVar_1(){};
    virtual void WyszukujeIustawiamWskaznikiDoInnychModulow() override;
private:
    virtual void V_NaPrzyciskMyszaZmienne(GdkEventButton* event) override;
    virtual void V_NaRuchMyszaZmienne(GdkEventMotion* event) override;
    
};
class SterowanieMyszaVar_2 : public SterowanieMysza
{
public:
    SterowanieMyszaVar_2();
    ~SterowanieMyszaVar_2(){};
    virtual void WyszukujeIustawiamWskaznikiDoInnychModulow() override;
private:
    ModyfikacjaPunktow modyfikacjaPunktow;
    
    virtual void V_NaPrzyciskMyszaZmienne(GdkEventButton* event) override ;
    virtual void V_NaRuchMyszaZmienne(GdkEventMotion* event) override ;
    void WybieraniePunktu(unsigned int&);
    
};
#endif // STEROWANIEMYSZA_H
