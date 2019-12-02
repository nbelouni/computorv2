//
// Created by Hugo JEANNIN on 12/2/19.
//

#ifndef COMPUTERV2_IOPERAND_HPP
#define COMPUTERV2_IOPERAND_HPP

class Real;
class Complex;
class Matrix;
class Function;

template <typename T>
class IOperand
{
    virtual T addReal(Real r) = 0;
    virtual T addComplex(Complex c) = 0;
    virtual T addMatrix(Matrix m) = 0;
    virtual T addFunction(Function f) = 0;

    virtual T subReal(Real r) = 0;
    virtual T subComplex(Complex c) = 0;
    virtual T subMatrix(Matrix m) = 0;
    virtual T subFunction(Function f) = 0;

    virtual T mulReal(Real r) = 0;
    virtual T mulComplex(Complex c) = 0;
    virtual T mulMatrix(Matrix m) = 0;
    virtual T mulFunction(Function f) = 0;

    virtual T divReal(Real r) = 0;
    virtual T divComplex(Complex c) = 0;
    virtual T divMatrix(Matrix m) = 0;
    virtual T divFunction(Function f) = 0;

    virtual T modReal(Real r) = 0;
    virtual T modComplex(Complex c) = 0;
    virtual T modMatrix(Matrix m) = 0;
    virtual T modFunction(Function f) = 0;

    IOperand();
    virtual ~IOperand();
};

#endif //COMPUTERV2_IOPERAND_HPP
