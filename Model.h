#ifndef MODEL_H
#define MODEL_H
#include <gtkglmm.h>


class Model{
public :
    Model();
    virtual ~Model(); 
    void RysujOstroslup();
	virtual void Rysuj();
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
};

#endif