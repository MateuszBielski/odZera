#ifndef MODEL_H
#define MODEL_H
#include <gtkglmm.h>
#include <WspolrzedneImacierzeSterowania.h>
#define UTRWAL_MPOS_Z_AKTUALNEJ_MACIERZY 1
#define ZESTAW_FUNKCJI 2
#define PRZELICZ_PUNKTY 4



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
    virtual void UstawPolozenieSrodkaModelu(float* zeWskaznika);
	void UzywajPushMatrix(bool);//--
    void PokazujWartosci(bool b){pokazujWartosci = b;};//
    void PrzydzielenieNumeru(int n){jestemZaladowanyPodNumerem = n;};
//    virtual spModel SprobujPrzywrocic(){};
    void UtrwalMposZaktualnejMacierzy();
    virtual void PrzeliczPunktyZaktualnejMacierzy();
    virtual void WlaczJednorazowoWymienneFunkcje(int jakieFunkcjeFlagi);
    void UstawPustaDomyslnaFunkcje();
    float* SrodekModelu(){return srodekModelu;};
    
    std::shared_ptr<WspolrzedneImacierzeSterowania> mojeWspolrzedneImacierzeSterowania;
    bool czyJestemGrupa = false;
    float * normalne = 0;
    int ileNormalnych = 0;
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
    int ileVertexow = 0;
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
    void RysujGeometrieStare();
	void RysujGeometrieStare2();
private:
float p[8][3];
float n[6][3];

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
using spLinieN = std::shared_ptr<LinieZnormalnych>;
#endif