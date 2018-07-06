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
    virtual int PodlaczanieSygnalow(upOknoGL& okno) = 0;
protected:
	 void UstawOkno(Gtk::Widget* o);
	 Gtk::Widget* oknoSterowane;
	 
};

#endif // STEROWANIE_H
