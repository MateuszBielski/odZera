#include <Okno1.h>
Okno1::Okno1()
{
	
}
bool Okno1::Inicjuj()
{
	
	this->set_size_request(200,200);
	PodlaczenieSygnalow();
    ustawElementyOkna();
	UstawieniaKlasyDziedziczacej();
	return true;
}
bool Okno1::on_configure_event(GdkEventConfigure* event)
{
	
}
int Okno1::PodlaczenieSygnalow()
{
    
}
void Okno1::ustawElementyOkna()
{
	
}
void Okno1::NowyWatek()
{

}


