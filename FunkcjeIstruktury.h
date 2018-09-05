#ifndef FUNKCJEISTRUKTURY_H
#define FUNKCJEISTRUKTURY_H
#include <GL/glu.h>
#include <gtkglmm.h>

struct POINT{
    POINT(float x, float y):x(x),y(y){};
    float x,y;
};
void WyswietlWartosciMacierzy4x4(float * macierz16);
void TransformujPikselDoPrzestrzeniSceny(int x, int y,float glebokosc,float*  pozycjaPunktu3D);
void TransformujPikselDoPrzestrzeniSceny(int x, int y,float*  pozycjaPunktu3D);
#endif
