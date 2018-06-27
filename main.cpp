//#include <gtkmm.h>
#include <gtkglmm.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <Okno1.h>
#include <OknoGL.h>

int main(int argc, char **argv)
{
    Gtk::Main app(argc,argv);
    GL::init(argc, argv);
    Okno1 okno;
    okno.Inicjuj();
    app.run(okno);
    
    return 0;
}
