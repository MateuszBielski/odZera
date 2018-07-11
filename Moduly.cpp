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
    /*Wykonać  tablicę wskaźników do funkcji u uruchomic je w pętli
     * */
	renderowanie = std::make_shared<Renderowanie>();
    
    pEkranGL->EmitujSygnalRysuj().connect(sigc::mem_fun(*renderowanie,&Renderowanie::Renderuj));
//	oknoGL->signal_delete_event().connect(sigc::mem_fun(*this,&Moduly::on_my_delete_event));
}
bool Moduly::on_my_delete_event(GdkEventAny* any_event)
{
//	delete oknoGL;
	oknoGL = nullptr;//w tym momencie znika przycisk który należy do tego okna a jest widoczny oknie oknoGlowne
	Komunikat("Moduly::on_my_delete_event");
	return true;
}
