#ifndef OKNOPROBA2_H
#define OKNOPROBA2_H
#include <Okno1.h>
#include <OknoGL.h>
class OknoProba2 : public Okno1
{
public:
	OknoProba2();
	~OknoProba2();
    virtual void Wypisz_AxB_nadPrzyciskami(int,int) override;
protected:
	virtual bool on_configure_event(GdkEventConfigure* event);
	virtual void NowyWatek();
    virtual int PodlaczenieSygnalow();
    virtual void ustawElementyOkna();
	virtual void UstawieniaKlasyDziedziczacej();
private:
    void NaPrzyciskZmienRozmiar();
    void PokazLiczenie();
	void WypelnijBufor();
    
    TextView tekst;
    Button b_ZmienRozmiar;
	Button b_UstawTekst;
    Button b_UruchomWatek;
//    Button b_NoweOknoGL;
	P_BuforTekstu buforTekstu;
    short licznik = 0;
    std::thread* watek;
//    std::unique_ptr<OknoGL> oknoGL;
	
	

};

#endif // OKNOPROBY_H
