#ifndef GRUPAMODELI_H
#define GRUPAMODELI_H
#include <Model.h>
using spModel = std::shared_ptr<Model>;
class GrupaModeli : public Model
{
public:
	GrupaModeli();
	~GrupaModeli();
	void DodajDoMnie(spModel);
    virtual void Rysuj() override;
    virtual void RysujZnazwami() override;
private:
	using listaModeli = std::list<spModel>;
	listaModeli mojeModele;
};

#endif // GRUPAMODELI_H
