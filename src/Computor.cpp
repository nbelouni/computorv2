//
// Created by Hugo JEANNIN on 12/2/19.
//

#include "../inc/Computor.hpp"
#include "../inc/Rational.hpp"
#include "../inc/Complex.hpp"
#include "../inc/Matrix.hpp"

Computor::Computor(){}

Computor::~Computor(){}

void Computor::testComplex()
{
    Operand *tmp;
    Complex *cp;
    Complex res;

    Rational r_a(42);

    Complex c_a;
    Complex c_b(0.23);
    Complex c_c(32, 0.23);
    Complex c_d(c_c);
    Complex c_e(23, 0.012);

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

    Complex asd(42, -23);
    Complex qwe(42, 23);

    tmp = asd + qwe;
    std::cout << "asd - qwe = " << asd << " - " << qwe << " = " << *tmp << std::endl;
    std::cout << std::endl;

    res = c_e * c_c;
    std::cout << "c_e * c_c = " << c_e << " * " << c_c << " = " << res << std::endl;
    std::cout << std::endl;

    res = c_e * r_a;
    std::cout << "c_e * r_a = " << c_e << " * " << r_a << " = " << res << std::endl;
    std::cout << std::endl;
/*
    Complex ab(-2, 5);
    Complex cd(1, -3);

    res = ab * cd;
    std::cout << "ab * cd = " << ab << " * " << cd << " = " << res << std::endl;
    std::cout << std::endl;

*/
    Complex ab(3, 2);
    Complex cd(4, -3);

    res = ab / cd;
    std::cout << "ab / cd = " << ab << " / " << cd << " = " << res << std::endl;
    std::cout << std::endl;

    Complex wief(4, 0);
    Complex gior(1, -3);

    res = wief / gior;
    std::cout << "wief / gior = " << wief << " / " << gior << " = " << res << std::endl;
    std::cout << std::endl;

    Complex wbeicw(1, -3);
    Rational woehfy(4);

    res = wbeicw / woehfy;
    std::cout << "wbeicw / woehfy = " << wbeicw << " / " << woehfy << " = " << res << std::endl;
    std::cout << std::endl;
}


void Computor::testRational()
{
    Operand *res;

    Operand pouet;
    std::cout << "pouet " << pouet << std::endl;

    Rational r_a;
    Rational r_b(3.123);
    Rational r_c(5);
    Rational r_d(r_b);
    Rational r_e(3);
    Rational r_f(0.0);

    std::cout << "r_a " << r_a << std::endl;
    r_a.setValue(42.42);
    std::cout << "r_a " << r_a << std::endl;
    std::cout << "r_b " << r_b << std::endl;
    std::cout << "r_c " << r_c << std::endl;
    std::cout << "r_d " << r_d << std::endl;
    std::cout << std::endl;

    res = r_a + r_b;

    res = r_a + r_b;
    std::cout << "r_a + r_b = " << r_a << " + " << r_b << " = " << *res << std::endl;
    std::cout << std::endl;

    res = r_c + r_c;
    std::cout << "r_c + r_c = " << r_c << " + " << r_c << " = " << *res << std::endl;
    std::cout << std::endl;

    res = r_d + r_b;
    std::cout << "r_d + r_b = " << r_d << " + " << r_b << " = " << *res << std::endl;
    std::cout << std::endl;

    res = r_a - r_c;
    std::cout << "r_a - r_c = " << r_a << " - " << r_c << " = " << *res << std::endl;
    std::cout << std::endl;

    res = r_a * r_c;
    std::cout << "r_a * r_c = " << r_a << " * " << r_c << " = " << *res << std::endl;
    std::cout << std::endl;

    res = r_a / r_c;
    std::cout << "r_a / r_c = " << r_a << " / " << r_c << " = " << *res << std::endl;
    std::cout << std::endl;

    res = r_c % r_e;
    std::cout << "r_c / r_e = " << r_c << " % " << r_e << " = " << *res << std::endl;
    std::cout << std::endl;

    Rational ab(4);
    Complex cd(2, -4);

    res = ab / cd;
    std::cout << "ab / cd = " << ab << " / " << cd << " = " << *res << std::endl;
    std::cout << std::endl;

//    res = ab % cd;
//    std::cout << "ab % cd = " << ab << " % " << cd << " = " << *res << std::endl;
//    std::cout << std::endl;

    res = r_a % r_f;
    std::cout << "r_a / r_f = " << r_a << " / " << r_f << " = " << *res << std::endl;
    std::cout << std::endl;

    res = r_a / r_f;
    std::cout << "r_a / r_f = " << r_a << " / " << r_f << " = " << *res << std::endl;
    std::cout << std::endl;

}

