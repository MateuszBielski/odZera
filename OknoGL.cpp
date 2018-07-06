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
    pEkranGL = std::make_unique<EkranRysujacy>();
//    pEkranGL->set_size_request(200,200);
    pEkranGL->Inicjuj();
//    ====================
    //zadeklarować jako pole klasy tego okna:
    sterowanie = std::make_unique<SterowanieMysza>();
    
    
  
    /
    sterowanie->PodlaczenieSygnalow(this);
    //albo
    //sterowanie->PodlaczenieSygnalow(pEkranGL);
//    ===================
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
