#include "GrupaModeli.h"

GrupaModeli::GrupaModeli()
{
}

GrupaModeli::~GrupaModeli()
{
}
void GrupaModeli::DodajDoMnie(Model&& model)
{
	mojeModele.push_back(std::move(model));
}
