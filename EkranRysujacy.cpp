#include "EkranRysujacy.h"
#include "FunkcjeIstruktury.h"
EkranRysujacy::EkranRysujacy()
{
	Komunikat("EkranRysujacy");
    planBliski = 5.0;
    planDaleki = 60.0;
}

EkranRysujacy::~EkranRysujacy()
{
	Komunikat("~EkranRysujacy");
}
void EkranRysujacy::UstawienieSceny()
{
//	Komunikat("EkranRysujacy::UstawienieSceny");
	
	szerokosc = get_width();
	wysokosc = get_height();
	glViewport(0, 0, szerokosc, wysokosc);
    glShadeModel(GL_SMOOTH);//cieniowanie kolorem GK_SMOOTH, GL_FLAT
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_BLEND);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (szerokosc > wysokosc) {
      float aspect = static_cast<float>(szerokosc) / static_cast<float>(wysokosc);
      glFrustum(-aspect, aspect, -1.0, 1.0, planBliski, planDaleki);
//      glFrustum(-0.1, 0.1, wsp*-0.1, wsp * 0.1, nearDoKorektySceny, 400.0);
    } else {
      float aspect = static_cast<float>(wysokosc) / static_cast<float>(szerokosc);
      glFrustum(-1.0, 1.0, -aspect, aspect, planBliski, planDaleki);
    }

    glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void EkranRysujacy::OswietlenieUstaw()
{
    glEnable(GL_LIGHTING);
    
    //kolormateriału (glColor uwzględniany)
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    //światło punktowe
    float kolorZrodla[] = {0.8,0.8,0.8,1.0};
    float temp[] = {0.0,1.0,3.0,0.0};
    memcpy(pozycjaZrodlaSwiatla,temp,4*sizeof(float));
    glLightfv(GL_LIGHT1,GL_POSITION,pozycjaZrodlaSwiatla); 
    glLightfv(GL_LIGHT1,GL_DIFFUSE,kolorZrodla);
    glEnable(GL_LIGHT1);
}
void EkranRysujacy::RysujScene()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	
    renderowanie->TransformacjaCalegoWidoku(); 
	glLightfv(GL_LIGHT1,GL_POSITION,pozycjaZrodlaSwiatla);
    renderowanie->RysujModele();
    
}

void EkranRysujacy::PodajPozycjeZrodlaSwiatla(float * tutaj){
    memcpy(tutaj,pozycjaZrodlaSwiatla,4*sizeof(float));
}
void EkranRysujacy::UstawPozycjeZrodlaSwiatla(float * wedlugParametrow){
    memcpy(pozycjaZrodlaSwiatla,wedlugParametrow,4*sizeof(float));
    renderowanie->UstawPolozenieSwiatla(wedlugParametrow);
}
int EkranRysujacy::WyznaczIndeksObiektuWpunkcie(int x, int y)
{
	
    
    //implementacja z arcball gwiazdy:
//    clock_t czas[5];
//    czas[0] = clock();
    
    //przygotowanie bufora zaznaczenia
    const int rozmiarBuforaZaznaczenia = 1024;
    unsigned buforZaznaczenia[rozmiarBuforaZaznaczenia];
    std::fill_n (buforZaznaczenia,rozmiarBuforaZaznaczenia,0);
    glSelectBuffer(rozmiarBuforaZaznaczenia, buforZaznaczenia);

    //przygotowanie promienia pod myszką 
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glLoadIdentity();
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    gluPickMatrix(x, wysokosc - y, 8, 8, viewport);
    //czas[1]=clock();
        float aspect = static_cast<float>(szerokosc) / static_cast<float>(wysokosc);
        glFrustum(-aspect, aspect, -1.0, 1.0, planBliski, planDaleki);
    glMatrixMode(GL_MODELVIEW);
    //przełączanie w tryb selekcji i renderowanie sceny
    glRenderMode(GL_SELECT); //umieść znak komemtarza przed tym poleceniem, żeby zobaczyć co widzi myszka
    RysujScene();//BEZ_SWAPBUFFERS
//    czas[2]=clock();
    //powrót do norlamlnego trybu renderowania
    int ileTrafien = glRenderMode(GL_RENDER);
//    czas[3]=clock();
//    g_print("\nWyoborPunktu ileTrafien= %d, zawartosc bufora: \n ", ileTrafien);
//    for (int j = 0; j < 5 * ileTrafien + 10; j++)g_print(" %d,", buforZaznaczenia[j]);
    //przywracanie oryginalnej macierzy rzutowania
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    return CoZaznaczono(ileTrafien,buforZaznaczenia);
    
}
int EkranRysujacy::CoZaznaczono(int ileTrafien,unsigned int * dane)
{
    int wynik=-1;
    if (ileTrafien > 0) {
        unsigned poczatekRekordu = 0;
        unsigned wysokoscStosuNazw = dane[poczatekRekordu];
        unsigned dlugoscRekordu = 3 + wysokoscStosuNazw;
        unsigned indeksNajblizszegoPunktu = dane[poczatekRekordu+2+wysokoscStosuNazw];
        unsigned odlegloscNajblizszegoPunktu = dane[poczatekRekordu+2];
        unsigned biezacaOdlegloscPunktu = odlegloscNajblizszegoPunktu;
        int biezacyIndeks = 0;
        for (int i = 0; i < ileTrafien; i++) {
            wysokoscStosuNazw = dane[poczatekRekordu];
            dlugoscRekordu = 3 + wysokoscStosuNazw;
//			g_print("\nindeks najblizszego punktu %d",indeksNajblizszegoPunktu);
            biezacaOdlegloscPunktu = dane[poczatekRekordu+2];
//			g_print(" bieżąca odległość punktu %d",biezacaOdlegloscPunktu);
            if(biezacaOdlegloscPunktu < odlegloscNajblizszegoPunktu ){
                odlegloscNajblizszegoPunktu = biezacaOdlegloscPunktu;
                indeksNajblizszegoPunktu = dane[poczatekRekordu+2+wysokoscStosuNazw];
            }
//			g_print("\nkoniec pętli\nindeks najblizszego punktu %d odleglosc najblizszego %d",indeksNajblizszegoPunktu, odlegloscNajblizszegoPunktu);
            poczatekRekordu += dlugoscRekordu;
//			g_print(" bieżąca odległość punktu %d\n",biezacaOdlegloscPunktu);
        }
        wynik=indeksNajblizszegoPunktu;

    }
//    g_print("  indeks najbliższegoPunktu %d",wynik);
	return wynik;
    /*
    czas[4] = clock();
    long delta[5]; //= (long) (koniec - start);
    printf("\n czasy:");
    for(int i=0;i<4;i++){
        delta[i]=(long)(czas[i+1]-czas[i]);
        printf("\n%d. %d ms",i,delta[i]);
    }
    delta[4]=(long)(czas[4]-czas[0]);
    printf("\ncalosc %d ms",delta[4]);
    return wynik;*/
}
