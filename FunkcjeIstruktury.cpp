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
void IloczynMacierzyIwektora(float * m, float * v, float * vDest){
    register int i = 0, j = 0;
    for(i ; i < 4 ; i++){
        vDest[i] = m[i*4+0] * v[0] + m[i*4+1] * v[1] + m[i*4+2] * v[2] + m[i*4+3] * v[3];//możliwe że macierz przetransponować
    }
}