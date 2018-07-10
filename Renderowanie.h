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
    void on_server_something(bool a, int b);
	void PodlaczSygnalZ(std::shared_ptr<EkranGL>);
    void PodlaczSygnalZ(EkranGL&);
	
};

#endif // RENDEROWANIE_H
