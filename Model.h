#ifndef MODEL_H
#define MODEL_H
#include <gtkglmm.h>


class Model{
public :
    Model();
    virtual ~Model(); 
    void RysujOstroslup();
	virtual void Rysuj();
    virtual void Wygladzanie(bool){};//do zastanowienia się czy warto przy każdym obiekcie to ustalać
    void UstalPolozenie3f(float*);
protected:
    //void UstalVertexy(int szer, int wys, float skala);
    //void UstalIndexy(int szer, int wys);
    //void UstalKolory();
    float * vertexy = 0;
    int * indeksy = 0;
    float * kolory = 0;
    float * normalne = 0;
    int ileVertexow = 0;
    int ileIndeksow = 0;
    float polozenie3f[3];
};

class Ostroslup : public Model{
  public:
    Ostroslup(){};
    virtual ~Ostroslup(){};
    virtual void Rysuj() override;
};
class Kostka : public Model{
  public:
    Kostka(){};
    virtual ~Kostka(){};
    virtual void Rysuj() override;
};
#endif