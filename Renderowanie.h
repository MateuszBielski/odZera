#ifndef RENDEROWANIE_H
#define RENDEROWANIE_H
#include <Komunikat.h>
#include <EkranGL.h>
#include <sigc++/sigc++.h>

class Renderowanie : public sigc::trackable
{
public:
	Renderowanie();
	~Renderowanie();
	void Renderuj(int i, bool b);
	void PodlaczSygnalZ(std::shared_ptr<EkranGL>);
	
};

#endif // RENDEROWANIE_H
