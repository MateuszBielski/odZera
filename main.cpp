//ścieżka do Msys2: cd E:/programowanie/GtkWs/odZera

#include <gtkglmm.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <OknoProba2.h>
#include <Moduly.h>

int main(int argc, char **argv)
{
    Gtk::Main app(argc,argv);
    GL::init(argc, argv);

    spOkno1 okno = std::make_shared<OknoProba2>();
	okno->Inicjuj();
    
    auto moduly = std::make_unique<Moduly>();
    moduly->DolaczDo(okno);
    moduly->WszystkieDodaj();//tutaj definiujemy, które klasy będą używane jako moduły
//    moduly->WszystkieNazwyWyswietl();
    moduly->WszystkiePolaczJakPotrzebuja();
    app.run(*okno);
    
    return 0;
}
