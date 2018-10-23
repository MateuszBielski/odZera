#include <FunkcjeIstruktury.h>

void WyswietlWartosciMacierzy4x4(float * macierz16){
   float m[4][4];
   memcpy(m,macierz16,16*sizeof(float));
   g_print("\nModel::Rysuj macierz modelview");
   for (int i = 0 ; i < 4 ; i++){
       g_print("\n");
       for (int j = 0 ; j < 4 ; j++)
        g_print("  %2.5f",m[j][i]);
   } 
}

void TransformujPikselDoPrzestrzeniSceny(int x, int y,float glebokosc,float*  pozycjaPunktu3D)
{
   int viewport[4]; glGetIntegerv(GL_VIEWPORT,viewport);
   double macierzModelWidok[16];
   glGetDoublev(GL_MODELVIEW_MATRIX,macierzModelWidok);
   double macierzRzutowania[16];
   glGetDoublev(GL_PROJECTION_MATRIX,macierzRzutowania);
   
   double wspolrzednePunktu3D[3];
   
   gluUnProject((double)x,(double)( viewport[3]-y),
               glebokosc,macierzModelWidok,macierzRzutowania,viewport,
                &wspolrzednePunktu3D[0],
                &wspolrzednePunktu3D[1],
                &wspolrzednePunktu3D[2]);
   
   for (int i=0;i<3;i++)
   {
       pozycjaPunktu3D[i]=(float)wspolrzednePunktu3D[i];
       //g_print("%2.3f  ",pozycjaPunktu3D[i]);
   }
       
} 
void TransformujPikselDoPrzestrzeniSceny(int x, int y,float*  pozycjaPunktu3D)
{
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble wspolrzednePunktu3D[3];
 
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
 
    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    glReadPixels( x, int(winY), 1, 1,GL_DEPTH_COMPONENT, GL_FLOAT, &winZ );// GL_STENCIL_INDEX
//    winZ = 0.0;
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &wspolrzednePunktu3D[0], &wspolrzednePunktu3D[1], &wspolrzednePunktu3D[2]);
//    g_print("\n2D %2.3f  %2.3f  %2.3f  3D: ",winX,winY,winZ);
    for (int i=0;i<3;i++)
   {
       pozycjaPunktu3D[i]=(float)wspolrzednePunktu3D[i];
//       g_print("%2.3f  ",pozycjaPunktu3D[i]);
   }
}
void Quat_to_Phi_a(float * q,float* phi,float* a){
    register int i = 0;
    float phi_przez_dwa = acos(q[3]);
    float sin_phi_przez_dwa = sin(phi_przez_dwa);
    for(i ; i < 3 ; i++){
        a[i] = (q[i])/sin_phi_przez_dwa;
    }
    *phi = 2 * phi_przez_dwa;
    
}
//wersja która działa dla obrotów indywidualnych bryły
void IloczynWektoraImacierzy4f(float * v, float * m, float * vDest){
    register int i = 0, j;
    
    //macierz zapisana rzędami - jest właściwa dla korekty obrotów
    for(i ; i < 4 ; i++){
        j = 0;vDest[i] = 0;
        for(j ; j < 4 ; j++)vDest[i] += m[i*4+j] * v[j];
//        vDest[i] = m[i] * v[0] + m[4+i] * v[1] + m[8+i] * v[2] + m[12+i] * v[3];//wersja macierzy zapisanej kolumnami
    }
}

//wersja która działa dla wykonania transformacji na punkcie we współrzędnych jednorodnych (x,y,z,1)
void IloczynMacierzyIwektora4f(float * m, float * v, float * vDest){
	vDest[0] = m[0]*v[0] + m[4]*v[1] + m[8]*v[2] + m[12]*v[3];
	vDest[1] = m[1]*v[0] + m[5]*v[1] + m[9]*v[2] + m[13]*v[3];
	vDest[2] = m[2]*v[0] + m[6]*v[1] + m[10]*v[2] + m[14]*v[3];
	vDest[3] = m[3]*v[0] + m[7]*v[1] + m[11]*v[2] + m[15]*v[3];
}

float DlugoscWektora3fv(float* wektor)
{
      float dlugosc=0;
      
      for (int i=0;i<3;i++){dlugosc+=(wektor[i]*wektor[i]);}
      return sqrt(dlugosc);
}

void NormujWektor3fv(float* wektor)
{
      float wsp=DlugoscWektora3fv(wektor);
      for (int i=0;i<3;i++){wektor[i]/=wsp;}
}
