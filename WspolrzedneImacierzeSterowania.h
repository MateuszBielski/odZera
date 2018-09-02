#ifndef WSPOLRZEDNEIMACIERZESTEROWANIA_H
#define WSPOLRZEDNEIMACIERZESTEROWANIA_H

class WspolrzedneImacierzeSterowania
{
public:
	WspolrzedneImacierzeSterowania();
	~WspolrzedneImacierzeSterowania();

	float m_BeginX;
    float m_BeginY;
    float m_DX;
    float m_DY;
    float m_Pos[3];
    float macierzObrotu[4][4];
};

#endif // WSPOLRZEDNEIMACIERZESTEROWANIA_H
