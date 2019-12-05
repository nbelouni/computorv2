//
// Created by Hugo JEANNIN on 12/2/19.
//

#include "../inc/Computor.hpp"

Computor::Computor()
{
    std::cerr << "Computor constructed." << std::endl;
}

Computor::~Computor()
{
    std::cerr << "Computor destroyed." << std::endl;
}

void Computor::test()
{
//    Complex comp;
    Real a;
    std::cout << "a = " << a << std::endl;
    Real b(2.4, 4);
    std::cout << "b = " << b << std::endl;
    Real c(1.345);
    std::cout << "c = " << c << std::endl;
    Real d(b);
    std::cout << "d = " << d << std::endl;
    a.setPower(2);
    a.setValue(321);
    std::cout << "a = " << a << std::endl;
//    a = b;
//    a + a;
    a = d + b;
    std::cout << "a = " << a << std::endl;
    a = c;
    std::cout << "a = " << a << std::endl;

}
