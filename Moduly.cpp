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
    sterowanie->PodlaczanieSygnalow(*oknoGL);
//    sterowanie->PodlaczanieSygnalow(*(oknoGL->pEkranGL)); - w tej wersji powoduje naruszenie ochrony pamięci
    /*Wykonać  tablicę wskaźników do funkcji u uruchomic je w pętli
     * */
	renderowanie = std::make_shared<Renderowanie>();
    
    pEkranGL->signal_something().connect(sigc::mem_fun(*renderowanie,&Renderowanie::Renderuj));
    std::cout << "Before EkranGL::do_something()" << std::endl;
    pEkranGL->do_something();
	std::cout << "After EkranGL::do_something()" << std::endl;
	 
}
