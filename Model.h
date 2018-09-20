#ifndef MODEL_H
#define MODEL_H
#include <gtkglmm.h>
#include <WspolrzedneImacierzeSterowania.h>


class Model{
public :
    Model();
    virtual ~Model(); 
    void RysujOstroslup();
	virtual void Rysuj();
	virtual void RysujGeometrie(){};
    virtual void Wygladzanie(bool){};//do zastanowienia się czy warto przy każdym obiekcie to ustalać
    void UstalM_Pos(float*);
    void UstawPolozenieSrodkaModelu(float* zeWskaznika);
	void UzywajPushMatrix(bool);//--
    void PokazujWartosci(bool b){pokazujWartosci = b;};
    void JestemZaladowanyPodNumerem(int n){jestemZaladowanyPodNumerem = n;};
    
    std::shared_ptr<WspolrzedneImacierzeSterowania> mojeWspolrzedneImacierzeSterowania;
protected:
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
    void RysujGeometrieNieUdane();
    void RysujGeometrieNowe();
};


#endif