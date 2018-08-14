#ifndef MODUL_H 
#define MODUL_H
#include <Komunikat.h>
#include <set> //musi być
using namespace Gtk;
class Modul : public std::enable_shared_from_this<Modul>
{
public:
    using spModul = std::shared_ptr<Modul>;
    using MapaStringModul = std::map<std::string,spModul>;
//	using ListaSpModul = std::list<spModul>;
	using ZbiorSpModul = std::set<spModul>;
    Modul();
    ~Modul();
    std::string Nazwa(){return nazwa;};
    void JestemDodanyDo(MapaStringModul* );
    virtual int PolaczZkimPorzebujeNaPoczatek(){};
    virtual void UstawIzainstalujPrzyciskW(VBox&){};
protected:
    Button bObslugaTegoModulu;
    std::string nazwa;
	MapaStringModul* mapaZmodulami;
    bool CzyJestModul(std::string);
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
    
	void DodajCoUzywam(spModul m);
	ZbiorSpModul coUzywam;
	ZbiorSpModul coMnieUzywa;
	void AktualizujPolaczeniaModulowZaleznych();
};
#endif