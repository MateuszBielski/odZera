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
    b_UruchomWatek.signal_clicked().connect(sigc::mem_fun(*this,&Okno1::NowyWatek));
    return 1;
}
void Okno1::ustawElementyOkna()
{
	b_ZmienRozmiar.set_label("zmien rozmiar");
	b_UstawTekst.set_label("ustaw tekst");
    b_UruchomWatek.set_label("nowy wątek");
	
	add(vBox);
	vBox.pack_start(tekst, Gtk::PACK_SHRINK);
	vBox.pack_start(b_UstawTekst, Gtk::PACK_EXPAND_WIDGET);
    vBox.pack_start(b_ZmienRozmiar, Gtk::PACK_EXPAND_WIDGET);
    vBox.pack_start(b_UruchomWatek, Gtk::PACK_SHRINK);
    show_all();
}
void Okno1::NaPrzyciskZmienRozmiar()
{
	this->set_size_request(300,400);
	PodlaczenieSygnalow();
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
void Okno1::WypiszRozmiarOkna(int h, int w)
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
void Okno1::NowyWatek()
{
//    std::thread([=]{PokazLiczenie();});
    buforTekstu->set_text("rozpoczęcie nowego wątku");
    watek = new std::thread([=]{PokazLiczenie();});
}
void Okno1::PokazLiczenie()
{
	
//    using namespace std::literals;
    Glib::ustring sLicznik;
	char c[10];
	g_print("funkcja w drugim wątku");
    while(licznik < 20){
        std::this_thread::sleep_for(std::chrono::seconds(1));
        sprintf(c,"%d",licznik++);
        sLicznik = c;
//        g_print(" %d",licznik);
        buforTekstu->set_text(sLicznik);
    }
}
void PokazLiczenieObiektu(Okno1* o)
{
    o->PokazLiczenie();
}
