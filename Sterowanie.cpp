#include "Sterowanie.h"

Sterowanie::Sterowanie()
{
	nazwa = "sterowanie";
}

Sterowanie::~Sterowanie()
{
}
int Sterowanie::PodlaczanieSygnalow(Gtk::Widget& okno)
{
	int ileSygnalow = 0;
	return ileSygnalow;
}

void Sterowanie::UstawOkno(Gtk::Widget* o)
{
	oknoSterowane = o;
}
