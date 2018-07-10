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
    pEkranGL = std::make_shared<EkranRysujacy>();
    pEkranGL->Inicjuj();
    vBox.pack_start(*pEkranGL);
    show_all();
}
void OknoGL::UstawIzainstalujPrzyciskW(Gtk::VBox& vbox)
{
    b_NoweOknoGL.set_label("nowe okno GL");
    vbox.pack_start(b_NoweOknoGL,Gtk::PACK_SHRINK);
    vbox.show_all();
    b_NoweOknoGL.signal_clicked().connect(sigc::mem_fun(*this,&OknoGL::Inicjuj));
}
std::shared_ptr<EkranGL> OknoGL::WskEkranGL()
{
	return pEkranGL;
}
EkranGL& OknoGL::RefEkranGL()
{
	return *pEkranGL;
}
