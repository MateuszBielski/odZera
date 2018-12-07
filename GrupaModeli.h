#ifndef GRUPAMODELI_H
#define GRUPAMODELI_H
#include <ModelPusty.h>

class GrupaModeli : public Model
{
public:
	GrupaModeli();
	~GrupaModeli();
	itLspModel DodajDoMnie(spModel);
    spModel WydzielZeMnieKorzystajac(spModel );
    virtual void Rysuj() override;
    virtual void RysujZnazwami() override;
    virtual void RysujZWidocznymiPunktami() override;
    virtual void TransformacjePrzedRysowaniem() override;
    void WyliczSrodekCiezkosci();
    void SrodekModeluZmodeliWylicz();
    virtual void UtrwalPrzeksztalcenia() override;
	virtual void WlaczJednorazowoWymienneFunkcje(int jakieFunkcjeFlagi) override;
    int IleMamModeli();
    template<int flagi>
    void GrupaRysujTemplate();
private:
	using listaModeli = std::list<spModel>;
	listaModeli mojeModele;
    float srodekCiezkosci[3];//od wprowadzenia przesuwanego środka modelu przestał być używany
};
using spGrupaModeli = std::shared_ptr<GrupaModeli>;
#endif // GRUPAMODELI_H
