#include <Model.h>
//#include <FunkcjeIstruktury.h>


Model::Model():kolor{0.6,0.8,0.7}
{
    mojeWspolrzedneImacierzeSterowania = std::make_shared<WspolrzedneImacierzeSterowania>();
    srodekModelu = &srodekModeluTab[0];
    for(int i = 0 ; i < 3 ; i++)srodekModelu[i] = 0.0;
}
Model::~Model()
{
	/*if(vertexy) delete [] vertexy;
    if(indeksy) delete [] indeksy;
    if(kolory) delete [] kolory;
    if(normalne) delete [] normalne;*/
}
void Model::UzywajPushMatrix(bool jak)
{
	czyPushMatrix = jak;
}
void Model::UdostepnijBazieVertexyInormalne(float * v,int ileV,float * n,int ileN){
    vertexy = v;
    ileVertexow = ileV;
    normalne = n;
    ileNormalnych = ileN;
}
void Model::UdostepnijBazieIndeksyWierzcholkow(unsigned short * nr, unsigned short ile){
	indeksyNaroznikow = nr;
    ileNaroznikowSciany = ile;
}
void Model::Rysuj(int flagi)
{
    RysujGeometrieOdpowiednio = &Model::RysujGeometrie;
    switch(flagi){
        case 0:
        RysujTemplate<0>();
        break;
        case Z_NAZWAMI_MODELI:
        RysujTemplate<Z_NAZWAMI_MODELI>();
        break;
        case Z_WIDOCZNYMI_PUNKTAMI:
        RysujTemplate<Z_WIDOCZNYMI_PUNKTAMI>();
//        RysujTylkoPunktyZnazwami();
        break;
        case TYLKO_PUNKTY_Z_NAZWAMI:
//        RysujTemplate<TYLKO_PUNKTY_Z_NAZWAMI>();
//        RysujTylkoPunktyZnazwami();
        RysujGeometrieOdpowiednio = &Model::RysujTylkoPunktyZnazwami;
        RysujTemplate<0>();
        break;
    }
}
void Model::RysujWidocznePunkty()
{
    glColor3f(1.0,0.0,0.0);
    glPointSize(7.0);
    glBegin(GL_POINTS);
	for(int ve = 0 ; ve < ileVertexow ;ve++){
//		glNormal3fv(&normalne[s*3]);
		glVertex3fv(&vertexy[ve*3]);
	}
    glEnd(); 
}

void Model::RysujTylkoPunktyZnazwami()
{
//    TransformacjePrzedRysowaniem();
    glPointSize(7.0);
    
	for(int ve = 0 ; ve < ileVertexow ;ve++){
        auto nazwa = (GLuint)(&vertexy[ve*3]);
        glLoadName(nazwa);//adres traktowany jako liczba
        glBegin(GL_POINTS);
		glVertex3fv(&vertexy[ve*3]);
        glEnd();
	}
}
void Model::TransformacjePrzedRysowaniem(){
    glTranslatef(mojeWspolrzedneImacierzeSterowania->m_Pos[0],mojeWspolrzedneImacierzeSterowania->m_Pos[1],mojeWspolrzedneImacierzeSterowania->m_Pos[2]);
    glTranslatef(srodekModelu[0],srodekModelu[1],srodekModelu[2]);
	glMultMatrixf(&mojeWspolrzedneImacierzeSterowania->macierzObrotu[0][0]);
	glTranslatef(-srodekModelu[0],-srodekModelu[1],-srodekModelu[2]);
}

void Model::UstalM_Pos(float* zTablicy)
{
	for(short i= 0 ; i < 3 ; i++)mojeWspolrzedneImacierzeSterowania->m_Pos[i] = zTablicy[i];
}
void Model::UstawPolozenieSrodkaModelu(float* zeWskaznika)
{
	for(int i = 0 ; i < 3 ; i++)srodekModelu[i] = zeWskaznika[i];
}

void Model::UstawPustaDomyslnaFunkcje()
{
   FunkcjaWymienna = &Model::DomyslnaWymiennaFunkcja; 
}
void Model::WlaczJednorazowoWymienneFunkcje(int jakieFunkcjeFlagi){
    
    std::string jakaFunkcja;
    if(jakieFunkcjeFlagi & UTRWAL_MPOS_Z_AKTUALNEJ_MACIERZY){
        FunkcjaWymienna = &Model::UtrwalMposZaktualnejMacierzy;
        jakaFunkcja = "UtrwalMposZaktualnejMacierzy";
    }
	if(jakieFunkcjeFlagi & ZESTAW_FUNKCJI){
		FunkcjeWymienne.push_back(&Model::F_pierwsza);
		FunkcjeWymienne.push_back(&Model::F_trzecia);
		FunkcjeWymienne.push_back(&Model::F_druga);
		FunkcjaWymienna = &Model::WykonajWszystkieFunkcjeZestawu;
        jakaFunkcja = "WykonajWszystkieFunkcjeZestawu";
	}
    if(jakieFunkcjeFlagi & UTRWAL_PUNKTY_NORMALNE_SRODEK){
        FunkcjaWymienna = &Model::PrzeliczPunktyZaktualnejMacierzy;
        jakaFunkcja = "PrzeliczPunktyZaktualnejMacierzy";
    }
    if(jakieFunkcjeFlagi & UTRWAL_SRODEK){
        FunkcjaWymienna = &Model::UtrwalSrodekZaktualnejMacierzy;
        jakaFunkcja = "UtrwalSrodekZaktualnejMacierzy";
    }
//    g_print("\nWlaczJednorazowoWymienneFunkcje %s model %d",jakaFunkcja.c_str(),jestemZaladowanyPodNumerem);
}
void Model::UtrwalMposZaktualnejMacierzy()
{
    auto pokaz = [](float * v){
		g_print("\n ");
		for(int i = 0; i < 4 ; i++)g_print("  %2.3f",v[i]);
	};
	float tempDest[4], tempM_pos[4];
    float macierzModelWidok[16];
    for(int i = 0; i < 3 ; i++){
		tempM_pos[i] = srodekModelu[i];
	}
    tempM_pos[3] = 1;
    glGetFloatv(GL_MODELVIEW_MATRIX,macierzModelWidok);
    WyswietlWartosciMacierzy4x4(macierzModelWidok);
    IloczynMacierzyIwektora4f(macierzModelWidok,tempM_pos,tempDest);
    for(int i = 0; i < 3 ; i++)srodekModelu[i] = tempDest[i];
    g_print("\nModel::UtrwalMposZaktualnejMacierzy mój numer %d",jestemZaladowanyPodNumerem);
	pokaz(tempM_pos);
	pokaz(tempDest);
    UstawPustaDomyslnaFunkcje();
	mojeWspolrzedneImacierzeSterowania->UstawWartosciStartowe();
}
void Model::F_pierwsza()
{
	g_print("\nfunkcja pierwsza");
}

