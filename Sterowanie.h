#ifndef STEROWANIE_H
#define STEROWANIE_H

class Sterowanie
{
public:
	Sterowanie();
	~Sterowanie();
	virtual int PodlaczanieSygnalow(Widget& okno) = 0;
protected:
	 void UstawOkno(Widget* o);
	 Widget* oknoSterowane;
	 
};

#endif // STEROWANIE_H
