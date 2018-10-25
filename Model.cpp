#include <Model.h>
#include <FunkcjeIstruktury.h>


Model::Model()
{
    mojeWspolrzedneImacierzeSterowania = std::make_shared<WspolrzedneImacierzeSterowania>();
    for(int i = 0 ; i < 3 ; i++)srodekModelu[i] = 0.0;
}
Model::~Model()
{
	if(vertexy) delete [] vertexy;
    if(indeksy) delete [] indeksy;
    if(kolory) delete [] kolory;
    if(normalne) delete [] normalne;
}
void Model::UzywajPushMatrix(bool jak)
{
	czyPushMatrix = jak;
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
void Model::Rysuj()
{
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
    g_print("\nWlaczJednorazowoWymienneFunkcje %d",jestemZaladowanyPodNumerem);
    if(jakieFunkcjeFlagi & UTRWAL_MPOS_Z_AKTUALNEJ_MACIERZY){
        FunkcjaWymienna = &Model::UtrwalMposZaktualnejMacierzy;
    }
	if(jakieFunkcjeFlagi & ZESTAW_FUNKCJI){
		FunkcjeWymienne.push_back(&Model::F_pierwsza);
		FunkcjeWymienne.push_back(&Model::F_trzecia);
		FunkcjeWymienne.push_back(&Model::F_druga);
		FunkcjaWymienna = &Model::WykonajWszystkieFunkcjeZestawu;
	}
    if(jakieFunkcjeFlagi & PRZELICZ_PUNKTY){
        FunkcjaWymienna = &Model::PrzeliczPunktyZaktualnejMacierzy;
    }
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

void Model::RysujZnazwami()
{
//    g_print(" %d",jestemZaladowanyPodNumerem);
    glLoadName(jestemZaladowanyPodNumerem);
    Rysuj();
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


Kostka::Kostka()
{
    ileNormalnych = 6;
    normalne = &n[0][0];
    float srodek[] = {0.0f,0.0f,0.0f};
    UstawPolozenieSrodkaModelu(srodek);
    ObliczPunktyKorzystajacZdlugosciIsrodka(1.0,srodek);
}
Kostka::Kostka(float* zeWskaznika)
{
    
    ileNormalnych = 6;
    normalne = &n[0][0];
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
    stare[3] = 1.0f;
    glGetFloatv(GL_MODELVIEW_MATRIX,m);
//    WyswietlWartosciMacierzy4x4(m);
   for(int i  = 0; i < 8 ; i++){
        kopiuj3(p[i],stare);
//        IloczynWektoraImacierzy4f(stare,m,nowe);
        IloczynMacierzyIwektora4f(m,stare,nowe);
        kopiuj3(nowe,p[i]);
   }
   for(int i  = 0; i < 6 ; i++){
        kopiuj3(n[i],stare);
//        pokazPunkt(stare);
//        IloczynWektoraImacierzy4f(stare,m,nowe);
        IloczynMacierzyIwektora4f(&mojeWspolrzedneImacierzeSterowania->macierzObrotu[0][0],stare,nowe);
        kopiuj3(nowe,n[i]);
//        NormujWektor3fv(n[i]);
//        pokazPunkt(nowe);
   }
   kopiuj3(srodekModelu,stare);
//    IloczynWektoraImacierzy4f(stare,m,nowe);
    IloczynMacierzyIwektora4f(m,stare,nowe);
    kopiuj3(nowe,srodekModelu);
   UstawPustaDomyslnaFunkcje();
}
void Kostka::RysujGeometrieStare2()
{
    float d = 0.5;//połowa długości boku
    glColor3f(0.6,0.8,0.7);
    float cX=srodekModelu[0], cY=srodekModelu[1], cZ=srodekModelu[2];
    glBegin(GL_QUADS);
    //przód
    glNormal3f(0,0,1.0);
    glVertex3f(cX-d,cY-d,cZ+d);//0,0,0
    glVertex3f(cX+d,cY-d,cZ+d);//x,0,0
    glVertex3f(cX+d,cY+d,cZ+d);//x,y,0
    glVertex3f(cX-d,cY+d,cZ+d);//0,y,0
    
    //tył
    glNormal3f(0,0,-1.0);//
    //glColor3f(0.8,0.3,0.0);
    glVertex3f(cX-d,cY-d,cZ-d);//0,0,-z
    glVertex3f(cX-d,cY+d,cZ-d);//0,y,-z
    glVertex3f(cX+d,cY+d,cZ-d);//x,y,-z
    glVertex3f(cX+d,cY-d,cZ-d);//x,0,-z
    
    //prawy
    glNormal3f(1.0,0,0);
    //glColor3f(0.2,0.7,0.0);
    glVertex3f(cX+d,cY-d,cZ-d);//x,0,-z
    glVertex3f(cX+d,cY+d,cZ-d);//x,y,-z
    glVertex3f(cX+d,cY+d,cZ+d);//x,y,0
    glVertex3f(cX+d,cY-d,cZ+d);//x,0,0
    
    //lewy
    glNormal3f(-1.0,0,0);
    //glColor3f(0.2,0.7,0.0);
    glVertex3f(cX-d,cY-d,cZ-d);//0,0,-z
    glVertex3f(cX-d,cY-d,cZ+d);//0,0,0
    glVertex3f(cX-d,cY+d,cZ+d);//0,y,0
    glVertex3f(cX-d,cY+d,cZ-d);//0,y,-z
    
    //góra
    glNormal3f(0,1.0,0);
    //glColor3f(0.2,0.0,0.8);
    glVertex3f(cX-d,cY+d,cZ+d);//0,y,0
    glVertex3f(cX+d,cY+d,cZ+d);//x,y,0
    glVertex3f(cX+d,cY+d,cZ-d);//x,y,-z
    glVertex3f(cX-d,cY+d,cZ-d);//0,y,-z
    
    //dół
    glNormal3f(0,-1.0,0);
    //glColor3f(0.2,0.0,0.8);
    glVertex3f(cX-d,cY-d,cZ+d);//0,0,0
    glVertex3f(cX-d,cY-d,cZ-d);//0,0,-z
    glVertex3f(cX+d,cY-d,cZ-d);//x,0,-z
    glVertex3f(cX+d,cY-d,cZ+d);//x,0,0
    glEnd();
}

void Kostka::RysujGeometrieStare()
{
    float x=1.0f, y = x, z = x;
    glTranslatef(-0.5,-0.5,0.5);
    glBegin(GL_QUADS);
    //przód
    glNormal3f(0,0,1.0);
    glColor3f(0.8,0.8,0.8);
    glVertex3f(0,0,0);
    glVertex3f(x,0,0);
    glVertex3f(x,y,0);
    glVertex3f(0,y,0);
    
    //tył
    glNormal3f(0,0,-1.0);
    //glColor3f(0.8,0.3,0.0);
    glVertex3f(0,0,-z);
    glVertex3f(0,y,-z);
    glVertex3f(x,y,-z);
    glVertex3f(x,0,-z);
    
    //prawy
    glNormal3f(1.0,0,0);
    //glColor3f(0.2,0.7,0.0);
    glVertex3f(x,0,-z);
    glVertex3f(x,y,-z);
    glVertex3f(x,y,0);
    glVertex3f(x,0,0);
    
    //lewy
    glNormal3f(-1.0,0,0);
    //glColor3f(0.2,0.7,0.0);
    glVertex3f(0,0,-z);
    glVertex3f(0,0,0);
    glVertex3f(0,y,0);
    glVertex3f(0,y,-z);
    
    //góra
    glNormal3f(0,1.0,0);
    //glColor3f(0.2,0.0,0.8);
    glVertex3f(0,y,0);
    glVertex3f(x,y,0);
    glVertex3f(x,y,-z);
    glVertex3f(0,y,-z);
    
    //dół
    glNormal3f(0,-1.0,0);
    //glColor3f(0.2,0.0,0.8);
    glVertex3f(0,0,0);
    glVertex3f(0,0,-z);
    glVertex3f(x,0,-z);
    glVertex3f(x,0,0);
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