void Computor::testMatrix()
{
    Operand *tmp;

/*
    std::vector<double> pouet = {1, 2, 3, 4, 5, 6};
    Matrix yo(pouet, 2, 3);
    std::cout << yo << std::endl;

    Matrix tak({1, 2, 3, 4, 5, 6}, 2, 3);
    std::cout << tak << std::endl;

    Matrix eafwj({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);
    std::cout << eafwj << std::endl;

    tak = eafwj;
    std::cout << tak << std::endl;

    Matrix aadd({1, 2, 3, 4}, 2, 2);
    Matrix badd({10, 20, 30, 40}, 2, 2);

    tmp = aadd + badd;
    std::cout << aadd << std::endl;
    std::cout << badd << std::endl;
    std::cout << *tmp << std::endl;

    aadd = Matrix({7, 4, 3, 1}, 2, 2);
    std::cout << aadd << std::endl;
    std::cout << badd << std::endl;
    std::cout << *tmp << std::endl;

    Matrix waef({12, 32}, 1, 3);
*/
    Rational ra(2);
    Matrix mat({1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3);
/*

    tmp = mat + ra;
    std::cout << *tmp << std::endl;
//    tmp = ra + mat;
//    std::cout << *tmp << std::endl;
*/

/*
    tmp = mat - ra;
    std::cout << *tmp << std::endl;
//    tmp = ra - mat;
//    std::cout << *tmp << std::endl;
*/

/*
    tmp = mat * mat;
    std::cout << *tmp << std::endl;
    tmp = mat * ra;
    std::cout << *tmp << std::endl;
//    tmp = ra * mat;
//    std::cout << *tmp << std::endl;
*/

/*
    tmp = mat / mat;
    std::cout << *tmp << std::endl;
    tmp = mat / ra;
    std::cout << *tmp << std::endl;
//    tmp = ra / mat;
//    std::cout << *tmp << std::endl;
*/

/*
    tmp = mat % mat;
    std::cout << *tmp << std::endl;
    tmp = mat % ra;
    std::cout << *tmp << std::endl;
//    tmp = ra % mat;
  //  std::cout << *tmp << std::endl;
*/

/*
    Matrix mata({11, 12, 21, 22, 31, 32, 41, 42}, 4, 2);
    Matrix matb({11, 12, 13, 21, 22, 23}, 2, 3);

    std::cout << mata << std::endl;
    std::cout << matb << std::endl;
    // Bon c'est degeux mais je vais voir plus tard.
    tmp = mata.dot(mata, matb);
    std::cout << *tmp << std::endl;
*/

    Matrix mata({11, 12, 13}, 1, 3);
    Matrix matb({11, 21, 31}, 3, 1);

    std::cout << mata << std::endl;
    std::cout << matb << std::endl;
    // Bon c'est degeux mais je vais voir plus tard.
    tmp = mata.dot(mata, matb);
    std::cout << *tmp << std::endl;

/*
    Matrix mata({11, 12, 13, 21, 22, 23, 31, 32, 33}, 3, 3);
    Matrix matb({110, 120, 130, 210, 220, 230, 310, 320, 330}, 3, 3);

    std::cout << mata << std::endl;
    std::cout << matb << std::endl;
    // Bon c'est degeux mais je vais voir plus tard.
    tmp = mata.dot(mata, matb);
    std::cout << *tmp << std::endl;
*/
/*

    std::vector<double> pouet;

//    pouet = mata.getColumn(2);
//    for (int i = 0; i < pouet.size(); i++)
//    {
//        std::cout << " " << pouet[i];
//    }
//    std::cout << std::endl;

    pouet = mata.getColumn(0);
    std::cout << "col 0: ";
    for (int i = 0; i < pouet.size(); i++)
    {
        std::cout << " " << pouet[i];
    }
    std::cout << std::endl;

    pouet = mata.getColumn(1);
    std::cout << "col 1: ";
    for (int i = 0; i < pouet.size(); i++)
    {
        std::cout << " " << pouet[i];
    }
    std::cout << std::endl;

    pouet = mata.getRow(0);
    std::cout << "row 0: ";
    for (int i = 0; i < pouet.size(); i++)
    {
        std::cout << " " << pouet[i];
    }
    std::cout << std::endl;

    pouet = mata.getRow(1);
    std::cout << "row 1: ";
    for (int i = 0; i < pouet.size(); i++)
    {
        std::cout << " " << pouet[i];
    }
    std::cout << std::endl;

//    pouet = mata.getRow(-1);
//    for (int i = 0; i < pouet.size(); i++)
//    {
//        std::cout << " " << pouet[i];
//    }
//    std::cout << std::endl;
*/

}
