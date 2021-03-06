#include "OknoProby.h"

OknoProby::OknoProby()
{
}

OknoProby::~OknoProby()
{
}

void OknoProby::NowyWatek()
{
	buforTekstu->set_text("rozpoczęcie nowego wątku");
    watek = new std::thread([=]{PokazLiczenie();});
}

int OknoProby::PodlaczenieSygnalow()
{
	b_ZmienRozmiar.signal_clicked().connect(sigc::mem_fun(*this,&OknoProby::NaPrzyciskZmienRozmiar));
	b_UstawTekst.signal_clicked().connect(sigc::mem_fun(*this,&OknoProby::WypelnijBufor));
    b_UruchomWatek.signal_clicked().connect(sigc::mem_fun(*this,&OknoProby::NowyWatek));
    b_NoweOknoGL.signal_clicked().connect(sigc::mem_fun(*this,&OknoProby::NoweOknoGL));
    return 1;
}

void OknoProby::ustawElementyOkna()
{
	b_ZmienRozmiar.set_label("zmien rozmiar");
	b_UstawTekst.set_label("ustaw tekst");
    b_UruchomWatek.set_label("nowy wątek");
    b_NoweOknoGL.set_label("nowe okno GL");
	
	add(vBox);
	vBox.pack_start(tekst, Gtk::PACK_SHRINK);
	vBox.pack_start(b_UstawTekst, Gtk::PACK_EXPAND_WIDGET);
    vBox.pack_start(b_ZmienRozmiar, Gtk::PACK_EXPAND_WIDGET);
    vBox.pack_start(b_UruchomWatek, Gtk::PACK_SHRINK);
    vBox.pack_start(b_NoweOknoGL, Gtk::PACK_SHRINK);
    show_all();
}

void OknoProby::NaPrzyciskZmienRozmiar()
{
	this->set_size_request(300,400);
	PodlaczenieSygnalow();
}

void OknoProby::NoweOknoGL()
{
	oknoGL = std::make_unique<OknoGL>();
    oknoGL->Inicjuj();
}

void OknoProby::PokazLiczenie()
{
	
    Glib::ustring sLicznik;
	char c[10];
	Komunikat("funkcja w drugim wątku");
    while(licznik < 20){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        sprintf(c,"%d",licznik++);
        sLicznik = c;
//        Komunikat(" %d",licznik);
        buforTekstu->set_text(sLicznik);
    }
}

void OknoProby::WypiszRozmiarOkna(int h, int w)
{
	Glib::ustring wymiary;
	char c[10];
	
	/*
	itoa(v,c,10);
	wymiary = c;
	itoa(h,c,10);
	wymiary +=" x ";
	wymiary += c;*/
	sprintf(c,"%d x %d",w,h);
	wymiary = c;
	buforTekstu->set_text(wymiary);
}

void OknoProby::WypelnijBufor()
{
	buforTekstu->set_text("tekst do wyświetlenia");
}
bool OknoProby::on_configure_event(GdkEventConfigure* event)
{
	WypiszRozmiarOkna(event->height,event->width);
	return false;
}
void OknoProby::UstawieniaKlasyDziedziczacej()
{
	buforTekstu = TextBuffer::create();
	tekst.set_buffer(buforTekstu);
}
