#ifndef OKNOPROBY_H
#define OKNOPROBY_H
#include <Okno1.h>
#include <OknoGL.h>
class OknoProby : public Okno1
{
public:
	OknoProby();
	~OknoProby();
protected:
	virtual bool on_configure_event(GdkEventConfigure* event);
	virtual void NowyWatek();
    virtual int PodlaczenieSygnalow();
    virtual void ustawElementyOkna();
	virtual void UstawieniaKlasyDziedziczacej();
private:
    void NaPrzyciskZmienRozmiar();
    void NoweOknoGL();
    void PokazLiczenie();
	void WypiszRozmiarOkna(int,int);
	void WypelnijBufor();
	
	TextView tekst;
    Button b_ZmienRozmiar;
	Button b_UstawTekst;
    Button b_UruchomWatek;
    Button b_NoweOknoGL;
	P_BuforTekstu buforTekstu;
    short licznik = 0;
    std::thread* watek;
    std::unique_ptr<OknoGL> oknoGL;

};

#endif // OKNOPROBY_H
