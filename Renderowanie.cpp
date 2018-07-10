#include "Renderowanie.h"

Renderowanie::Renderowanie()
{
}

Renderowanie::~Renderowanie()
{
}
void Renderowanie::Renderuj( bool b, int i)
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
void Renderowanie::on_server_something(bool a, int b)
{
  std::cout << "Renderowanie::on_server_something() called with these parameters: "
      << a << ", " << b << std::endl;
}