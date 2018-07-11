#ifndef MODULY_H
#define MODULY_H
#include <Okno1.h>
#include <OknoGL.h>
#include <SterowanieMysza.h>
#include <Renderowanie.h>
class Moduly
{
public:
    Moduly();
    ~Moduly();
    bool DolaczDo(spOkno1);
    int Uruchom();
	bool on_my_delete_event(GdkEventAny* any_event);
    
private:
    spOkno1 oknoGlowne;
    
    upOknoGL oknoGL;
    
    /*należy sprawdzić  możliwość łatwego umieszczania obiektu sterowanie w różnych klasach okna/ekranu
     *- wypróbować, w której sprawdzi się najlepiej*/
    std::unique_ptr<Sterowanie> sterowanie;
	std::shared_ptr<Renderowanie> renderowanie;
    std::shared_ptr<EkranGL> pEkranGL;
    
};
#endif