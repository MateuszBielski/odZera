#ifndef MODELPUSTY_H
#define MODELPUSTY_H
#include <Model.h>

class ModelPusty : public Model{
public:
    ModelPusty(itLspModel dokadWstawiono):tuJestemPelny(dokadWstawiono){};
    ModelPusty(){};
    virtual ~ModelPusty();
    itLspModel AdresPelnegoObiektu();
private:
     itLspModel tuJestemPelny;
};

#endif // MODELPUSTY_H
