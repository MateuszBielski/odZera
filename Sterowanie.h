#ifndef STEROWANIE_H
#define STEROWANIE_H
#include <gtkmm/widget.h>
#include <Komunikat.h>
#include <Modul.h>
#include <EkranGL.h>
#include <WspolrzedneImacierzeSterowania.h> 

#define CALYM_WIDOKIEM 1
#define WYBRANYM_OBIEKTEM 2

class Sterowanie : public Modul
{
public:
	Sterowanie();
	virtual ~Sterowanie();
	virtual int PodlaczanieSygnalow(Gtk::Widget& okno) = 0;
    virtual int PolaczZkimPotrzebujeNaPoczatek();
	void Steruj(int czym);
    virtual void KopiujZinnegoModulu(spModul) override;
protected:
	void UstawOkno(Gtk::Widget* o);
	Gtk::Widget* oknoSterowane;
    void KopiujParametrySterowania(Sterowanie& );
    
	WspolrzedneImacierzeSterowania calegoWidoku;//, wybranegoObiektu;
	WspolrzedneImacierzeSterowania * wybranegoObiektu;
    WspolrzedneImacierzeSterowania * aktualneSterowanie;
};

#endif // STEROWANIE_H
