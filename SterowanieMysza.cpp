#include "SterowanieMysza.h"
#include <trackball.h>



SterowanieMysza::SterowanieMysza()
{
	Komunikat("SterowanieMysza");
	calegoWidoku.przesunieciePierwotne[2] = -15.0;
//    UstawZestawObslugi(1);
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

void SterowanieMysza::PrzejmijSterowanieOd(SterowanieMysza & dotychczasowe){
    dotychczasowe.ZablokujPolaczenia();
//    KopiujParametrySterowania(dotychczasowe);
//    aktualneSterowanie = dotychczasowe.aktualneSterowanie;
    calegoWidoku.SkopiujWartosciZ(dotychczasowe.calegoWidoku);
    renderowanie->PobierzWskaznikNaWektorPrzesunieciaPierwotnego(&calegoWidoku.przesunieciePierwotne[0]);
    OdblokujPolaczenia();
}

bool SterowanieMysza::on_button_press_event(GdkEventButton* event)
{
    PobierzWspolrzedne_ix_iy(event->x,event->y);
    V_NaPrzyciskMyszaZmienne(event);
    OdswiezWidok();
    return true;
}

bool SterowanieMysza::on_motion_notify_event(GdkEventMotion* event)
{
    PobierzWspolrzedneWruchu_ix_iy_x_y(event->x,event->y);
    OdczytajWymiaryOkna();
    aktualneSterowanie->m_DX = x - aktualneSterowanie->m_BeginX;
    aktualneSterowanie->m_DY = y - aktualneSterowanie->m_BeginY;
    if(aktualneSterowanie->m_DX == 0 && aktualneSterowanie->m_DY == 0)return true;
    V_NaRuchMyszaZmienne(event);
    aktualneSterowanie->m_BeginX = x;
    aktualneSterowanie->m_BeginY = y;
    aktualneSterowanie->BiezaceUstawJakoPoprzednie_PozycjaKursoraMyszy3D();
//        std::cout << std::bitset<24>(oknoSterowane->get_events())<<std::endl;
    OdswiezWidok();
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
     
     Quat_to_Phi_a(wybranegoObiektu->m_QuatDiff,&katWybranegoModelu,osWybranyModel);
     IloczynWektoraImacierzy4f(osWybranyModel,&calegoWidoku.macierzObrotu[0][0],osObroconaWybranegoModelu);
     Trackball::axis_to_quat(osObroconaWybranegoModelu,katWybranegoModelu,wybranegoObiektu->m_QuatDiff);
}
void SterowanieMysza::WybieranieModelu(unsigned int& klawiszFunkcyjny){
    renderowanie->UstawRysowanieZnazwami();//by zrealizować w funkcji StosNazwObiektuWpunkcie
    auto stosNazw = ekran->StosNazwObiektuWpunkcie(ix,iy);
    zarzadzanieObiektami->WybierzModelOnumerze(stosNazw);
    if(klawiszFunkcyjny & GDK_SHIFT_MASK){
       zarzadzanieObiektami->WybranyModelPrzeniesDoGrupy();
    }
    if(klawiszFunkcyjny & GDK_CONTROL_MASK){
       zarzadzanieObiektami->WyodrebnijZgrupy(stosNazw) ;
    }
    bool czyUaktualnicAdresAktualneSterowanie = (aktualneSterowanie == wybranegoObiektu);
//        g_print("\nSterowanieMysza::on_button_press_event uaktualnić sterowanie? %d",czyUaktualnicAdresAktualneSterowanie);
    wybranegoObiektu = zarzadzanieObiektami->DajWybranyModel()->mojeWspolrzedneImacierzeSterowania.get();
    if(czyUaktualnicAdresAktualneSterowanie) aktualneSterowanie = wybranegoObiektu;    
}
void SterowanieMysza::SwiatloPozycjaOdczytaj(){
    float pozycja4f[4];
    float pozycja3f[3];
    ekran->PodajPozycjeZrodlaSwiatla(pozycja4f);

    TransformujPikselDoPrzestrzeniSceny(ix,iy,0.7,pozycja3f);
    for(int i = 0 ; i < 3 ; i++)pozycja4f[i] = pozycja3f[i];
    ekran->UstawPozycjeZrodlaSwiatla(pozycja4f);
}
void SterowanieMysza::SwiatloPozycjaZmien(){
    float pozycjaWczesniejsza[4];
    float pozycjaBiezaca[3];
    ekran->PodajPozycjeZrodlaSwiatla(pozycjaWczesniejsza);
    TransformujPikselDoPrzestrzeniSceny(ix,iy,0.7,pozycjaBiezaca);//,0.8
    for(int i = 0 ; i < 3 ; i++){
        pozycjaWczesniejsza[i] += pozycjaBiezaca[i] - pozycjaWczesniejsza[i];
    }
    ekran->UstawPozycjeZrodlaSwiatla(pozycjaWczesniejsza);    
}
void SterowanieMysza::PobierzWspolrzedne_ix_iy(gdouble x, gdouble y){
    aktualneSterowanie->m_BeginX = x;
    aktualneSterowanie->m_BeginY = y;
    ix = static_cast<int>(x);
    iy = static_cast<int>(y);
}
void SterowanieMysza::PobierzWspolrzedneWruchu_ix_iy_x_y(gdouble event_x, gdouble event_y)
{
    /*float x = event->x;
    float y = event->y;
    int ix = static_cast<int>(event->x);
    int iy = static_cast<int>(event->y);*/
    x = event_x;
    y = event_y;
    ix = static_cast<int>(event_x);
    iy = static_cast<int>(event_y);
}
    
void SterowanieMysza::OdczytajWymiaryOkna()
{
    w = oknoSterowane->get_width();
    h = oknoSterowane->get_height();
}
void SterowanieMysza::ObracajAktualneSterowanie(){
    
    Trackball::trackball(aktualneSterowanie->m_QuatDiff,
                       (2.0 * aktualneSterowanie->m_BeginX - w) / w,
                       (h - 2.0 * aktualneSterowanie->m_BeginY) / h,
                       (2.0 * x - w) / w,
                       (h - 2.0 * y) / h);
    if(aktualneSterowanie == wybranegoObiektu)KorekcjaOsiObrotuWybranegoModelu();
    Trackball::add_quats(aktualneSterowanie->m_QuatDiff, aktualneSterowanie->m_Quat, aktualneSterowanie->m_Quat);
    Trackball::build_rotmatrix(aktualneSterowanie->macierzObrotu, aktualneSterowanie->m_Quat);
}
void SterowanieMysza::PrzesuwajAktualnieSterowane(){
    TransformujPikselDoPrzestrzeniSceny(aktualneSterowanie->m_BeginX,aktualneSterowanie->m_BeginY,aktualneSterowanie->wspolrzednaZpodKursorem,
                                        aktualneSterowanie->poprzedniaPozycjaKursoraMyszy3D);
    TransformujPikselDoPrzestrzeniSceny(ix,iy,aktualneSterowanie->wspolrzednaZpodKursorem,aktualneSterowanie->biezacaPozycjaKursoraMyszy3D);
    aktualneSterowanie->ZmienM_Pos_zgodnieZruchemKursora3D();
}
void SterowanieMysza::OdswiezWidok()
{
    oknoSterowane->get_window()->invalidate_rect(oknoSterowane->get_allocation(), false);
}

void SterowanieMyszaVar_1::V_NaPrzyciskMyszaZmienne(GdkEventButton* event){
     if (event->button == 2){
       float temp;
       glReadPixels( ix, iy, 1, 1,GL_DEPTH_COMPONENT, GL_FLOAT, &temp );
       if(temp < 1.0)aktualneSterowanie->wspolrzednaZpodKursorem = temp;
        TransformujPikselDoPrzestrzeniSceny(ix,iy,aktualneSterowanie->wspolrzednaZpodKursorem,aktualneSterowanie->poprzedniaPozycjaKursoraMyszy3D);
    }
    //prawy przycisk
    if (event->button == 3)
    {
        SwiatloPozycjaOdczytaj();
    }
    //podwójne kliknięcie lewy
    if(event->button == 1 && event->type == GDK_2BUTTON_PRESS)  
    {
        auto klawiszFunkcyjny = event->state;
        WybieranieModelu(klawiszFunkcyjny);
    }
    //podwójne klik prawy
    if(event->button == 2 && event->type == GDK_2BUTTON_PRESS)  
    {       
    }
}
void SterowanieMyszaVar_1::WyszukujeIustawiamWskaznikiDoInnychModulow(){
	ekran = Ptr_WyszukajWModulach<EkranRysujacy>("ekranGL");
	renderowanie =  Ptr_WyszukajWModulach<Renderowanie1>("renderowanie");
    renderowanie->PobierzWskaznikNaWektorPrzesunieciaPierwotnego(&calegoWidoku.przesunieciePierwotne[0]);
	renderowanie->PobierzWskaznikNaWektorPrzesuniecia(&calegoWidoku.m_Pos[0]);
	renderowanie->PobierzWskaznikNaMacierzObrotu(&calegoWidoku.macierzObrotu[0][0]);
    
    zarzadzanieObiektami = Ptr_WyszukajWModulach<ZarzadzanieObiektami>("zarzadznieObiektami");
	//poniższe może powodować przypisanie adresu współrzędnchImacierzy modelu, który nie isnieje
//    wybranegoObiektu = zarzadzanieObiektami->DajWybranyModel()->mojeWspolrzedneImacierzeSterowania.get();
    
}
void SterowanieMyszaVar_1::V_NaRuchMyszaZmienne(GdkEventMotion* event){
     if (event->state & GDK_BUTTON1_MASK) {
        ObracajAktualneSterowanie();
    }
    if (event->state & GDK_BUTTON2_MASK){
        PrzesuwajAktualnieSterowane();
    }
    if (event->state & GDK_BUTTON3_MASK){
        SwiatloPozycjaZmien();
    }
}
SterowanieMyszaVar_1::SterowanieMyszaVar_1()
{
	//tutaj nie zmieniamy nazwy, gdyż posługujemy się oryginalną nazwą "sterowanie", która umożliwa odszukanie tego modułu z innych, wcześnijszych miejsc
}
void SterowanieMyszaVar_2::WyszukujeIustawiamWskaznikiDoInnychModulow()
{
    ekran = Ptr_WyszukajWModulach<EkranRysujacy>("ekranGL");
    renderowanie =  Ptr_WyszukajWModulach<Renderowanie1>("renderowanie");
    zarzadzanieObiektami = Ptr_WyszukajWModulach<ZarzadzanieObiektami>("zarzadznieObiektami");
}
SterowanieMyszaVar_2::SterowanieMyszaVar_2()
{
	nazwa = "sterowanieVar_2";
    aktualneSterowanie = &modyfikacjaPunktow;
	zablokujPolaczeniaPrzyStarcie = true;
}
void SterowanieMyszaVar_2::V_NaPrzyciskMyszaZmienne(GdkEventButton* event){
    if (event->button == 1){
       WybieraniePunktu();
        float temp;
       glReadPixels( ix, iy, 1, 1,GL_DEPTH_COMPONENT, GL_FLOAT, &temp );
       if(temp < 1.0)aktualneSterowanie->wspolrzednaZpodKursorem = temp;
        TransformujPikselDoPrzestrzeniSceny(ix,iy,aktualneSterowanie->wspolrzednaZpodKursorem,aktualneSterowanie->poprzedniaPozycjaKursoraMyszy3D);
    }
}
void SterowanieMyszaVar_2::V_NaRuchMyszaZmienne(GdkEventMotion* event){
     if (event->state & GDK_BUTTON1_MASK){
        PrzesuwajAktualnieSterowane();
    }
}
void SterowanieMyszaVar_2::WybieraniePunktu(){
    renderowanie->UstawRysowanieTylkoPunktowZnazwami();
    auto idPunktu = ekran->StosNazwObiektuWpunkcie(ix,iy).top();
    if(idPunktu == -1)return;
    modyfikacjaPunktow.WyczyscIwstawJedenPunkt((float*)(idPunktu));
    
}