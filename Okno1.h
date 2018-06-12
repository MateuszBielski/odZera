#ifndef OKNO1_H
#define OKNO1_H
#include <gtkmm.h> 
using namespace Gtk;
class Okno1 : public Window
{
public:
    Okno1();
    virtual ~Okno1(){};
protected:
    VBox vBox;
    Button b_ZmienRozmiar;
};
#endif
