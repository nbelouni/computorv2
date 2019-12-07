//
// Created by Hugo JEANNIN on 12/2/19.
//

#include "../inc/Computor.hpp"

Computor::Computor(){}

Computor::~Computor(){}

void Computor::testComplex()
{
    Real r_a(42);
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
//    Real *ptr_a;
//    Real *ptr_b;

    Complex c_a;
    Real r_a;
    Real r_b(4.0);
    Real r_c(1.345);
    Real r_d(r_b);

//    ptr_a = &r_a;
//    ptr_b = &r_b;
    std::cout << "r_a = " << r_a << std::endl;
    std::cout << "r_b = " << r_b << std::endl;
    std::cout << "r_c = " << r_c << std::endl;
    std::cout << "r_d = " << r_d << std::endl;
    r_a.setValue(321);
    std::cout << "r_a = " << r_a << std::endl;

    // THIS !=
    r_a = r_b;
    std::cout << "*r_a = " << &r_a << std::endl;
    std::cout << "*r_b = " << &r_b << std::endl;
    std::cout << "r_a = " << r_a << std::endl;
    std::cout << "*r_a, *r_d, *r_b" << &r_a << ", " << &r_d << ", " << &r_b << std::endl;
    r_a = r_d - r_b;
    std::cout << "*r_a, *r_d, *r_b" << &r_a << ", " << &r_d << ", " << &r_b << std::endl;
    std::cout << "r_a = r_d - r_b : " << r_a << std::endl;
    r_a = r_d + r_b;
    std::cout << "r_a = r_d + r_b : " << r_a << std::endl;

    // THAT
    r_a = r_b;
    std::cout << "*r_a = " << &r_a << std::endl;
    std::cout << "*r_b = " << &r_b << std::endl;
    std::cout << "r_a = " << r_a << std::endl;
    std::cout << "*r_a, *r_d, *r_b" << &r_a << ", " << &r_d << ", " << &r_b << std::endl;
    r_a = r_d + r_b;
    std::cout << "*r_a, *r_d, *r_b" << &r_a << ", " << &r_d << ", " << &r_b << std::endl;
    std::cout << "r_a = r_d + r_b : " << r_a << std::endl;
    r_a = r_d - r_b;
    std::cout << "r_a = r_d - r_b : " << r_a << std::endl;

    r_a = r_c;
    std::cout << "r_a = " << r_a << std::endl;
    ///////////////////////////////////////
    /// NE PAS REUTILISER LES VARIABLES ///
    ///////////////////////////////////////

    Operand *op = new Operand();
    Real real_a(13);
    Real real_b(26);
    Real real_c(34);
    Real real_e(7);
    Real *real_d = new Real();
    Complex cp_a(2, 0);
    Complex cp_b(3, 4);
    Complex *cp_c = new Complex();

    std::cout << "real_a" << real_a << std::endl;
    std::cout << "real_b" << real_b << std::endl;
    std::cout << "real_c" << real_c << std::endl;
    std::cout << "real_d" << *real_d << std::endl;
    std::cout << "real_e" << real_e << std::endl;
    std::cout << "op" << *op << std::endl;

    real_d = dynamic_cast<Real *>(real_b + real_c);
    op = real_a + real_b;

    std::cout << "real_d" << *real_d << std::endl;
    std::cout << "op" << *op << std::endl;

    real_d = static_cast<Real *>(op);

    std::cout << "real_d" << *real_d << std::endl;
    std::cout << "op" << *op << std::endl;

    op = real_b + cp_a;
    real_d = static_cast<Real *>(op);

    std::cout << "op" << *op << std::endl;
    std::cout << "real_d" << *real_d << std::endl;

    op = real_c + cp_b;
    cp_c = static_cast<Complex *>(op);

    std::cout << "op" << *op << std::endl;
    std::cout << "cp_c" << *cp_c << std::endl;
/*
    real_d = static_cast<Real *>(real_b * real_e);
    std::cout << "real_d" << *real_d << std::endl;
*/

    real_d = static_cast<Real *>(real_c % real_e);
    std::cout << "real_d" << *real_d << std::endl;
/*

    real_d = static_cast<Real *>(real_b * real_b);
    std::cout << "real_d" << *real_d << std::endl;

    real_d = static_cast<Real *>(real_a * real_c);
    std::cout << "real_d" << *real_d << std::endl;
    real_d->reset();
*/

/*
    op = real_b * cp_a;
    real_d = static_cast<Real *>(op);
    real_d->reset();

    std::cout << "op" << *op << std::endl;
    std::cout << "real_d" << *real_d << std::endl;

    op = real_c * cp_b;
    cp_c = static_cast<Complex *>(op);

    std::cout << "op" << *op << std::endl;
    std::cout << "cp_c" << *cp_c << std::endl;
*/
/*
    real_d = static_cast<Real *>(real_b + real_b);
    std::cout << "real_d" << *real_d << std::endl;

    op = real_b - cp_a;
    real_d = static_cast<Real *>(op);

    std::cout << "op" << *op << std::endl;
    std::cout << "real_d" << *real_d << std::endl;

    op = real_c - cp_b;
    cp_c = static_cast<Complex *>(op);

    std::cout << "op" << *op << std::endl;
    std::cout << "cp_c" << *cp_c << std::endl;
*/
}

void Computor::testModulo()
{
//    double lhs = 0.999999999999999;
    double lhs = 3.00;
//    double lhs = 3.2;
    double rhs = 5.0;


    double trux;
    int yo = 12;

    trux = static_cast<double>(yo);

/*
    if (floor(lhs) == lhs)
    {
        std::cout << lhs << "CAN BE INTEGER" <<std::endl;
    }
    else
    {
        std::cout << lhs << "NIQUE TOI" <<std::endl;
    }
    std::cout << floor(lhs) << std::endl;

    int yo = static_cast<int>(lhs);
    std::cout << yo << std::endl;

    int pouet = (int) std::round(lhs);
    std::cout << pouet << std::endl;

    int wefawe = static_cast<int>(std::round(lhs));
    std::cout << wefawe << std::endl;

*/
//    int ndty = const_cast<int>(std::round(3.0));
//    std::cout << ndty << std::endl;
//
//    int iojs = (int) std::round(3.0);
//    std::cout << iojs << std::endl;

}


