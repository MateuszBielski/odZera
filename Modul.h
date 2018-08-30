#ifndef MODUL_H 
#define MODUL_H
#include <Komunikat.h>
#include <Okno1.h>
#include <set> //musi być
#include <bitset>
using namespace Gtk;
class Modul : public std::enable_shared_from_this<Modul>
{
public:
    using spModul = std::shared_ptr<Modul>;
    using MapaStringModul = std::map<std::string,spModul>;
	using ZbiorSpModul = std::set<spModul>;
    Modul();
    ~Modul();
    std::string Nazwa(){return nazwa;};
    void JestemDodanyDo(MapaStringModul* );
    virtual int PolaczZkimPotrzebujeNaPoczatek(){};
    virtual void UstawIzainstalujPrzyciskW(VBox&){};
    void ZablokujPolaczenia();
    void OdblokujPolaczenia();
    virtual void KopiujZinnegoModulu(spModul){};
    void BioreWskaznikDo(spOkno1);
    virtual void WyszukujeIustawiamWskaznikiDoInnychModulow(){};
protected:
    Button bObslugaTegoModulu;
    spOkno1 oknoPodstawowe;
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
    /*============*/
	void DodajCoUzywam(spModul m);
	ZbiorSpModul coUzywam;
	ZbiorSpModul coMnieUzywa;
	void AktualizujPolaczeniaModulowZaleznych();
    /*powyższy fragment powstał na potrzeby przełączania sterowania, później zaczęła działać koncepcja blokowania połączeń*/
    
    //połączenia
    using spConnection = std::shared_ptr<sigc::connection>;
    void DodajDoListyWskaznikPolaczenia(spConnection );
    spConnection UtrwalPolaczenie(sigc::connection&& );
    std::list<spConnection> mojePolaczenia;
    bool zablokujPolaczeniaPrzyStarcie = false;
    
};
#endif
