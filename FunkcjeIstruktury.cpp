#include <FunkcjeIstruktury.h>

void WyswietlWartosciMacierzy4x4(float * macierz16){
   float m[4][4];
   memcpy(m,macierz16,16*sizeof(float));
   g_print("\nModel::Rysuj macierz modelview");
   for (int i = 0 ; i < 4 ; i++){
       g_print("\n");
       for (int j = 0 ; j < 4 ; j++)
        g_print("  %2.3f",m[j][i]);
   } 
}

void TransformujPikselDoPrzestrzeniSceny(POINT pozycjaPiksela,float glebokosc,float*  pozycjaPunktu3D)
{
   int viewport[4]; glGetIntegerv(GL_VIEWPORT,viewport);
   double macierzModelWidok[16];
   glGetDoublev(GL_MODELVIEW_MATRIX,macierzModelWidok);
   double macierzRzutowania[16];
   glGetDoublev(GL_PROJECTION_MATRIX,macierzRzutowania);
   
   double wspolrzednePunktu3D[3];
   
   gluUnProject((double)pozycjaPiksela.x,(double)( viewport[3]-pozycjaPiksela.y),
               glebokosc,macierzModelWidok,macierzRzutowania,viewport,
                &wspolrzednePunktu3D[0],
                &wspolrzednePunktu3D[1],
                &wspolrzednePunktu3D[2]);
                
   //g_print("\nTransformujPikselDoPrzestrzeniSceny 2D %2.3f %2.3f    ",pozycjaPiksela.x,( viewport[3]-pozycjaPiksela.y));
   
   for (int i=0;i<3;i++)
   {
       pozycjaPunktu3D[i]=(float)wspolrzednePunktu3D[i];
       //g_print("%2.3f  ",pozycjaPunktu3D[i]);
   }
       
} 