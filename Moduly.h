#ifndef MODULY_H
#define MODULY_H
#include <Okno1.h>
#include <OknoGL.h>

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
    
};
#endif