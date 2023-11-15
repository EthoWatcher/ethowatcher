#ifndef RANDCUSTOM_H
#define RANDCUSTOM_H

#include <random>
class RandCustom
{
public:
    RandCustom(int seed);
    int generate();
private:
    int seed;
};

#endif // RANDCUSTOM_H
