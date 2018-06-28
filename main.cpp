//#include <gtkmm.h>
#include <gtkglmm.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <OknoProby.h>

int main(int argc, char **argv)
{
    Gtk::Main app(argc,argv);
    GL::init(argc, argv);
//    Okno1 okno;
    std::unique_ptr<Okno1> okno = std::make_unique<OknoProby>();
	okno->Inicjuj();
    app.run(*okno);
    
    return 0;
}
