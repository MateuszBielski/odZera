#ifndef GRUPAMODELI_H
#define GRUPAMODELI_H
#include <Model.h>

class GrupaModeli : public Model
{
public:
	GrupaModeli();
	~GrupaModeli();
	itLspModel DodajDoMnie(spModel);
    virtual void Rysuj() override;
    virtual void RysujZnazwami() override;
    virtual void TransformacjePrzedRysowaniem() override;
    void WyliczSrodekCiezkosci();
    void UtrwalPrzeksztalceniaMoichModeli();
	virtual void WlaczJednorazowoWymienneFunkcje(int jakieFunkcjeFlagi) override;
private:
	using listaModeli = std::list<spModel>;
	listaModeli mojeModele;
    float srodekCiezkosci[3];
};

#endif // GRUPAMODELI_H
