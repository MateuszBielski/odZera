#ifndef CZWOROSCIAN_H
#define CZWOROSCIAN_H
#include <Model.h>

class Czworoscian : public Model{
public:
    Czworoscian();
    Czworoscian(float x, float y, float z);
    Czworoscian(float * srodekModelu);
    Czworoscian(float * srodekModelu,float * kolor);
    virtual ~Czworoscian(){};
    virtual void RysujGeometrie() override;
    void ObliczPunktyKorzystajacZdlugosciIsrodka(float d, float* c);
private:
    float p[4][3];
    float n[4][3];
    static unsigned short nr[];    
};

#endif // CZWOROSCIAN_H
