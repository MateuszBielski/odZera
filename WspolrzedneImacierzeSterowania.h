#ifndef WSPOLRZEDNEIMACIERZESTEROWANIA_H
#define WSPOLRZEDNEIMACIERZESTEROWANIA_H
#include <gtkmm.h>
class WspolrzedneImacierzeSterowania
{
public:
	WspolrzedneImacierzeSterowania();
	~WspolrzedneImacierzeSterowania();
    void ZmienM_Pos_zgodnieZruchemKursora3D();
    void BiezaceUstawJakoPoprzednie_m_Begin();
    void BiezaceUstawJakoPoprzednie_PozycjaKursoraMyszy3D();
	float m_QuatDiff[4];
    float m_Quat[4];
	
	float m_BeginX;
    float m_BeginY;
    float m_DX;
    float m_DY;
    float m_Pos[3];
    float macierzObrotu[4][4];
    float biezacaPozycjaKursoraMyszy3D[3];
    float poprzedniaPozycjaKursoraMyszy3D[3];
    
};

#endif // WSPOLRZEDNEIMACIERZESTEROWANIA_H