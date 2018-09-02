#include "WspolrzedneImacierzeSterowania.h"
#define DIG_2_RAD (G_PI / 180.0)
#define RAD_2_DIG (180.0 / G_PI)

WspolrzedneImacierzeSterowania::WspolrzedneImacierzeSterowania()
{
	m_Pos[0] = 0.0;
    m_Pos[1] = 0.0;
    m_Pos[2] = 0.0;

	float sine = sin(0.5 * 0.0 * DIG_2_RAD);
    m_Quat[0] = sine;
    m_Quat[1] = 0;
    m_Quat[2] = 0;
    m_Quat[3] = cos(0.5 * 0.0 * DIG_2_RAD);
	m_QuatDiff[0] = 0.0;
    m_QuatDiff[1] = 0.0;
    m_QuatDiff[2] = 0.0;
    m_QuatDiff[3] = 1.0;
	for(int i = 0; i < 4 ; i++)for(int j = 0; j < 4 ; j++)macierzObrotu[i][j] = 0.0;
	macierzObrotu[0][0] = 1.0;
	macierzObrotu[1][1] = 1.0;
	macierzObrotu[2][2] = 1.0;
	macierzObrotu[3][3] = 1.0;
}

WspolrzedneImacierzeSterowania::~WspolrzedneImacierzeSterowania()
{
}