void Model::F_druga()
{
	g_print("\nfunkcja druga");
}

void Model::F_trzecia()
{	
	g_print("\nfunkcja trzecia");
}

void Model::WykonajWszystkieFunkcjeZestawu()
{
	for(auto& funkcja : FunkcjeWymienne){
//z std::function poniższe 3 nie działają:
//		(this->*funkcja)();
//		(*funkcja)();
//		funkcja();
		(this->*funkcja)();
	}
	UstawPustaDomyslnaFunkcje();
}
void Model::PrzeliczPunktyZaktualnejMacierzy()
{
//	g_print("\nbazowa funkcja Model::PrzeliczPunktyZaktualnejMacierzy");
    float m[16],tylkoObroty[16];
    glGetFloatv(GL_MODELVIEW_MATRIX,m);
    auto WyluskajObrotyZmacierzyModelWidok = [&](){
        for(int k = 0 ; k < 16 ; k++)tylkoObroty[k] = m[k];
        for(int l = 12 ; l < 15 ; l++)tylkoObroty[l] = 0;
    };
    for(int i  = 0; i < ileVertexow ; i++){
        IloczynMacierzy4fIwektora3fzTymczasowym(m,&vertexy[i*3]);
    }
    WyluskajObrotyZmacierzyModelWidok();
    for(int i  = 0; i < ileNormalnych ; i++){
        IloczynMacierzy4fIwektora3fzTymczasowym(tylkoObroty,&normalne[i*3]);
    }
    IloczynMacierzy4fIwektora3fzTymczasowym(m,srodekModelu);
   UstawPustaDomyslnaFunkcje();
}
void Model::UtrwalSrodekZaktualnejMacierzy(){
    float m[16];
    glGetFloatv(GL_MODELVIEW_MATRIX,m);
    IloczynMacierzy4fIwektora3fzTymczasowym(m,srodekModelu);
    UstawPustaDomyslnaFunkcje();
}
void Model::UtrwalPrzeksztalcenia(){
    glLoadIdentity();
    WlaczJednorazowoWymienneFunkcje(UTRWAL_PUNKTY_NORMALNE_SRODEK);
    //Rysuj();
    Rysuj(0);
    mojeWspolrzedneImacierzeSterowania->UstawWartosciStartowe();
}
void Model::MacierzaObrotuPrzeliczPunktyIjaWyzeruj(){
    g_print("\nModel::MacierzaObrotuPrzeliczPunktyIjaWyzeruj()");
    for(int i = 0; i < ileVertexow ; i++){
        IloczynMacierzy4fIwektora3fzTymczasowym(&mojeWspolrzedneImacierzeSterowania->macierzObrotu[0][0],vertexy+3*i);
    }
    mojeWspolrzedneImacierzeSterowania->MacierzObrotuUstawJednostkowo();
}
void Model::SrodekUstawZzewnetrznegoAdresu(float* adr)
{
    srodekModelu = adr;
}
void Model::RysujOstroslup()
{
	float x=srodekModelu[0] + 1.0;
	float y=srodekModelu[1] + 1.0;
    
    for(int i =0; i < 3; i++){
    glColor3f(0.4*i,0.3,0.0);
        glTranslatef(0,0,0.5);
        glRotatef(-30,1,0,0);
        glBegin(GL_TRIANGLES);
        glVertex3f(-x,-y,0);
        glVertex3f(x,-y,0);
        glVertex3f(0,y,0);
        glEnd();
        glRotatef(30,1,0,0);
        glTranslatef(0,0,-1);
        glRotatef(120,0,1,0);
    }
    
}


//poniższe to pozostałość po użyciu tablicy wierzchołków w starszym innym projekcie
	/*glEnableClientState( GL_VERTEX_ARRAY );
    glVertexPointer( 3, GL_FLOAT, 0, vertexy );
    
    glEnableClientState(GL_COLOR_ARRAY);
    glColorPointer(3, GL_FLOAT, 0, kolory);
	
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer( GL_FLOAT, 0, normalne );
    glDrawElements( GL_TRIANGLE_STRIP, ileIndeksow, GL_UNSIGNED_INT,indeksy);
    glDisableClientState( GL_VERTEX_ARRAY );
    glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);*/



