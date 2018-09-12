#include "SterowanieMysza.h"
#include <trackball.h>



SterowanieMysza::SterowanieMysza()
{
	Komunikat("SterowanieMysza");
	calegoWidoku.przesunieciePierwotne[2] = -15.0;
}

SterowanieMysza::~SterowanieMysza()
{
	Komunikat("~SterowanieMysza");
}

int SterowanieMysza::PodlaczanieSygnalow(Gtk::Widget& okno)
{
    UstawOkno(&okno);
	okno.set_events(Gdk::BUTTON1_MOTION_MASK|Gdk::BUTTON_PRESS_MASK|Gdk::SCROLL_MASK|Gdk::BUTTON2_MOTION_MASK|Gdk::BUTTON3_MOTION_MASK);
    DodajDoListyWskaznikPolaczenia(
        UtrwalPolaczenie(okno.signal_button_press_event().connect(sigc::mem_fun(*this,&SterowanieMysza::on_button_press_event))));
    DodajDoListyWskaznikPolaczenia(
        UtrwalPolaczenie(okno.signal_motion_notify_event().connect(sigc::mem_fun(*this,&SterowanieMysza::on_motion_notify_event))));
    DodajDoListyWskaznikPolaczenia(
        UtrwalPolaczenie(okno.signal_scroll_event().connect(sigc::mem_fun(*this,&SterowanieMysza::on_my_scroll_event))));
   return 3;
}

void SterowanieMysza::WyszukujeIustawiamWskaznikiDoInnychModulow(){
	ekran = Ptr_WyszukajWModulach<EkranRysujacy>("ekranGL");
	renderowanie =  Ptr_WyszukajWModulach<Renderowanie>("renderowanie");
    renderowanie->PobierzWskaznikNaWektorPrzesunieciaPierwotnego(&calegoWidoku.przesunieciePierwotne[0]);
	renderowanie->PobierzWskaznikNaWektorPrzesuniecia(&calegoWidoku.m_Pos[0]);
	renderowanie->PobierzWskaznikNaMacierzObrotu(&calegoWidoku.macierzObrotu[0][0]);
	renderowanie->DajWybranyModel()->WezWskaznikiMacierzyObrotuIpolozenia(&wybranegoObiektu.macierzObrotu[0][0],&wybranegoObiektu.m_Pos[0]);
}
bool SterowanieMysza::on_button_press_event(GdkEventButton* event)
{
    aktualneSterowanie->m_BeginX = event->x;
    aktualneSterowanie->m_BeginY = event->y;
    int ix = static_cast<int>(event->x);
    int iy = static_cast<int>(event->y);
    if (event->button == 2){
       float temp;
       glReadPixels( ix, iy, 1, 1,GL_DEPTH_COMPONENT, GL_FLOAT, &temp );
       if(temp < 1.0)aktualneSterowanie->wspolrzednaZpodKursorem = temp;
        TransformujPikselDoPrzestrzeniSceny(ix,iy,aktualneSterowanie->wspolrzednaZpodKursorem,aktualneSterowanie->poprzedniaPozycjaKursoraMyszy3D);
    }
    //prawy przycisk
    if (event->button == 3){
        float pozycja4f[4];
        float pozycja3f[3];
        ekran->PodajPozycjeZrodlaSwiatla(pozycja4f);

        TransformujPikselDoPrzestrzeniSceny(ix,iy,0.7,pozycja3f);
        for(int i = 0 ; i < 3 ; i++)pozycja4f[i] = pozycja3f[i];
        ekran->UstawPozycjeZrodlaSwiatla(pozycja4f);
    }
    //podwójne kliknięcie
    if(event->type == GDK_2BUTTON_PRESS && event->button == 1){
        ekran->WyznaczIndeksObiektuWpunkcie(ix,iy);
    }
    oknoSterowane->get_window()->invalidate_rect(oknoSterowane->get_allocation(), false);
    return true;
}

