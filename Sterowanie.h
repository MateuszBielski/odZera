#ifndef STEROWANIE_H
#define STEROWANIE_H
#include <gtkmm/widget.h>
#include <Komunikat.h>
#include <OknoGL.h>

class Sterowanie
{
public:
	Sterowanie();
	~Sterowanie();
	virtual int PodlaczanieSygnalow(Gtk::Widget& okno) = 0;
	virtual void PodlaczSygnalPrzeksztalcenieWidoku(EkranGL& ) = 0;
	virtual void PrzeksztalcenieWidoku( bool b, int i) = 0;
protected:
	 void UstawOkno(Gtk::Widget* o);
	 Gtk::Widget* oknoSterowane;
	 
};

#endif // STEROWANIE_H
