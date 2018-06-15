#include <Okno1.h>

Okno1::Okno1()
{
	
}
bool Okno1::Inicjuj()
{
	set_reallocate_redraws(true);
	this->set_size_request(200,200);
	PodlaczenieSygnalow();
    ustawElementyOkna();
	buforTekstu = TextBuffer::create();
	tekst.set_buffer(buforTekstu);
	return true;
}
int Okno1::PodlaczenieSygnalow()
{
    b_ZmienRozmiar.signal_clicked().connect(sigc::mem_fun(*this,&Okno1::NaPrzyciskZmienRozmiar));
	b_UstawTekst.signal_clicked().connect(sigc::mem_fun(*this,&Okno1::WypelnijBufor));
    return 1;
}
void Okno1::ustawElementyOkna()
{
	b_ZmienRozmiar.set_label("zmien rozmiar");
	b_UstawTekst.set_label("ustaw tekst");
	
	add(vBox);
	vBox.pack_start(tekst, Gtk::PACK_SHRINK);
	vBox.pack_start(b_UstawTekst, Gtk::PACK_EXPAND_WIDGET);
    vBox.pack_start(b_ZmienRozmiar, Gtk::PACK_EXPAND_WIDGET);
    show_all();
}
void Okno1::NaPrzyciskZmienRozmiar()
{
	this->set_size_request(300,400);
}
void Okno1::WypelnijBufor()
{
	buforTekstu->set_text("tekst do wyświetlenia");
}
bool Okno1::on_configure_event(GdkEventConfigure* event)
{
	
	WypiszRozmiarOkna(event->height,event->width);
	return false;
}
void Okno1::WypiszRozmiarOkna(int h, int v)
{
	Glib::ustring wymiary;
	char c[10];
	
	itoa(v,c,10);
	wymiary = c;
	itoa(h,c,10);
	wymiary +=" x ";
	wymiary += c;
	buforTekstu->set_text(wymiary);
}
