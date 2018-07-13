#ifndef EKRANRYSUJACY_H
#define EKRANRYSUJACY_H
#include <EkranGL.h>
class EkranRysujacy : public EkranGL
{
public:
	EkranRysujacy();
	~EkranRysujacy();
private:
	virtual void UstawienieSceny();
	virtual void RysujScene();
    virtual void Oswietlenie();
};

#endif // EKRANRYSUJACY_H
