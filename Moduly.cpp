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
    
    pEkranGL = std::make_shared<EkranRysujacy>();
    pEkranGL->Inicjuj();
    pEkranGL->ZainstalujSieW(oknoGL->refVBox());
    
    sterowanie = std::make_unique<SterowanieMysza>();
	sterowanie->PodlaczanieSygnalow(*pEkranGL);
	sterowanie->PodlaczSygnalPrzeksztalcenieWidoku(*pEkranGL);
    /*Wykonać  tablicę wskaźników do funkcji u uruchomic je w pętli
     * */
	renderowanie = std::make_shared<Renderowanie>();
    pEkranGL->EmitujSygnalRysuj().connect(sigc::mem_fun(*renderowanie,&Renderowanie::Renderuj));

}

