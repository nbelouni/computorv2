//
// Created by Hugo JEANNIN on 12/2/19.
//

#include "../inc/Computor.hpp"

Computor::Computor(){}

Computor::~Computor(){}

void Computor::testComplex()
{
    Operand *tmp;
    Complex *cp;
    Complex res;

    Real r_a(42);

    Complex c_a;
    Complex c_b(0.23);
    Complex c_c(32, 0.23);
    Complex c_d(c_c);
    Complex c_e(23, 0.012);
/*

    std::cout << "c_a " << c_a << std::endl;
    std::cout << "c_b " << c_b << std::endl;
    std::cout << "c_c " << c_c << std::endl;
    std::cout << "c_d " << c_d << std::endl;
    std::cout << "c_e " << c_e << std::endl;
    std::cout << std::endl;

    tmp = c_e + c_c;
    std::cout << "c_e + c_c = " << c_e << " + " << c_c << " = " << *tmp << std::endl;
    cp = dynamic_cast<Complex *>(tmp);
    std::cout << std::endl;
    std::cout << *cp << std::endl;
    std::cout << std::endl;

    res = c_e + c_c;
    std::cout << "c_e + c_c = " << c_e << " + " << c_c << " = " << res << std::endl;
    std::cout << std::endl;

    res = c_e - c_c;
    std::cout << "c_e - c_c = " << c_e << " - " << c_c << " = " << res << std::endl;
    std::cout << std::endl;
*/

/*
    res = c_e * c_c;
    std::cout << "c_e * c_c = " << c_e << " * " << c_c << " = " << res << std::endl;
    std::cout << std::endl;
*/

/*
    res = c_e * r_a;
    std::cout << "c_e * r_a = " << c_e << " * " << r_a << " = " << res << std::endl;
    std::cout << std::endl;
*/
/*
    Complex ab(-2, 5);
    Complex cd(1, -3);

    res = ab * cd;
    std::cout << "ab * cd = " << ab << " * " << cd << " = " << res << std::endl;
    std::cout << std::endl;

*/
/*
    Complex ab(3, 2);
    Complex cd(4, -3);

    res = ab / cd;
    std::cout << "ab / cd = " << ab << " / " << cd << " = " << res << std::endl;
    std::cout << std::endl;
*/

/*
    Complex ab(4, 0);
    Complex cd(1, -3);

    res = ab / cd;
    std::cout << "ab / cd = " << ab << " / " << cd << " = " << res << std::endl;
    std::cout << std::endl;
*/
    Complex ab(1, -3);
    Real cd(4);

    res = ab / cd;
    std::cout << "ab / cd = " << ab << " / " << cd << " = " << res << std::endl;
    std::cout << std::endl;
}


void Computor::testReal()
{
    Real res;

    Real r_a;
    Real r_b(3.123);
    Real r_c(5);
    Real r_d(r_b);
    Real r_e(3);
    Real r_f(0.0);

    std::cout << "r_a " << r_a << std::endl;
    r_a.setValue(42.42);
    std::cout << "r_a " << r_a << std::endl;
    std::cout << "r_b " << r_b << std::endl;
    std::cout << "r_c " << r_c << std::endl;
    std::cout << "r_d " << r_d << std::endl;
    std::cout << std::endl;

    res = r_a + r_b;
    std::cout << "r_a + r_b = " << r_a << " + " << r_b << " = " << res << std::endl;
    std::cout << std::endl;

    res = r_c + r_c;
    std::cout << "r_c + r_c = " << r_c << " + " << r_c << " = " << res << std::endl;
    std::cout << std::endl;

    res = r_d + r_b;
    std::cout << "r_d + r_b = " << r_d << " + " << r_b << " = " << res << std::endl;
    std::cout << std::endl;

    res = r_a - r_c;
    std::cout << "r_a - r_c = " << r_a << " - " << r_c << " = " << res << std::endl;
    std::cout << std::endl;

    res = r_a * r_c;
    std::cout << "r_a * r_c = " << r_a << " * " << r_c << " = " << res << std::endl;
    std::cout << std::endl;

    res = r_a / r_c;
    std::cout << "r_a / r_c = " << r_a << " / " << r_c << " = " << res << std::endl;
    std::cout << std::endl;

    res = r_c % r_e;
    std::cout << "r_c / r_e = " << r_c << " % " << r_e << " = " << res << std::endl;
    std::cout << std::endl;

    Real ab(4);
    Complex cd(2, -4);
    Complex cres;

    cres = ab / cd;
    std::cout << "ab / cd = " << ab << " / " << cd << " = " << cres << std::endl;
    std::cout << std::endl;

    res = r_a / r_f;
    std::cout << "r_a / r_f = " << r_a << " / " << r_f << " = " << res << std::endl;
    std::cout << std::endl;

}
