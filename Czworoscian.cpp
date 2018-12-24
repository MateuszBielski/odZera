#include "Czworoscian.h"
//#include <FunkcjeIstruktury.h>
unsigned short Czworoscian::indeksNaroznika[] = {0,2,1,
                                    0,1,3,
                                    1,2,3,
                                    0,3,2};
Czworoscian::Czworoscian(float x, float y, float z)
{
    UdostepnijBazieVertexyInormalne(&p[0][0],4,&n[0][0],4);
	UdostepnijBazieIndeksyWierzcholkow(&indeksNaroznika[0],3);
    float srodek[] = {x,y,z};
    UstawPolozenieSrodkaModelu(srodek);
    ObliczPunktyKorzystajacZdlugosciIsrodka(1.5,srodek);
}
Czworoscian::Czworoscian():Czworoscian(0.0,0.0,0.0)
{
}
Czworoscian::Czworoscian(float * zeWskaznika):Czworoscian(zeWskaznika[0],zeWskaznika[1],zeWskaznika[2])
{
}
Czworoscian::Czworoscian(float * srodek,float * kol):Czworoscian(srodek)
{
    for(int i = 0 ; i < 3 ; i++)kolor[i] = kol[i];
}
void Czworoscian::ObliczPunktyKorzystajacZdlugosciIsrodka(float a, float* c){
//    g_print("\nCzworoscian::ObliczPunkty");
    float H = a*sqrt(6.0f)/3;
    float h = a*sqrt(3.0f)/2;
    //podstawa
    for(int i = 0 ; i < 3 ; i++)p[i][1] = 0.0;
    p[0][0] = -a/2; p[1][0] = a/2; p[2][0] = 0.0f;
    p[0][2] = h/3.0; p[1][2] = h/3.0; p[2][2] = -2*h/3.0;
    //wierzcholek
    p[3][0] = 0.0; p[3][1] = H; p[3][2] = 0.0;
    //przesunąć do środka ciężkości
    float srodekGeometryczny[3];
    for(int i = 0 ; i < 3 ; i++)srodekGeometryczny[i] = 0.0f;
    for(int j = 0 ; j < 4 ; j++){
        for(int i = 0 ; i < 3 ; i++)srodekGeometryczny[i] += p[j][i];
    }
    for(int i = 0 ; i < 3 ; i++)srodekGeometryczny[i] /= 4.0;
//    g_print("\nsrodek czworościanu %2.3f, %2.3f, %2.3f",srodekGeometryczny[0],srodekGeometryczny[1],srodekGeometryczny[2]);
    for(int i = 0; i < 4; i++)p[i][1] -=srodekGeometryczny[1];
    //dodać środek modelu************
    for(int i = 0; i < 4; i++){
		for(int j = 0; j < 3; j++)p[i][j]+=c[j];
	}
    //normalne
    n[0][0] = 0;n[0][1] = -1;n[0][2] = 0;
    n[1][0] = 0;n[1][1] = h/3.0;n[1][2] = H;
    n[2][0] = h;n[2][1] = a*h/(3*H);n[2][2] = -a/2;
    n[3][0] = -h;n[3][1] = a*h/(3*H);n[3][2] = -a/2;
    for(int i = 1 ; i < 4 ; i++)NormujWektor3fv(n[i]);
}
void Czworoscian::RysujGeometrie(){
	RysujGeometrieTemplate<0,GL_TRIANGLES>();
}
