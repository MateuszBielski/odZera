//#include <gtkmm.h>
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
    app.run(*okno);
    
    return 0;
}
