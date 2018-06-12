#include <gtkmm.h>
#include <Okno1.h>

int main(int argc, char **argv)
{
	Gtk::Main app(argc,argv);
    Okno1 okno;
    app.run(okno);
    return 0;
}
