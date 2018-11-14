#ifndef STARERYSOWANIE_H
#define STARERYSOWANIE_H
#include <Model.h>

class Ostroslup : public Model{
  public:
    Ostroslup(){};
    virtual ~Ostroslup(){};
	virtual void RysujGeometrie()  override;
};


class TrzyKwadraty : public Model{
  public:
    TrzyKwadraty(){};
    ~TrzyKwadraty(){};
    virtual void RysujGeometrie() override;
};

#endif // STARERYSOWANIE_H
