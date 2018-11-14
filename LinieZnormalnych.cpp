#include "LinieZnormalnych.h"

void LinieZnormalnych::RysujDla(std::shared_ptr<Model> model)
{
    normalne = model->normalne;
    ileNormalnych = model->ileNormalnych;
    mojeWspolrzedneImacierzeSterowania = model->mojeWspolrzedneImacierzeSterowania;
    //srodek modelu NIE kopiujemy
}

void LinieZnormalnych::RysujGeometrie()
{
    float r[6] = {1.0,0.5,0.2,0.2,0.2,0.2};
    float g[6] = {0.2,0.2,1.0,0.5,0.2,0.2};
    float b[6] = {0.2,0.2,0.2,0.2,1.0,0.5};
    auto JakaNormalna = [](){
      float biezacyWektor[3];
      glGetFloatv(GL_CURRENT_NORMAL,biezacyWektor);
      g_print("\nbieżące wartości normalnej %2.3f,  %2.3f,  %2.3f,",biezacyWektor[0],biezacyWektor[1],biezacyWektor[2]);
    };
    for(int i = 0 ; i < ileNormalnych ; i++){
        glBegin(GL_LINES);
        glColor3f(r[i],g[i],b[i]);
        glNormal3fv(&normalne[i*3]);
        glVertex3f(0.0,0.0,0.0);
        glVertex3fv(&normalne[i*3]);
        glEnd();
        
    }
    /*g_print("\nLinieZnormalnych::RysujGeometrie");
    for(int i = 0 ; i < ileNormalnych ; i++){
        float * pN = &normalne[i*3];
        g_print("\n  %2.3f,  %2.3f,  %2.3f",pN[0],pN[1],pN[2]);
    }*/
}

