#ifndef OKNOGL_H
#define OKNOGL_H
#include <EkranRysujacy.h>



using namespace Gtk;

class OknoGL :  public Window//public GL::DrawingArea,
{
public: 
   OknoGL();
    virtual ~OknoGL();
    void Inicjuj();
    void UstawIzainstalujPrzyciskW(VBox&);
	std::shared_ptr<EkranGL> WskEkranGL();
    EkranGL& RefEkranGL();
private:
    std::shared_ptr<EkranGL> pEkranGL;
    VBox vBox;
    Button b_NoweOknoGL;
};
using upOknoGL = std::unique_ptr<OknoGL>;
#endif