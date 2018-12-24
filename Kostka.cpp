#include "Kostka.h"
unsigned short Kostka::indeksNaroznika[] = {0,1,5,4,
                            3,7,6,2,
                            2,6,5,1,
                            3,0,4,7,
                            4,5,6,7,
                            0,3,2,1};
unsigned short Kostka::indeksySasiadow[][2] = {{1,2},{3,4},{1,2},{3,4},{1,2},{3,4},
                                            {1,2},{3,4},{1,2},{3,4},{1,2},{3,4},
                                            {1,2},{3,4},{1,2},{3,4},{1,2},{3,4},
                                            {1,2},{3,4},{1,2},{3,4},{1,2},{3,4}};//wygląda na to, że nie trzeba wszystkich inicjalizować, reszta ma teraz wartość 0
//====================
//poniżej wymuszenie obliczenia indeksów wierzcholkow sasiadujacych
bool Kostka::indeksyUstalone = Kostka::UstalIndeksySasiadow();

bool Kostka::UstalIndeksySasiadow(){
   int ileScian = 6;
    int ileWierzcholkowWscianie = 4;
    int ktoryNaroznik = -1;
    int lewySasiad,prawySasiad;
    auto Podstaw = [&](int tempIndex1,int tempIndex2){
        ++ktoryNaroznik;
        lewySasiad = indeksNaroznika[ktoryNaroznik + tempIndex1];
        prawySasiad = indeksNaroznika[ktoryNaroznik + tempIndex2];
        indeksySasiadow[ktoryNaroznik][0] = lewySasiad;
        indeksySasiadow[ktoryNaroznik][1] = prawySasiad;
    };
    for(int s = 0; s < ileScian ; s++){
        int w = 0;
        Podstaw(ileWierzcholkowWscianie - 1,1);
       for(w = 1; w < ileWierzcholkowWscianie-1 ; w++)Podstaw(- 1,1);
       Podstaw(- 1, - ileWierzcholkowWscianie + 1);
    }
//    for(int i = 0 ; i < 24 ; i++)g_print("\n%d L: %d, P: %d",i,indeksySasiadow[i][0],indeksySasiadow[i][1]);
    return true;
}
Kostka::Kostka(float x, float y, float z)
{
    UdostepnijBazieVertexyInormalne(&p[0][0],8,&n[0][0],6);
	UdostepnijBazieIndeksyWierzcholkow(&indeksNaroznika[0],4);
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
}

