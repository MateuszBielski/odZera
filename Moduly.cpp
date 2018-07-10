#include <Moduly.h>

Moduly::Moduly()
{
}

Moduly::~Moduly()
{
}

bool Moduly::DolaczDo(spOkno1 okno)
{
    if(okno == nullptr)return false;
    oknoGlowne = okno;
    return true;
}
int Moduly::Uruchom()
{
    oknoGL = std::make_unique<OknoGL>();
    oknoGL->UstawIzainstalujPrzyciskW(oknoGlowne->refVBox());
    sterowanie = make_unique<SterowanieMysza>();
    sterowanie->PodlaczanieSygnalow(*oknoGL);
//    sterowanie->PodlaczanieSygnalow(*(oknoGL->pEkranGL)); - w tej wersji powoduje naruszenie ochrony pamięci
    /*Wykonać  tablicę wskaźników do funkcji u uruchomic je w pętli
     * */
	renderowanie = std::make_shared<Renderowanie>();
	renderowanie->PodlaczSygnalZ(oknoGL->WskEkranGL());
	//oknoGL->WskEkranGL()->sRysuj.connect(sigc::mem_fun(*renderowanie,&Renderowanie::Renderuj));// ta linia powoduje błąd przy uruchomieniu
	
	 
}
