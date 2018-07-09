#include "Renderowanie.h"

Renderowanie::Renderowanie()
{
}

Renderowanie::~Renderowanie()
{
}
void Renderowanie::Renderuj()
{
	Komunikat("Renderowanie::Renderuj()");
}
void Renderowanie::PodlaczSygnalZ(std::shared_ptr<EkranGL> ekran)
{
	//ekran->sRysuj.connect(sigc::mem_fun(*this,&Renderowanie::Renderuj));
}
