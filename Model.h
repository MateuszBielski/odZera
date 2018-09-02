#ifndef MODEL_H
#define MODEL_H
#include <gtkglmm.h>


class Model{
public :
    Model();
    virtual ~Model(); 
    void RysujOstroslup();
	virtual void Rysuj();
	virtual void RysujGeometrie(){};
    virtual void Wygladzanie(bool){};//do zastanowienia się czy warto przy każdym obiekcie to ustalać
    void UstalPolozenie3f(float*);
	void UzywajPushMatrix(bool);//do usunięcia
protected:
    float polozenie3f[3];
    bool czyPushMatrix = false;//do usunięcia
	float* mnozeniePrzezMacierz = nullptr;
	
	//funkcje i kontener funkcji - nie chce działać zgodnie z założeniem
	using wsk_ProstaFunkcja = void(*)();
	using kontener_Funkcji = std::vector<wsk_ProstaFunkcja>;
	using iterator_do_Funkcji = kontener_Funkcji::iterator;
	kontener_Funkcji potrzebneDoNarysowania;
	//potrzebne są kolejno pola typu iterator kontenera z nazwą funkcji np. iterator_do_Funkcji mnozPrzezMatryce 
	//- żeby znaleźć miejsce do wstawienia kolejnej funkcji we właściwej kolejności, we właściwym miejscu
	
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
};
#endif