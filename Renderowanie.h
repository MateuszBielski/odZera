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
	void Renderuj( bool b, int i);
	
};

#endif // RENDEROWANIE_H
