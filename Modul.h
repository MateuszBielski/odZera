#ifndef MODUL_H 
#define MODUL_H
#include <Komunikat.h>
class Moduly;
class Modul
{
public:
	using MapaStrModul = std::map<std::string,Modul>;
	
    Modul();
    ~Modul();
    std::string Nazwa(){return nazwa;};
    void JestemDodanyDo(Moduly * m){tuJestemDodanyModuly = m;};
    void JestemDodanyDo(MapaStrModul* );
protected:
    std::string nazwa;
    Moduly* tuJestemDodanyModuly;
	
	MapaStrModul* mapaZmodulami;
    
};
#endif