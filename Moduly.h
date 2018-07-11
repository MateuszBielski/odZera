#ifndef MODULY_H
#define MODULY_H
#include <Okno1.h>
#include <OknoGL.h>
#include <SterowanieMysza.h>
#include <Renderowanie.h>
#include <client.h>
#include <server.h>
class Moduly
{
public:
    Moduly();
    ~Moduly();
    bool DolaczDo(spOkno1);
    int Uruchom();
    
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