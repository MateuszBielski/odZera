#include <Model.h>
#include <FunkcjeIstruktury.h>

Model::Model()
{
    polozenie3f[0] = 0.0f;
    polozenie3f[1] = 0.0f;
    polozenie3f[2] = 0.0f;
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
	float x=1.0;
	float y=1.0;
    
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
	if(wskWektoraPolozeniaWyliczanyWsterowaniu != nullptr)memcpy(polozenie3f,wskWektoraPolozeniaWyliczanyWsterowaniu,3*sizeof(float));
	glTranslatef(polozenie3f[0],polozenie3f[1],polozenie3f[2]);
    if(mnozeniePrzezMacierz != nullptr)glMultMatrixf(mnozeniePrzezMacierz);
    if(pokazujWartosci){
        float macierzModelWidok[16];
        glGetFloatv(GL_MODELVIEW_MATRIX,macierzModelWidok);
        WyswietlWartosciMacierzy4x4(macierzModelWidok);
    }
	RysujGeometrie();
	if(czyPushMatrix)glPopMatrix();
}


void Model::UstalPolozenie3f(float* zTablicy)
{
	for(short i= 0 ; i < 3 ; i++)polozenie3f[i] = zTablicy[i];
}
void Model::WezWskaznikiMacierzyObrotuIpolozenia(float* adrMacierzy,float* adrPolozenia)
{
	mnozeniePrzezMacierz = adrMacierzy;
	wskWektoraPolozeniaWyliczanyWsterowaniu = adrPolozenia;
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
void Kostka::RysujGeometrie()
{
    float x=1.0f, y = x, z = x;
    //glShadeModel(GL_FLAT);//cieniowanie kolorem GK_SMOOTH, GL_FLAT
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
