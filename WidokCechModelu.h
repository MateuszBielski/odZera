#ifndef WIDOKCECHMODELU_H
#define WIDOKCECHMODELU_H
#include "Czworoscian.h"

class WidokCechModelu : public Model{
public:
    WidokCechModelu();
    virtual ~WidokCechModelu(){};
    void RysujDla(std::shared_ptr<Model>);
    virtual void TransformacjePrzedRysowaniem() override;
    virtual void RysujGeometrie() override;
private:
    Czworoscian znacznik;
    spModel wskazywany = nullptr;
    float * zastepczaM_Pos;
    float * zastepczaSrodek;
};
using spWidokCech = std::shared_ptr<WidokCechModelu>;
#endif // WIDOKCECHMODELU_H
