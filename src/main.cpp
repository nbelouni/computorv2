
#include "../inc/Computorv2.hpp"

int main(int argc, char *argv[])
{
    Computor cp;

    try
    {
        cp.test();
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << &e << std::endl;
    }
    return 0;
}
