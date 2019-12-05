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

void Computor::testComplex()
{
    Real r_a(42, 2);
    Complex c_a;
    Complex c_b(0.23);
    Complex c_c(32, 0.23);
    Complex c_d(c_c);
    Complex c_e(23, 0.0);
    std::cout << "c_a= " << c_a << std::endl;
    std::cout << "c_b= " << c_b << std::endl;
    std::cout << "c_c= " << c_c << std::endl;
    std::cout << "c_d= " << c_d << std::endl;
    std::cout << "c_e= " << c_e << std::endl;
//    c_a = r_a;
    c_a = c_c;
    c_a = c_b + r_a;
    std::cout << "c_a= " << c_a << std::endl;
    r_a = c_e;
    std::cout << "r_a= " << r_a << std::endl;
    r_a = c_c;
    std::cout << "r_a= " << r_a << std::endl;
}


void Computor::testReal()
{
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
//    a = comp;
    a = b;
//    a + a;
    a = d + b;
//    a = d + comp;
    std::cout << "a = " << a << std::endl;
    a = c;
    std::cout << "a = " << a << std::endl;
}
