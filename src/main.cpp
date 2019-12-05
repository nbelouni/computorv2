
#include "../inc/Computorv2.hpp"

int main(int argc, char *argv[])
{
    Computor cp;

    try
    {
        cp.testComplex();
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << "INVALID ARGUMENT: " << e.what() << std::endl;
    }
    catch (const std::logic_error &e)
    {
        std::cerr << "LOGIC ERROR: " << e.what() << std::endl;
    }
    return 0;
}
