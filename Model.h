#ifndef MODEL_H
#define MODEL_H
#include <gtkglmm.h>
#include <WspolrzedneImacierzeSterowania.h>
#define UTRWAL_MPOS_Z_AKTUALNEJ_MACIERZY 1
#define ZESTAW_FUNKCJI 2



class Model{
public :
    Model();
    virtual ~Model(); 
    void RysujOstroslup();
	virtual void Rysuj();
    virtual void RysujZnazwami();
	virtual void RysujGeometrie(){};
    virtual void TransformacjePrzedRysowaniem();
    virtual void Wygladzanie(bool){};//do zastanowienia się czy warto przy każdym obiekcie to ustalać
    void UstalM_Pos(float*);
    void UstawPolozenieSrodkaModelu(float* zeWskaznika);
	void UzywajPushMatrix(bool);//--
    void PokazujWartosci(bool b){pokazujWartosci = b;};
    void PrzydzielenieNumeru(int n){jestemZaladowanyPodNumerem = n;};
    void UtrwalMposZaktualnejMacierzy();
    void WlaczJednorazowoWymienneFunkcje(int jakieFunkcjeFlagi);
    
    
    std::shared_ptr<WspolrzedneImacierzeSterowania> mojeWspolrzedneImacierzeSterowania;
    bool czyJestemGrupa = false;
protected:
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
    float srodekModelu[3];
    
	float * vertexy = 0;
    int * indeksy = 0;
    float * kolory = 0;
    float * normalne = 0;
    int ileVertexow = 0;
    int ileIndeksow = 0;
};
class ModelPusty : public Model{
    
};
class Ostroslup : public Model{
  public:
    Ostroslup(){};
    virtual ~Ostroslup(){};
	virtual void RysujGeometrie()  override;
};
class Kostka : public Model{
  public:
    Kostka(){};
    virtual ~Kostka(){};
    virtual void RysujGeometrie() override;
//    void RysujGeometrieNieUdane();
    void RysujGeometrieStare();
};
class TrzyKwadraty : public Model{
  public:
    TrzyKwadraty(){};
    ~TrzyKwadraty(){};
    virtual void RysujGeometrie() override;
};

#endif