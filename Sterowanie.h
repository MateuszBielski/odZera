#ifndef STEROWANIE_H
#define STEROWANIE_H
#include <gtkmm/widget.h>
#include <Komunikat.h>
#include <Modul.h>
#include <EkranGL.h> 

class Sterowanie : public Modul
{
public:
	Sterowanie();
	~Sterowanie();
	virtual int PodlaczanieSygnalow(Gtk::Widget& okno) = 0;
    virtual int PolaczZkimPotrzebujeNaPoczatek();
	virtual void PodlaczSygnalPrzeksztalcenieWidoku(EkranGL& ) = 0;
	virtual void PrzeksztalcenieWidoku( bool b, int i) = 0;
    virtual void KopiujZinnegoModulu(spModul) override;
protected:
	void UstawOkno(Gtk::Widget* o);
	Gtk::Widget* oknoSterowane;
    void KopiujParametrySterowania(Sterowanie& );
    float m_BeginX;
    float m_BeginY;
    float m_DX;
    float m_DY;
    float m_Pos[3];
    float macierzObrotu[4][4];
	 
};

#endif // STEROWANIE_H
