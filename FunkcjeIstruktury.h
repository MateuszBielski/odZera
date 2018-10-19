#ifndef FUNKCJEISTRUKTURY_H
#define FUNKCJEISTRUKTURY_H
#include <GL/glu.h>
#include <gtkglmm.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#else
struct POINT{
    POINT(float x, float y):x(x),y(y){};
    float x,y;
};
#endif
void WyswietlWartosciMacierzy4x4(float * macierz16);
void TransformujPikselDoPrzestrzeniSceny(int x, int y,float glebokosc,float*  pozycjaPunktu3D);
void TransformujPikselDoPrzestrzeniSceny(int x, int y,float*  pozycjaPunktu3D);
void Quat_to_Phi_a(float * quat,float* phi,float* a);
void IloczynWektoraImacierzy4f(float * v, float * m, float * vDest);
void IloczynMacierzyIwektora4f(float * m, float * v, float * vDest);
#endif
