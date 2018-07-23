#ifndef MODUL_H 
#define MODUL_H
#include <Komunikat.h>
class Modul
{
public:
    using spModul = std::shared_ptr<Modul>;
    using MapaStringModul = std::map<std::string,spModul>;
	
    Modul();
    ~Modul();
    std::string Nazwa(){return nazwa;};
    void JestemDodanyDo(MapaStringModul* );
    virtual int PolaczZkimPorzebujeNaPoczatek(){};
protected:
    std::string nazwa;
	
	MapaStringModul* mapaZmodulami;
    spModul WyszukajWDodanychModulach(std::string);
    template<typename T>
    auto& WyszkajWmodulachIzwrocWlasciwyTyp(std::string rodzajModulu);//--nie działa chociaż się kompiluje
    
};

template<typename T>
std::shared_ptr<T> WyszukajWModulach_Ptr(std::string rodzajModulu, Modul::MapaStringModul& moduly);
template<typename T>
T& WyszukajWModulach_Ref(std::string, Modul::MapaStringModul& );
#endif