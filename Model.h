#ifndef MODEL_H
#define MODEL_H
#include <gtkglmm.h>
#include <WspolrzedneImacierzeSterowania.h>
#define UTRWAL_MPOS_Z_AKTUALNEJ_MACIERZY 1
#define ZESTAW_FUNKCJI 2
#define PRZELICZ_PUNKTY 4
#define Z_NAZWAMI_MODELI 1



class Model{
public :
    Model();
    virtual ~Model(); 
    
	virtual void Rysuj();
    virtual void RysujZnazwami();
	virtual void RysujGeometrie(){};
    virtual void TransformacjePrzedRysowaniem();
    void UstalM_Pos(float*);//użyte dla światła tylko
    virtual void UstawPolozenieSrodkaModelu(float* zeWskaznika);
    void PokazujWartosci(bool b){pokazujWartosci = b;};//
    void PrzydzielenieNumeru(int n){jestemZaladowanyPodNumerem = n;};
    virtual void PrzeliczPunktyZaktualnejMacierzy();//używane przy dodawaniu do grupy, brakuje dla innych niż kostka
    virtual void WlaczJednorazowoWymienneFunkcje(int jakieFunkcjeFlagi);
    virtual void UtrwalPrzeksztalcenia();
    void UstawPustaDomyslnaFunkcje();
    float* SrodekModelu(){return srodekModelu;};
    
    float * vertexy = 0;
    int ileVertexow = 0;
    
    float * normalne = 0;
    int ileNormalnych = 0; 
    
    std::shared_ptr<WspolrzedneImacierzeSterowania> mojeWspolrzedneImacierzeSterowania;
    bool czyJestemGrupa = false;
    
    template<int flagi>
    void RysujTemplate();
    
    //nie używane, albo mało
    virtual void MacierzaObrotuPrzeliczPunktyIjaWyzeruj();//nie spełniła oczekiwań
    void RysujOstroslup();
    virtual void Wygladzanie(bool){};//do zastanowienia się czy warto przy każdym obiekcie to ustalać
	void UzywajPushMatrix(bool);//--
    void UtrwalMposZaktualnejMacierzy();
    void SrodekUstawZzewnetrznegoAdresu(float *);
protected:
    void UdostepnijBazieVertexyInormalne(float * v,int ileV,float * n,int ileN);
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

    float * kolory = 0;
    int * indeksy = 0;
    int ileIndeksow = 0;
};
using spModel = std::shared_ptr<Model>;
using itLspModel = std::list<spModel>::iterator;

class ModelPusty : public Model{
public:
    ModelPusty(itLspModel dokadWstawiono):tuJestemPelny(dokadWstawiono){};
    virtual ~ModelPusty();
    itLspModel AdresPelnegoObiektu();
//    virtual spModel SprobujPrzywrocic() override;
private:
     itLspModel tuJestemPelny;
};
class Ostroslup : public Model{
  public:
    Ostroslup(){};
    virtual ~Ostroslup(){};
	virtual void RysujGeometrie()  override;
};
class LinieZnormalnych;
class Kostka : public Model{
  friend class LinieZnormalnych;
public:
    Kostka();//domyślnie ustawia środek modelu 0,0,0 i tak oblicza punkty
    Kostka(float * srodekModelu);
    virtual ~Kostka(){};
//	virtual void UstawPolozenieSrodkaModelu(float* zeWskaznika) override;
    virtual void PrzeliczPunktyZaktualnejMacierzy() override;
	void ObliczPunktyKorzystajacZdlugosciIsrodka(float d, float* c);
    virtual void RysujGeometrie() override;
private:
float p[8][3];
float n[6][3];

};
class Czworoscian : public Model{
public:
    Czworoscian();
    Czworoscian(float * srodekModelu);
    virtual ~Czworoscian(){};
    virtual void RysujGeometrie() override;
    void ObliczPunktyKorzystajacZdlugosciIsrodka(float d, float* c);
private:
    float p[4][3];
    float n[4][3];    
};
class TrzyKwadraty : public Model{
  public:
    TrzyKwadraty(){};
    ~TrzyKwadraty(){};
    virtual void RysujGeometrie() override;
};
class LinieZnormalnych : public Model{
public:
    LinieZnormalnych(){};
    virtual ~LinieZnormalnych(){};
    void RysujDla(std::shared_ptr<Model>);
    virtual void RysujGeometrie() override;
private:
    float * normalneModelu;
    
};
class WidokCechModelu : public Model{
public:
    WidokCechModelu();
    virtual ~WidokCechModelu(){};
    void RysujDla(std::shared_ptr<Model>);
    virtual void TransformacjePrzedRysowaniem() override;
    virtual void RysujGeometrie() override;
private:
    Czworoscian znacznik;
    spModel wskazywany = nullptr;
//    float srodekWskazywanegoModelu[3];
    float * zastepczaM_Pos;
    float * zastepczaSrodek;
//    std::shared_ptr<WspolrzedneImacierzeSterowania> przechowanieSterowania;
};
using spLinieN = std::shared_ptr<LinieZnormalnych>;
using spWidokCech = std::shared_ptr<WidokCechModelu>;
#endif