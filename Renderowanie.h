#ifndef RENDEROWANIE_H
#define RENDEROWANIE_H
#include <Komunikat.h>
#include <EkranGL.h>

class Renderowanie
{
public:
	Renderowanie();
	~Renderowanie();
	void Renderuj();
	void PodlaczSygnalZ(std::shared_ptr<EkranGL>);
	
};

#endif // RENDEROWANIE_H
