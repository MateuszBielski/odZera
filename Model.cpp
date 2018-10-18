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
    glMultMatrixf(&mojeWspolrzedneImacierzeSterowania->macierzObrotu[0][0]);
}

void Model::UstalM_Pos(float* zTablicy)
{
	for(short i= 0 ; i < 3 ; i++)mojeWspolrzedneImacierzeSterowania->m_Pos[i] = zTablicy[i];
}
void Model::UstawPolozenieSrodkaModelu(float* zeWskaznika)
{
	for(int i = 0 ; i < 3 ; i++)srodekModelu[i] = zeWskaznika[i];
}
void Model::WlaczJednorazowoWymienneFunkcje(int jakieFunkcjeFlagi){
    if(jakieFunkcjeFlagi & UTRWAL_MPOS_Z_AKTUALNEJ_MACIERZY){
        FunkcjaWymienna = &Model::UtrwalMposZaktualnejMacierzy;
    }
	if(jakieFunkcjeFlagi & ZESTAW_FUNKCJI){
		FunkcjeWymienne.push_back(F_pierwsza);
		FunkcjeWymienne.push_back(F_trzecia);
		FunkcjeWymienne.push_back(F_druga);
		FunkcjaWymienna = &Model::WykonajWszystkieFunkcjeZestawu;
	}
}
void Model::UtrwalMposZaktualnejMacierzy()
{
    float tempDest[4], tempM_pos[4];
    float macierzModelWidok[16];
    for(int i = 0; i < 3 ; i++)tempM_pos[i] = mojeWspolrzedneImacierzeSterowania->m_Pos[i];
    tempM_pos[3] = 0;
    glGetFloatv(GL_MODELVIEW_MATRIX,macierzModelWidok);
    IloczynMacierzyIwektora4f(macierzModelWidok,tempM_pos,tempDest);
    for(int i = 0; i < 3 ; i++)mojeWspolrzedneImacierzeSterowania->m_Pos[i] = tempDest[i];
//    g_print("\nModel::UtrwalMposZaktualnejMacierzy mój numer %d",jestemZaladowanyPodNumerem);
    FunkcjaWymienna = &Model::DomyslnaWymiennaFunkcja;
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
	FunkcjaWymienna = &Model::DomyslnaWymiennaFunkcja;
}
void Kostka::RysujGeometrieNowe()
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
void Kostka::RysujGeometrie()
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
