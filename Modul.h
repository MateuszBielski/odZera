#ifndef MODUL_H 
#define MODUL_H
#include <Komunikat.h>
class Moduly;
class Modul
{
public:
    Modul();
    ~Modul();
    std::string Nazwa(){return nazwa;};
    void JestemDodanyDo(Modul * m){tuJestemDodany = m;};
    
protected:
    std::string nazwa;
    Moduly* tuJestemDodany;
    
};
#endif