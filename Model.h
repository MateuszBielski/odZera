#ifndef MODEL_H
#define MODEL_H
#include <gtkglmm.h>
#include <WspolrzedneImacierzeSterowania.h>
#include <FunkcjeIstruktury.h>
#define UTRWAL_MPOS_Z_AKTUALNEJ_MACIERZY 1
#define ZESTAW_FUNKCJI 2
#define UTRWAL_PUNKTY_NORMALNE_SRODEK 4
#define UTRWAL_SRODEK 8
#define Z_NAZWAMI_MODELI 1
#define Z_WIDOCZNYMI_PUNKTAMI 2



class Model{
public :
    Model();
    virtual ~Model(); 
    
	virtual void Rysuj();
    virtual void RysujZnazwami();
    virtual void RysujZWidocznymiPunktami();
	virtual void RysujGeometrie(){};
    virtual void RysujWidocznePunkty();
    virtual void RysujPunktyZnazwami();
    virtual void TransformacjePrzedRysowaniem();
    void UstalM_Pos(float*);//użyte dla światła tylko
    virtual void UstawPolozenieSrodkaModelu(float* zeWskaznika);
    void PokazujWartosci(bool b){pokazujWartosci = b;};//
    void PrzydzielenieNumeru(int n){jestemZaladowanyPodNumerem = n;};
    virtual void PrzeliczPunktyZaktualnejMacierzy();//używane przy dodawaniu do grupy, brakuje dla innych niż kostka
    void UtrwalSrodekZaktualnejMacierzy();
    virtual void WlaczJednorazowoWymienneFunkcje(int jakieFunkcjeFlagi);
    virtual void UtrwalPrzeksztalcenia();
    void UstawPustaDomyslnaFunkcje();
    float* SrodekModelu(){return srodekModelu;};
    
    float * vertexy = 0;
    int ileVertexow = 0;
    
    float * normalne = 0;
    int ileNormalnych = 0; 
	
	unsigned short * indeksyNaroznikow = 0;
    unsigned short ileNaroznikowSciany = 0;
    
    std::shared_ptr<WspolrzedneImacierzeSterowania> mojeWspolrzedneImacierzeSterowania;
    bool czyJestemGrupa = false;
    
    template<int flagi>
    void RysujTemplate();
    template<int flagi,int>
    void RysujGeometrieTemplate();
    
    //nie używane, albo mało
    virtual void MacierzaObrotuPrzeliczPunktyIjaWyzeruj();//nie spełniła oczekiwań
    void RysujOstroslup();
    virtual void Wygladzanie(bool){};//do zastanowienia się czy warto przy każdym obiekcie to ustalać
	void UzywajPushMatrix(bool);//--
    void UtrwalMposZaktualnejMacierzy();//wcale nie używana
    void SrodekUstawZzewnetrznegoAdresu(float *);
protected:
    void UdostepnijBazieVertexyInormalne(float * v,int ileV,float * n,int ileN);
	void UdostepnijBazieIndeksyWierzcholkow(unsigned short *, unsigned short);
    using Ptr_F_void_void = void(Model::*)();
    Ptr_F_void_void FunkcjaWymienna = &Model::DomyslnaWymiennaFunkcja;
    void DomyslnaWymiennaFunkcja(){};
	
	//zestaw różnych funkcji - experymentalnie
//	using kontenerFunkcji = std::vector<std::function<void(Model&)>>;
	using kontenerFunkcji = std::vector<Ptr_F_void_void>;
	kontenerFunkcji FunkcjeWymienne;
	void F_pierwsza();
	void F_druga();
	void F_trzecia();
	void WykonajWszystkieFunkcjeZestawu();
//	std::function<int(MyValue&)> fifth = &MyValue::fifth;
	
    int jestemZaladowanyPodNumerem = -1;
    
    bool czyPushMatrix = true;
    bool pokazujWartosci = false;
	float* obrotIndywidualny = nullptr;
    float* srodekModelu;//pierwotnie wskazuje na poniższą tablicę 
    float srodekModeluTab[3];

    float kolor[3];
    
};
using spModel = std::shared_ptr<Model>;
using itLspModel = std::list<spModel>::iterator;


#include "ModelTemplate.cpp"
#endif