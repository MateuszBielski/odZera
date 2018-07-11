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
    
    add(vBox);
    show_all();
}
void OknoGL::UstawIzainstalujPrzyciskW(Gtk::VBox& vbox)
{
    b_NoweOknoGL.set_label("nowe okno GL");
    vbox.pack_start(b_NoweOknoGL,Gtk::PACK_SHRINK);
    vbox.show_all();
    b_NoweOknoGL.signal_clicked().connect(sigc::mem_fun(*this,&OknoGL::Inicjuj));
}
bool OknoGL::on_my_delete_event(GdkEventAny* any_event)
{
	Komunikat("OknoGL::on_my_delete_event");
}
