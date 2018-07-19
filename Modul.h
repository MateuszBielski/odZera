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
    /*template<typename T>
    T& WyszkajWmodulachIzwrocWlasciwyTyp(std::string rodzajModulu);//--nie działa chociaż się kompiluje*/
    
};
#endif