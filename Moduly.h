#ifndef MODULY_H
#define MODULY_H
#include <Okno1.h>
#include <OknoGL.h>
#include <SterowanieMysza.h>

class Moduly
{
public:
    Moduly();
    ~Moduly();
    bool DolaczDo(spOkno1);
    int Uruchom();
private:
    spOkno1 oknoGlowne;
    
    std::unique_ptr<OknoGL> oknoGL;
    
    /*należy sprawdzić  możliwość łatwego umieszczania obiektu sterowanie w różnych klasach okna/ekranu
     *- wypróbować, w której sprawdzi się najlepiej*/
    std::unique_ptr<Sterowanie> sterowanie;
    
};
#endif