bool SterowanieMysza::on_motion_notify_event(GdkEventMotion* event)
{
    float w = oknoSterowane->get_width();
    float h = oknoSterowane->get_height();
    float x = event->x;
    float y = event->y;
    int ix = static_cast<int>(event->x);
    int iy = static_cast<int>(event->y);
    aktualneSterowanie->m_DX = x - aktualneSterowanie->m_BeginX;
    aktualneSterowanie->m_DY = y - aktualneSterowanie->m_BeginY;
    if(aktualneSterowanie->m_DX == 0 && aktualneSterowanie->m_DY == 0)return true;
    if (event->state & GDK_BUTTON1_MASK) {
        Trackball::trackball(aktualneSterowanie->m_QuatDiff,
                           (2.0 * aktualneSterowanie->m_BeginX - w) / w,
                           (h - 2.0 * aktualneSterowanie->m_BeginY) / h,
                           (2.0 * x - w) / w,
                           (h - 2.0 * y) / h);
        if(aktualneSterowanie == &wybranegoObiektu)KorekcjaOsiObrotuWybranegoModelu();
        Trackball::add_quats(aktualneSterowanie->m_QuatDiff, aktualneSterowanie->m_Quat, aktualneSterowanie->m_Quat);
		Trackball::build_rotmatrix(aktualneSterowanie->macierzObrotu, aktualneSterowanie->m_Quat);
    }
    if (event->state & GDK_BUTTON2_MASK){
        TransformujPikselDoPrzestrzeniSceny(aktualneSterowanie->m_BeginX,aktualneSterowanie->m_BeginY,aktualneSterowanie->wspolrzednaZpodKursorem,
                                            aktualneSterowanie->poprzedniaPozycjaKursoraMyszy3D);
        TransformujPikselDoPrzestrzeniSceny(ix,iy,aktualneSterowanie->wspolrzednaZpodKursorem,aktualneSterowanie->biezacaPozycjaKursoraMyszy3D);
        aktualneSterowanie->ZmienM_Pos_zgodnieZruchemKursora3D();
        
    }
    if (event->state & GDK_BUTTON3_MASK){
        float pozycjaWczesniejsza[4];
        float pozycjaBiezaca[3];
        ekran->PodajPozycjeZrodlaSwiatla(pozycjaWczesniejsza);
        TransformujPikselDoPrzestrzeniSceny(ix,iy,0.7,pozycjaBiezaca);//,0.8
        for(int i = 0 ; i < 3 ; i++){
            pozycjaWczesniejsza[i] += pozycjaBiezaca[i] - pozycjaWczesniejsza[i];
        }
        ekran->UstawPozycjeZrodlaSwiatla(pozycjaWczesniejsza);
    }
	aktualneSterowanie->m_BeginX = x;
    aktualneSterowanie->m_BeginY = y;
    aktualneSterowanie->BiezaceUstawJakoPoprzednie_PozycjaKursoraMyszy3D();
//        std::cout << std::bitset<24>(oknoSterowane->get_events())<<std::endl;
	oknoSterowane->get_window()->invalidate_rect(oknoSterowane->get_allocation(), false);
    //nie może być false bo przekazuje jakby jeszcze kilka razy do obsługi i nie pozwala przeliczyć sie macierzom
    return true;
}

bool SterowanieMysza::on_my_scroll_event(GdkEventScroll* scroll_event)
{
    if (!scroll_event->direction){//GDK_SCROLL_UP
        calegoWidoku.przesunieciePierwotne[2] *=0.9;
    }
    if (scroll_event->direction){//GDK_SCROLL_DOWN
        calegoWidoku.przesunieciePierwotne[2] /=0.9;
    }
    oknoSterowane->get_window()->invalidate_rect(oknoSterowane->get_allocation(), false);
    return true;
}
void SterowanieMysza::KorekcjaOsiObrotuWybranegoModelu()
{
	/*
     * algorytm:
     * obrócić oś wokół której następuje obrót.  */
     float katWybranegoModelu;
     float osWybranyModel[4];
     float osObroconaWybranegoModelu[4];
     osWybranyModel[3] = 0;
     
     Quat_to_Phi_a(wybranegoObiektu.m_QuatDiff,&katWybranegoModelu,osWybranyModel);
     IloczynMacierzyIwektora(&calegoWidoku.macierzObrotu[0][0],osWybranyModel,osObroconaWybranegoModelu);
     Trackball::axis_to_quat(osObroconaWybranegoModelu,katWybranegoModelu,wybranegoObiektu.m_QuatDiff);
}
