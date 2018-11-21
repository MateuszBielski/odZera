#ifndef MODELETEMPLATE_CPP
#define MODELETEMPLATE_CPP
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
    if constexpr(flagi & Z_WIDOCZNYMI_PUNKTAMI){
        RysujPunktyZnazwami();
        g_print("\nZ_WIDOCZNYMI_PUNKTAMI");
    }
	RysujGeometrie();
	if(czyPushMatrix)glPopMatrix();
}

template<int flagi,int rodzajPrymitywu>
void Model::RysujGeometrieTemplate()
{
	glBegin(rodzajPrymitywu);
    glColor3fv(kolor);
	for(int s = 0 ; s < ileNormalnych ;s++){
		glNormal3fv(&normalne[s*3]);
		for(int w = 0 ; w < ileNaroznikowSciany ;w++)glVertex3fv(&vertexy[indeksyNaroznikow[s*ileNaroznikowSciany + w]*3]);
	}
    glEnd();
}
#endif