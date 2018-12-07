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
    glEnable(GL_POINT_SMOOTH);
    
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
	
	/***antyaliasing***/
//	glEnable(GL_POLYGON_SMOOTH);
//    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
//    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

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
    float kolorZrodla[] = {0.7,0.7,0.9,1.0};
    float temp[] = {0.0,1.0,3.0,1.0};//obowiązkowo 1 na końcu
    memcpy(pozycjaZrodlaSwiatla,temp,4*sizeof(float));
    glLightfv(GL_LIGHT1,GL_POSITION,pozycjaZrodlaSwiatla); 
    glLightfv(GL_LIGHT1,GL_DIFFUSE,kolorZrodla);
    glEnable(GL_LIGHT1);
    
    float kolorZrodla2[] = {0.1,0.3,0.1,1.0};
    float temp2[] = {-1.5,1.0,3.0,1.0};
    glLightfv(GL_LIGHT2,GL_POSITION,temp2); 
    glLightfv(GL_LIGHT2,GL_DIFFUSE,kolorZrodla2);
    glEnable(GL_LIGHT2);
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
EkranRysujacy::stos_int EkranRysujacy::StosNazwObiektuWpunkcie(int x, int y)
{
    const int rozmiarBuforaZaznaczenia = 1024;
    unsigned buforZaznaczenia[rozmiarBuforaZaznaczenia];
    std::fill_n (buforZaznaczenia,rozmiarBuforaZaznaczenia,0);
    glSelectBuffer(rozmiarBuforaZaznaczenia, buforZaznaczenia);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    glLoadIdentity();
    int viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    gluPickMatrix(x, wysokosc - y, 8, 8, viewport);
    float aspect = static_cast<float>(szerokosc) / static_cast<float>(wysokosc);
    glFrustum(-aspect, aspect, -1.0, 1.0, planBliski, planDaleki);
    glMatrixMode(GL_MODELVIEW);
    glRenderMode(GL_SELECT); //umieść znak komemtarza przed tym poleceniem, żeby zobaczyć co widzi myszka
    RysujScene();//BEZ_SWAPBUFFERS
    unsigned ileTrafien = glRenderMode(GL_RENDER);
//    g_print("\nWyoborPunktu ileTrafien= %d, zawartosc bufora: \n ", ileTrafien);
//    for (int j = 0; j < 5 * ileTrafien + 10; j++)g_print(" %d,", buforZaznaczenia[j]);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    return CoZaznaczono(ileTrafien,buforZaznaczenia);
}

EkranRysujacy::stos_int EkranRysujacy::CoZaznaczono(int ileTrafien, unsigned int* dane)
{
    stos_int wynik;
    wynik.push(-1);
   
    if (ileTrafien > 0) {
        unsigned poczatekRekordu = 0;
        unsigned wysokoscStosuNazw = dane[poczatekRekordu];
        unsigned dlugoscRekordu = 3 + wysokoscStosuNazw;
        stos_int indeksNajblizszegoPunktu;
        unsigned odlegloscNajblizszegoPunktu = dane[poczatekRekordu+2];
        unsigned biezacaOdlegloscPunktu = odlegloscNajblizszegoPunktu;
        auto wypelnijStosNazwami = [&](){
            stos_int nowyStos;
            indeksNajblizszegoPunktu = nowyStos;
//            g_print("\nwypelnijStosNazwami");
            for(short i = poczatekRekordu+2+wysokoscStosuNazw ; i > poczatekRekordu+2 ; i--){
                indeksNajblizszegoPunktu.push(dane[i]);
//                g_print(" %d",dane[i]);
            }
        };
       
        wypelnijStosNazwami();
        for (int i = 0; i < ileTrafien; i++) {
            wysokoscStosuNazw = dane[poczatekRekordu];
            dlugoscRekordu = 3 + wysokoscStosuNazw;
            biezacaOdlegloscPunktu = dane[poczatekRekordu+2];
            if(biezacaOdlegloscPunktu < odlegloscNajblizszegoPunktu ){
                odlegloscNajblizszegoPunktu = biezacaOdlegloscPunktu;
                wypelnijStosNazwami();
            }
            poczatekRekordu += dlugoscRekordu;
        }
        wynik=indeksNajblizszegoPunktu;

    }
//    g_print("  indeks najbliższegoPunktu %d",wynik);
	return wynik;
}

