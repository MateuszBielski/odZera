#ifndef GRUPAMODELI_H
#define GRUPAMODELI_H
#include <Model.h>
class GrupaModeli : public Model
{
public:
	GrupaModeli();
	~GrupaModeli();
	void DodajDoMnie(Model&&);
private:
	using listaModeli = std::list<Model>;
	listaModeli mojeModele;
};

#endif // GRUPAMODELI_H
