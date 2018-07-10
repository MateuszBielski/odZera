#include "Renderowanie.h"

Renderowanie::Renderowanie()
{
}

Renderowanie::~Renderowanie()
{
}
void Renderowanie::Renderuj(int i, bool b)
{
	Komunikat("Renderowanie::Renderuj()");
    g_print(", %d, %d",i,b);
}
void Renderowanie::PodlaczSygnalZ(std::shared_ptr<EkranGL> ekran)
{
	ekran->sRysuj.connect(sigc::mem_fun(*this,&Renderowanie::Renderuj));
}
void Renderowanie::PodlaczSygnalZ(EkranGL& ekran)
{
    auto sygnal = ekran.sRysuj;
    sygnal.connect(sigc::mem_fun(*this,&Renderowanie::Renderuj));
}
