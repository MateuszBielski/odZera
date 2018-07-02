#include <OknoGL.h>


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
    ====================
    //zadeklarować jako pole klasy tego okna:
    std::unique_ptr<Sterowanie> sterowanie = std::make_unique<SterowanieMysza_1>();
    
    /*należy sprawdzić  możliwość łatwego umieszczania obiektu sterowanie w różnych klasach okna/ekranu
     *- wypróbować, w której sprawdzi się najlepiej*/
  
    /*klasa sterowanieMysza ma przechowywać:
     * pozycję myszy
     * wskaźnik na obsługiwane okno
     * wykonać obliczenia przy pomocy trackball
     * być może wywołać funkcje okna jak odświeżenie sceny, przerysowanie okna, czy inne*/
    sterowanie->PodlaczenieSygnalow(this);
    PodlaczenieSygnalow(GL::DrawingArea& zOkna)//czy lepiej Window& ?
    {
        //pierwowzory do przerobienia:
        add_events(Gdk::BUTTON1_MOTION_MASK|Gdk::BUTTON_PRESS_MASK);
        signal_button_press_event().connect(sigc::mem_fun(*this,&ScenaGL::on_button_press_event));
        signal_motion_notify_event().connect(sigc::mem_fun(*this,&ScenaGL::on_motion_notify_event));
        //sprawdzić skąd pochodzą te sygnały - wydaje się, że z okna, które ma być obsługiwane
		//można użyć czegoś takiego jak kontener zawierający funkcje i je wywoływać wszystkie.
    }
    ===================
    vBox.pack_start(*pEkranGL);
    show_all();
}
