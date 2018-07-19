#ifndef MODUL_H 
#define MODUL_H
#include <Komunikat.h>
//class Moduly;
class Modul
{
public:
	using spModul = std::shared_ptr<Modul>;
    using MapaStringModul = std::map<std::string,spModul>;
	
    Modul();
    ~Modul();
    std::string Nazwa(){return nazwa;};
//    void JestemDodanyDo(Moduly * m){tuJestemDodanyModuly = m;};
    void JestemDodanyDo(MapaStringModul* );
    virtual int PolaczZkimPorzebujeNaPoczatek(){};
protected:
    std::string nazwa;
//    Moduly* tuJestemDodanyModuly;
	
	MapaStringModul* mapaZmodulami;
    std::shared_ptr<Modul> WyszukajWDodanychModulach(std::string);
    template<typename T>
    T& WyszkajWmodulachIzwrocWlasciwyTyp(std::string rodzajModulu);//--nie działa chociaż się kompiluje
    
};
#endif