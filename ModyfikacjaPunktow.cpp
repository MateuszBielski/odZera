#include "ModyfikacjaPunktow.h"
#include <algorithm>//UsunPunkt
#include <string.h>

PunktModyfikowany::PunktModyfikowany():adresZrodla(nullptr)
{
}
PunktModyfikowany::PunktModyfikowany(float* a):adresZrodla(a)
{
    PobierzIstniejaceWartosci();
    for(int i = 0 ; i < 3 ; i++){
        wartosciChwilowe[i] = 0.0f;
        wartosciObliczone[i] = 0.0f;
    }
}

PunktModyfikowany::~PunktModyfikowany()
{
    //UstawNoweWartosci();?
}

void PunktModyfikowany::PobierzIstniejaceWartosci()
{
    memcpy(wartosciDotychczasowe,adresZrodla,3*sizeof(float));
}

void PunktModyfikowany::UstawNoweWartosci()
{
    memcpy(adresZrodla,wartosciObliczone,3*sizeof(float));
}

bool PunktModyfikowany::operator ==(const PunktModyfikowany& rhs)
{
    return adresZrodla == rhs.adresZrodla;
}
/*bool PunktModyfikowany::operator !=(const PunktModyfikowany& p1, const PunktModyfikowany& p2)
{
}*/
void PunktModyfikowany::UwzglednijZmiane(float * d)
{
    for(int i = 0 ; i < 3 ; i++){
        wartosciObliczone[i] = wartosciDotychczasowe[i] + d[i];
        wartosciDotychczasowe[i] = wartosciObliczone[i];
    }
    UstawNoweWartosci();
}
ModyfikacjaPunktow::ModyfikacjaPunktow()
{
}

ModyfikacjaPunktow::~ModyfikacjaPunktow()
{
}

void ModyfikacjaPunktow::WyczyscIwstawJedenPunkt(float* adr)
{
    if(!mojePunkty.empty())mojePunkty.clear();
    DodajPunkt(adr);
}

void ModyfikacjaPunktow::DodajPunkt(float* adr)
{
    mojePunkty.push_back(PunktModyfikowany(adr));
    //coś zrobić z m_Pos - np skopiować z dodawanego punktu
}

void ModyfikacjaPunktow::UsunPunkt(float* adr)
{
    //poniższe z książki czysty kod c++17 str 181
    mojePunkty.erase(
    std::remove(std::begin(mojePunkty),std::end(mojePunkty),PunktModyfikowany(adr))
    ,std::end(mojePunkty));
}

it_zbiorPktMod ModyfikacjaPunktow::WyszukajWsrodPunktowWgAdresu(float*)
{
    
}
void ModyfikacjaPunktow::ZmienM_Pos_zgodnieZruchemKursora3D()
{
    float zmiana[3];
    for(int i = 0 ; i < 3 ; i++)
    {
        zmiana[i] = biezacaPozycjaKursoraMyszy3D[i] - poprzedniaPozycjaKursoraMyszy3D[i];
        m_Pos[i] += zmiana[i];
    }
    int ilePunktow = 0;
    for(auto& punkt : mojePunkty){
        punkt.UwzglednijZmiane(zmiana);
        ++ilePunktow;
    }
//    g_print("\nuwzględniono zmianę %d punktów, lista zawiera %d punktów",ilePunktow,mojePunkty.size());
}
