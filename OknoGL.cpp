#include <OknoGL.h>
#include <SterowanieMysza.h>


OknoGL::OknoGL()
{
    set_reallocate_redraws(true);
}

OknoGL::~OknoGL()
{
    Komunikat("destruktor OknoGL");
}

void OknoGL::Inicjuj()
{
    Komunikat("OknoGL::Inicjuj");
	PrzestawDzialanieButtObsluga("ukryj okno",&OknoGL::Ukryj);
    add(vBox);
    show_all();
}
void OknoGL::UstawIzainstalujPrzyciskW(Gtk::VBox& vbox)
{
    bObslugaTegoOkna.set_label("nowe okno GL");
    vbox.pack_start(bObslugaTegoOkna,Gtk::PACK_SHRINK);
    vbox.show_all();
    connectionButton = bObslugaTegoOkna.signal_clicked().connect(sigc::mem_fun(*this,&OknoGL::Inicjuj));
	this->signal_delete_event().connect(sigc::mem_fun(*this,&OknoGL::on_my_delete_event));
}
bool OknoGL::on_my_delete_event(GdkEventAny* any_event)
{
	PrzestawDzialanieButtObsluga("pokaż okno",&OknoGL::Pokaz);
	this->hide();
}

void OknoGL::Pokaz()
{
	PrzestawDzialanieButtObsluga("ukryj okno",&OknoGL::Ukryj);
	this->show();
}
void OknoGL::Ukryj()
{
	PrzestawDzialanieButtObsluga("pokaż okno",&OknoGL::Pokaz);
	this->hide();
}
void OknoGL::PrzestawDzialanieButtObsluga(const char * etykieta, pfVoid func )
{
	bObslugaTegoOkna.set_label(etykieta);
	connectionButton.disconnect();
	connectionButton = bObslugaTegoOkna.signal_clicked().connect(sigc::mem_fun(*this,func));
}
