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
    glTranslatef(mojeWspolrzedneImacierzeSterowania->m_Pos[0],mojeWspolrzedneImacierzeSterowania->m_Pos[1],mojeWspolrzedneImacierzeSterowania->m_Pos[2]);
    glMultMatrixf(&mojeWspolrzedneImacierzeSterowania->macierzObrotu[0][0]);
    if(pokazujWartosci){
        float macierzModelWidok[16];
        glGetFloatv(GL_MODELVIEW_MATRIX,macierzModelWidok);
        WyswietlWartosciMacierzy4x4(macierzModelWidok);
    }
	RysujGeometrie();
	if(czyPushMatrix)glPopMatrix();
}


void Model::UstalM_Pos(float* zTablicy)
{
	for(short i= 0 ; i < 3 ; i++)mojeWspolrzedneImacierzeSterowania->m_Pos[i] = zTablicy[i];
}
void Model::UstawPolozenieSrodkaModelu(float* zeWskaznika)
{
	for(int i = 0 ; i < 3 ; i++)srodekModelu[i] = zeWskaznika[i];
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
/*void Kostka::RysujGeometrieNieUdane(){
    float w[24]; //wierzchołki (x,y,z) dolna powierzchnia od lewego z przodu w prawo, góra tak samo
    float d = 0.5;//połowa długości boku

    short indeksyPlusow[] = {2,3,5,6,13,14,15,16,17,18,19,22};
    short indeksyMinusow[] = {0,1,4,7,8,9,10,11,12,20,21,23};
    
    short i,j,k,l;
    for(i = 0 ; i < 12 ; i++){
        j = indeksyMinusow[i];
        k = indeksyPlusow[i];
        l = j%3;
        w[j] = srodekModelu[l] - d;
        l = k%3;
        w[k] = srodekModelu[l] + d;
    }
    glBegin(GL_QUADS);
    //przód
    glColor3f(0.8,0.8,0.8);
    short iW[] = {0,1,5,4, 3,7,6,2, 2,6,5,4, 3,0,4,7, 4,5,6,7, 0,3,2,1};
    float iN[] ={0,0,1.0,0,0,-1.0,1.0,0,0,-1.0,0,0,0,1.0,0,0,-1.0,0}; 
    for(j = 0 ; j < 6; j++){
        //kolejne ściany
        glNormal3f(iN[3*j+0],iN[3*j+1],iN[3*j+2]);
        for(i = 0 ; i < 4 ; i++){
            k = 3*iW[j*6+i];
            glVertex3f(w[k],w[k+1],w[k+2]);
        }
    }
    glEnd();
    
    
}*/
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

