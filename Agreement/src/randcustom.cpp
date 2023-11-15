#include "randcustom.h"

// TODO: avaliar se seed está funcionando
RandCustom::RandCustom(int seed)
{
    this->seed = seed;
    std::srand(this->seed);
}

int RandCustom::generate()
{
    int random_variable = std::rand();
    return  random_variable;
}
