#ifndef MODUL_H 
#define MODUL_H
#include <Komunikat.h>
class Modul
{
public:
    using spModul = std::shared_ptr<Modul>;
    using MapaStringModul = std::map<std::string,spModul>;
	using ListaSpModul = std::list<spModul>;
	
    Modul();
    ~Modul();
    std::string Nazwa(){return nazwa;};
    void JestemDodanyDo(MapaStringModul* );
    virtual int PolaczZkimPorzebujeNaPoczatek(){};
protected:
    std::string nazwa;
	MapaStringModul* mapaZmodulami;
    template<typename T>
    std::shared_ptr<T> Ptr_WyszukajWModulach(std::string rodzajModulu)
    {
        return std::dynamic_pointer_cast<T>((*mapaZmodulami)[rodzajModulu]);
    }
    template<typename T>
    T& Ref_WyszukajWModulach(std::string rodzajModulu)
    {
        return *(Ptr_WyszukajWModulach<T>(rodzajModulu));
    }
    
	DodajCoUzywam(spModul m);
	ListaSpModul coUzywam;
	ListaSpModul coMnieUzywa;
	AktualizujPolaczeniaModulowZaleznych();
};
#endif