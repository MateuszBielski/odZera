#ifndef KOSTKA_H
#define KOSTKA_H
#include <Model.h>

//class LinieZnormalnych;
class Kostka : public Model{
//  friend class LinieZnormalnych;
public:
    Kostka();//domyślnie ustawia środek modelu 0,0,0 i tak oblicza punkty
    Kostka(float * srodekModelu);
    Kostka(float * srodekModelu,float * kolor);
    Kostka(float, float, float);
    virtual ~Kostka(){};
    virtual void PrzeliczPunktyZaktualnejMacierzy() override;
	void ObliczPunktyKorzystajacZdlugosciIsrodka(float d, float* c);
    virtual void RysujGeometrie() override;
private:
	float p[8][3];
    float n[6][3];
    unsigned short nr[24];
};

#endif // KOSTKA_H
