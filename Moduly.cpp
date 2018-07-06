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
}
