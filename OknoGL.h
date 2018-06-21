#ifndef OKNOGL_H
#define OKNOGL_H
#include <gtkmm.h>
#include <gtkglmm.h>

using namespace Gtk;
class OknoGL :  public Window//public GL::DrawingArea,
{
public: 
   OknoGL();
    virtual ~OknoGL();
};
#endif