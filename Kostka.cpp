#include "Kostka.h"
unsigned short Kostka::nr[] = {0,1,5,4,
                            3,7,6,2,
                            2,6,5,1,
                            3,0,4,7,
                            4,5,6,7,
                            0,3,2,1};
Kostka::Kostka(float x, float y, float z)
{
    UdostepnijBazieVertexyInormalne(&p[0][0],8,&n[0][0],6);
	UdostepnijBazieIndeksyWierzcholkow(&nr[0],4);
    float zeWskaznika[] = {x,y,z};
    UstawPolozenieSrodkaModelu(zeWskaznika);
    ObliczPunktyKorzystajacZdlugosciIsrodka(1.0,zeWskaznika);
}
Kostka::Kostka():Kostka(0.0f,0.0f,0.0f)
{
    
}
Kostka::Kostka(float* zeWskaznika):Kostka(zeWskaznika[0],zeWskaznika[1],zeWskaznika[2])
{
    
}
Kostka::Kostka(float * srodek,float * kol):Kostka(srodek)
{
    for(int i = 0 ; i < 3 ; i++)kolor[i] = kol[i];
}
void Kostka::ObliczPunktyKorzystajacZdlugosciIsrodka(float dd, float* c)
{
	//można dd użyć jako d[3] długość szerokość wysokość oddzielnie
	float d = dd/2;
	p[0][0] = -d; p[0][1] = -d; p[0][2] =  d;
	p[1][0] =  d; p[1][1] = -d; p[1][2] =  d;
	p[2][0] =  d; p[2][1] = -d; p[2][2] = -d;
	p[3][0] = -d; p[3][1] = -d; p[3][2] = -d;
	p[4][0] = -d; p[4][1] =  d; p[4][2] =  d;
	p[5][0] =  d; p[5][1] =  d; p[5][2] =  d;
	p[6][0] =  d; p[6][1] =  d; p[6][2] = -d;
	p[7][0] = -d; p[7][1] =  d; p[7][2] = -d;
	//dodanie wektora środka - czyli przesunięcie do punktu c(x,y,z)
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 3; j++)p[i][j]+=c[j];
	}
	//przód
	n[0][0] = 0; n[0][1] = 0; n[0][2] = 1;
	//tył
	n[1][0] = 0; n[1][1] = 0; n[1][2] =-1;
	//prawy
	n[2][0] = 1; n[2][1] = 0; n[2][2] = 0;
	//lewy
	n[3][0] =-1; n[3][1] = 0; n[3][2] = 0;
	//góra
	n[4][0] = 0; n[4][1] = 1; n[4][2] = 0;
	//dół
	n[5][0] = 0; n[5][1] =-1; n[5][2] = 0;
}

void Kostka::RysujGeometrie()
{
    RysujGeometrieTemplate<0,GL_QUADS>();
}

void Kostka::PrzeliczPunktyZaktualnejMacierzy()
{
    Model::PrzeliczPunktyZaktualnejMacierzy();
    /*float stare[4],nowe[4],m[16];
    auto kopiuj3 = [](float* zr,float* cel){
        for(int j = 0; j < 3 ; j++){
            cel[j] = zr[j];
        }
    };
    auto pokazPunkty = [&](){
        for(int i  = 0; i < 8 ; i++)g_print("\n%d %2.3f, %2.3f, %2.3f",i,p[i][0],p[i][1],p[i][2]);
    };
    auto pokazPunkt = [](float * u){
        g_print("\n   ");
        for(int i  = 0; i < 4 ; i++)g_print("  %2.3f",u[i]);
    };
    auto PunktMiedzyWektorami = [](float * v1, float * v2){
        float s[3];
        for(int i  = 0; i < 3 ; i++)s[i] = (v1[i] + v2[i])/2.0;
        g_print("\n %2.3f, %2.3f, %2.3f",s[0],s[1],s[2]);
    };
    stare[3] = 1.0f;
    glGetFloatv(GL_MODELVIEW_MATRIX,m);
//    WyswietlWartosciMacierzy4x4(m);
    float tylkoObroty[16];
    auto WyluskajObrotyZmacierzyModelWidok = [&](){
        for(int k = 0 ; k < 16 ; k++)tylkoObroty[k] = m[k];
        for(int l = 12 ; l < 15 ; l++)tylkoObroty[l] = 0;
    };
//    WyswietlWartosciMacierzy4x4(tylkoObroty);
   for(int i  = 0; i < 8 ; i++){
        kopiuj3(p[i],stare);
//        IloczynWektoraImacierzy4f(stare,m,nowe);
        IloczynMacierzyIwektora4f(m,stare,nowe);
        kopiuj3(nowe,p[i]);
   }
    WyluskajObrotyZmacierzyModelWidok();
   for(int i  = 0; i < 6 ; i++){
        kopiuj3(n[i],stare);
//        pokazPunkt(stare);
        IloczynMacierzyIwektora4f(tylkoObroty,stare,nowe);
        kopiuj3(nowe,n[i]);
   }
   kopiuj3(srodekModelu,stare);
    IloczynMacierzyIwektora4f(m,stare,nowe);
    kopiuj3(nowe,srodekModelu);
   UstawPustaDomyslnaFunkcje();*/
}

