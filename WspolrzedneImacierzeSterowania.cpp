#include "WspolrzedneImacierzeSterowania.h"
#define DIG_2_RAD (G_PI / 180.0)
#define RAD_2_DIG (180.0 / G_PI)

WspolrzedneImacierzeSterowania::WspolrzedneImacierzeSterowania()
{
	UstawWartosciStartowe();
}
void WspolrzedneImacierzeSterowania::UstawWartosciStartowe()
{
	for(int i = 0; i < 3 ; i++){
        m_Pos[i] = 0.0;
        przesunieciePierwotne[i] = 0.0;
        biezacaPozycjaKursoraMyszy3D[i] = 0.0;
        poprzedniaPozycjaKursoraMyszy3D[i] = 0.0;
    }

	float sine = sin(0.5 * 0.0 * DIG_2_RAD);
    m_Quat[0] = sine;
    m_Quat[1] = 0;
    m_Quat[2] = 0;
    m_Quat[3] = cos(0.5 * 0.0 * DIG_2_RAD);
	m_QuatDiff[0] = 0.0;
    m_QuatDiff[1] = 0.0;
    m_QuatDiff[2] = 0.0;
    m_QuatDiff[3] = 1.0;
	MacierzObrotuUstawJednostkowo();
}
void WspolrzedneImacierzeSterowania::MacierzObrotuUstawJednostkowo(){
    for(int i = 0; i < 4 ; i++)for(int j = 0; j < 4 ; j++)macierzObrotu[i][j] = 0.0;
	macierzObrotu[0][0] = 1.0;
	macierzObrotu[1][1] = 1.0;
	macierzObrotu[2][2] = 1.0;
	macierzObrotu[3][3] = 1.0;
}
void WspolrzedneImacierzeSterowania::SkopiujWartosciZ(std::shared_ptr<WspolrzedneImacierzeSterowania> spW )
{
	for(int i = 0; i < 3 ; i++){
        m_Pos[i] = spW->m_Pos[i];
        przesunieciePierwotne[i] = spW->przesunieciePierwotne[i];
        biezacaPozycjaKursoraMyszy3D[i] = spW->biezacaPozycjaKursoraMyszy3D[i];
        poprzedniaPozycjaKursoraMyszy3D[i] = spW->poprzedniaPozycjaKursoraMyszy3D[i];
    }
    for(int i = 0; i < 4 ; i++){
        m_Quat[i] = spW->m_Quat[i];
        m_QuatDiff[i] = spW->m_QuatDiff[i];
    }
    for(int i = 0; i < 4 ; i++)for(int j = 0; j < 4 ; j++)macierzObrotu[i][j] = spW->macierzObrotu[i][j];
}
WspolrzedneImacierzeSterowania::~WspolrzedneImacierzeSterowania()
{
    g_print("\ndestruktor WspolrzedneImacierzeSterowania");
}
void WspolrzedneImacierzeSterowania::ZmienM_Pos_zgodnieZruchemKursora3D()
{
//	g_print("\nZmienM_Pos %2.3f %2.3f %2.3f ",m_Pos[0],m_Pos[1],m_Pos[2]);
    for(int i = 0 ; i < 3 ; i++)m_Pos[i] += biezacaPozycjaKursoraMyszy3D[i] - poprzedniaPozycjaKursoraMyszy3D[i];
}

void WspolrzedneImacierzeSterowania::BiezaceUstawJakoPoprzednie_m_Begin()
{
    
}

void WspolrzedneImacierzeSterowania::BiezaceUstawJakoPoprzednie_PozycjaKursoraMyszy3D()
{
    for(int i = 0 ; i < 3 ; i++)poprzedniaPozycjaKursoraMyszy3D[i] = biezacaPozycjaKursoraMyszy3D[i];
}


