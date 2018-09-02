#ifndef STEROWANIE_H
#define STEROWANIE_H
#include <gtkmm/widget.h>
#include <Komunikat.h>
#include <Modul.h>
#include <EkranGL.h>
#include <WspolrzedneImacierzeSterowania.h> 

class Sterowanie : public Modul
{
public:
	Sterowanie();
	~Sterowanie();
	virtual int PodlaczanieSygnalow(Gtk::Widget& okno) = 0;
    virtual int PolaczZkimPotrzebujeNaPoczatek();
    virtual void KopiujZinnegoModulu(spModul) override;
protected:
	void UstawOkno(Gtk::Widget* o);
	Gtk::Widget* oknoSterowane;
    void KopiujParametrySterowania(Sterowanie& );
    
	WspolrzedneImacierzeSterowania calegoWidoku, wybranegoObiektu;
	WspolrzedneImacierzeSterowania * aktualneSterowanie;
};

#endif // STEROWANIE_H
