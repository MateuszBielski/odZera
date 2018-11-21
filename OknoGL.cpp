#include <OknoGL.h>
#include <SterowanieMysza.h>


OknoGL::OknoGL()
{
    Komunikat("OknoGL");
	set_reallocate_redraws(true);//czy potrzebne?
	nazwa = "oknoGL";
}

OknoGL::~OknoGL()
{
    Komunikat("~OknoGL");
}
int OknoGL::PolaczZkimPotrzebujeNaPoczatek()
{
	UstawIzainstalujPrzyciskW(oknoPodstawowe->refVBox());
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
    bObslugaTegoModulu.set_label("nowe okno GL");
    vbox.pack_start(bObslugaTegoModulu,Gtk::PACK_SHRINK);
    vbox.show_all();
    connectionButton = UtrwalPolaczenie(bObslugaTegoModulu.signal_clicked().connect(sigc::mem_fun(*this,&OknoGL::Inicjuj)));
    DodajDoListyWskaznikPolaczenia(connectionButton);
	DodajDoListyWskaznikPolaczenia(
        UtrwalPolaczenie(this->signal_delete_event().connect(sigc::mem_fun(*this,&OknoGL::on_my_delete_event))));
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
	bObslugaTegoModulu.set_label(etykieta);
	connectionButton->disconnect();
	*connectionButton = bObslugaTegoModulu.signal_clicked().connect(sigc::mem_fun(*this,func));
}
