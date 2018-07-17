#ifndef STEROWANIE_H
#define STEROWANIE_H
#include <gtkmm/widget.h>
#include <Komunikat.h>
#include <OknoGL.h> //potrzebne?
#include <Modul.h>

class Sterowanie : public Modul
{
public:
	Sterowanie();
	~Sterowanie();
	virtual int PodlaczanieSygnalow(Gtk::Widget& okno) = 0;
    virtual int PolaczZkimPorzebujeNaPoczatek();
	virtual void PodlaczSygnalPrzeksztalcenieWidoku(EkranGL& ) = 0;
	virtual void PrzeksztalcenieWidoku( bool b, int i) = 0;
//	void PrzeksztalcenieInterfejs();
protected:
	 void UstawOkno(Gtk::Widget* o);
	 Gtk::Widget* oknoSterowane;
	 
};

#endif // STEROWANIE_H
