#ifndef LINIEZNORMALNYCH_H
#define LINIEZNORMALNYCH_H
#include <Model.h>

class LinieZnormalnych : public Model{
public:
    LinieZnormalnych(){};
    virtual ~LinieZnormalnych(){};
    void RysujDla(std::shared_ptr<Model>);
    virtual void RysujGeometrie() override;
private:
    float * normalneModelu;
    
};
using spLinieN = std::shared_ptr<LinieZnormalnych>;
#endif // LINIEZNORMALNYCH_H
