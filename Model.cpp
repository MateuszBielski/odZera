#include <Model.h>
#include <FunkcjeIstruktury.h>


Model::Model()
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
template<int flagi>
void Model::RysujTemplate()
{
	if constexpr(flagi & Z_NAZWAMI_MODELI){
		glLoadName(jestemZaladowanyPodNumerem);
	}
    if(czyPushMatrix)glPushMatrix();
    TransformacjePrzedRysowaniem();
    (this->*FunkcjaWymienna)();
    if(pokazujWartosci){
        float macierzModelWidok[16];
        glGetFloatv(GL_MODELVIEW_MATRIX,macierzModelWidok);
        WyswietlWartosciMacierzy4x4(macierzModelWidok);
    }
	RysujGeometrie();
	if(czyPushMatrix)glPopMatrix();
}
void Model::Rysuj(){
	RysujTemplate<0>();
}
void Model::RysujZnazwami()
{
	RysujTemplate<Z_NAZWAMI_MODELI>();
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
    if(jakieFunkcjeFlagi & PRZELICZ_PUNKTY){
        FunkcjaWymienna = &Model::PrzeliczPunktyZaktualnejMacierzy;
        jakaFunkcja = "PrzeliczPunktyZaktualnejMacierzy";
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
//		mojeWspolrzedneImacierzeSterowania->m_Pos[i] = 0;
	}
    tempM_pos[3] = 1;
    glGetFloatv(GL_MODELVIEW_MATRIX,macierzModelWidok);
    WyswietlWartosciMacierzy4x4(macierzModelWidok);
    IloczynMacierzyIwektora4f(macierzModelWidok,tempM_pos,tempDest);
//	IloczynWektoraImacierzy4f(tempM_pos,macierzModelWidok,tempDest);
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
	g_print("\nbazowa funkcja Model::PrzeliczPunktyZaktualnejMacierzy");
    UstawPustaDomyslnaFunkcje();
}
void Model::UtrwalPrzeksztalcenia(){
    glLoadIdentity();
    WlaczJednorazowoWymienneFunkcje(PRZELICZ_PUNKTY);
    Rysuj();
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
/*spModel ModelPusty::SprobujPrzywrocic()
{
    return *tuJestemPelny;
}*/
ModelPusty::~ModelPusty()
{
//    g_print("\ndestruktor ModelPusty");
}
itLspModel ModelPusty::AdresPelnegoObiektu()
{
    return tuJestemPelny;
}

Kostka::Kostka()
{
    UdostepnijBazieVertexyInormalne(&p[0][0],8,&n[0][0],6);
    float srodek[] = {0.0f,0.0f,0.0f};
    UstawPolozenieSrodkaModelu(srodek);
    ObliczPunktyKorzystajacZdlugosciIsrodka(1.0,srodek);
}
Kostka::Kostka(float* zeWskaznika)
{
    UdostepnijBazieVertexyInormalne(&p[0][0],8,&n[0][0],6);
    UstawPolozenieSrodkaModelu(zeWskaznika);
    ObliczPunktyKorzystajacZdlugosciIsrodka(1.0,zeWskaznika);
}
/*void Kostka::UstawPolozenieSrodkaModelu(float* zeWskaznika)
{
	Model::UstawPolozenieSrodkaModelu(zeWskaznika);
	
}*/
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
    unsigned short nr[] = {	0,1,5,4,
							3,7,6,2,
							2,6,5,1,
							3,0,4,7,
							4,5,6,7,
							0,3,2,1};
	glBegin(GL_QUADS);
        glColor3f(0.6,0.8,0.7);
//        g_print("\nKostka::RysujGeometrie:");//--
	for(int s = 0 ; s < 6 ;s++){
		glNormal3fv(n[s]);
//       g_print("\n  %2.3f,  %2.3f,  %2.3f",n[s][0],n[s][1],n[s][2]);//--
		for(int w = 0 ; w < 4 ;w++)glVertex3fv(p[nr[s*4 + w]]);
	}
    glEnd();
}
void Kostka::PrzeliczPunktyZaktualnejMacierzy()
{
    float stare[4],nowe[4],m[16];
    auto kopiuj3 = [](float* zr,float* cel){
        for(int j = 0; j < 3 ; j++){
            cel[j] = zr[j];
//            g_print("   %2.3f %2.3f",cel[j],zr[j]);
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
//        IloczynMacierzyIwektora4f(&mojeWspolrzedneImacierzeSterowania->macierzObrotu[0][0],stare,nowe);//to nie działa przy utrwalaniu modeli z grupy, bo są wcześniejsze transformacje
        kopiuj3(nowe,n[i]);
//        pokazPunkt(nowe);
   }
//   PunktMiedzyWektorami(n[0],n[1]);
//   PunktMiedzyWektorami(n[2],n[3]);
//   PunktMiedzyWektorami(n[4],n[5]);
   kopiuj3(srodekModelu,stare);
//    IloczynWektoraImacierzy4f(stare,m,nowe);
    IloczynMacierzyIwektora4f(m,stare,nowe);
    kopiuj3(nowe,srodekModelu);
   UstawPustaDomyslnaFunkcje();
}
Czworoscian::Czworoscian(){
    UdostepnijBazieVertexyInormalne(&p[0][0],4,&n[0][0],4);
    float srodek[] = {0,0,0};
    ObliczPunktyKorzystajacZdlugosciIsrodka(1.5,srodek);
}
Czworoscian::Czworoscian(float * srodekModelu){
    UdostepnijBazieVertexyInormalne(&p[0][0],4,&n[0][0],4);
    ObliczPunktyKorzystajacZdlugosciIsrodka(1.5,srodekModelu);
}
void Czworoscian::ObliczPunktyKorzystajacZdlugosciIsrodka(float a, float* c){
    g_print("\nCzworoscian::ObliczPunkty");
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
    g_print("\nsrodek czworościanu %2.3f, %2.3f, %2.3f",srodekGeometryczny[0],srodekGeometryczny[1],srodekGeometryczny[2]);
    for(int i = 0; i < 4; i++)p[i][1] -=srodekGeometryczny[1];
    //dodać środek modelu************
    for(int i = 0; i < 4; i++){
		for(int j = 0; j < 3; j++)p[i][j]+=c[j];
	}
    //normalne
    n[0][0] = 0;n[0][1] = -1;n[0][0] = 0;
    n[1][0] = 0;n[1][1] = h/3.0;n[1][2] = H;
    n[2][0] = h;n[2][1] = a*h/(3*H);n[2][2] = -a/2;
    n[3][0] = -h;n[3][1] = a*h/(3*H);n[3][2] = -a/2;
    for(int i = 1 ; i < 4 ; i++)NormujWektor3fv(n[i]);
}
void Czworoscian::RysujGeometrie(){
   unsigned short nr[] = {	0,2,1,
							0,1,3,
							1,2,3,
							0,3,2};
	glBegin(GL_TRIANGLES);
        glColor3f(1.0,1.0,0.0);
	for(int s = 0 ; s < 4 ;s++){
		glNormal3fv(n[s]);
		for(int w = 0 ; w < 3 ;w++)glVertex3fv(p[nr[s*3 + w]]);
	}
    glEnd(); 
}
void Ostroslup::RysujGeometrie(){
    float x=1.0;
	float y=1.0;
    
    glRotatef(90,1,0,0);
    for(int i =0; i < 3; i++){
        glColor3f(0.4*i,0.9,0.0);
        glTranslatef(0,0,0.5);
        glRotatef(-30,1,0,0);
        glNormal3f(0,0,1.0);
        glBegin(GL_TRIANGLES);
        glVertex3f(-x,-y,0);
        glVertex3f(x,-y,0);
        glVertex3f(0,y,0);
        glEnd();
        glRotatef(30,1,0,0);
        glTranslatef(0,0,-0.5);
        glRotatef(120,0,1,0);
    }
    
}
void TrzyKwadraty::RysujGeometrie()
{
    glBegin(GL_QUADS);
    glNormal3f(0,1.0,0);
    glColor3f(0.8,0.8,0.8);
    glVertex3f(0,0,0);
    glNormal3f(0,1.0,0);
    glVertex3f(1,0,0);
    glNormal3f(0,1.0,0);
    glVertex3f(1,0,-1);
    glNormal3f(0,1.0,0);
    glVertex3f(0,0,-1);
    glEnd();
    
    glBegin(GL_QUADS);
    glColor3f(0.8,0.8,0.8);
    glNormal3f(0,1.0,0);
    glVertex3f(0,-1,2);
    glNormal3f(0,1.0,0);
    glVertex3f(1,-1,2);
    glNormal3f(0,1.0,0);
    glVertex3f(1,-1,1);
    glNormal3f(0,1.0,0);
    glVertex3f(0,-1,1);
    glEnd();
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
//    JakaNormalna();
    for(int i = 0 ; i < ileNormalnych ; i++){
//        float* pNormalne = (float*)(normalne[i]);
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
WidokCechModelu::WidokCechModelu(){
//    przechowanieSterowania = mojeWspolrzedneImacierzeSterowania;
}
void WidokCechModelu::RysujDla(std::shared_ptr<Model> wsk){
    if(wsk.get() == this)return;
    if(wskazywany != nullptr){
//        wskazywany->MacierzaObrotuPrzeliczPunktyIjaWyzeruj();//nie spełnia oczekiwań
        wskazywany->UtrwalPrzeksztalcenia();
    for(int i = 0 ; i < 3 ; i++){
            wskazywany->SrodekModelu()[i] += mojeWspolrzedneImacierzeSterowania->m_Pos[i];
            mojeWspolrzedneImacierzeSterowania->m_Pos[i] = 0;
        }
//        g_print("\nSrodek poprzedniego po zmianie %2.3f,  %2.3f,  %2.3f",wskazywany->SrodekModelu()[0],wskazywany->SrodekModelu()[1],wskazywany->SrodekModelu()[2]);    
    }
    wskazywany = wsk;
    zastepczaM_Pos = wskazywany->mojeWspolrzedneImacierzeSterowania->m_Pos;
    zastepczaSrodek = wskazywany->SrodekModelu();
    g_print("\nSrodek wybranego %2.3f,  %2.3f,  %2.3f",wskazywany->SrodekModelu()[0],wskazywany->SrodekModelu()[1],wskazywany->SrodekModelu()[2]);
}
void WidokCechModelu::RysujGeometrie(){
    
    znacznik.RysujGeometrie();
}
void WidokCechModelu::TransformacjePrzedRysowaniem()
{
    float s[3];
    for(int i = 0 ; i < 3 ; i++){
        s[i] = zastepczaM_Pos[i]+zastepczaSrodek[i]+mojeWspolrzedneImacierzeSterowania->m_Pos[i];//
    }
    glTranslatef(s[0],s[1],s[2]);
}
