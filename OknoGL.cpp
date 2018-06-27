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
    pEkranGL = std::make_unique<EkranGL>();
    pEkranGL->set_size_request(200,200);
    pEkranGL->Inicjuj();
    vBox.pack_start(*pEkranGL);
    show_all();
}
