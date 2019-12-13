#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Computorv2.hpp"
#include "Operand.hpp"

class Matrix: public Operand
{
	private:
	    std::vector<double>     values_;
		size_t                  rows_;
		size_t                  columns_;

	public:
		Matrix();
		Matrix(std::vector<double> values, size_t rows, size_t columns);
		Matrix(size_t rows, size_t columns);
		Matrix(Matrix &matrix);
		Matrix(const Matrix *matrix);
		~Matrix();

		Operand * operator=( Operand const & rhs ); // Equal
		Operand * operator+( Operand const & rhs ); // Sum
		Operand * operator-( Operand const & rhs ); // Difference
		Operand * operator*( Operand const & rhs ); // Product
		Operand * operator/( Operand const & rhs ); // Quotient
		Operand * operator%( Operand const & rhs ); // Modulo

        double 	computeDotLine(std::vector<double> a, std::vector<double> b) const;
        Operand *dot(Operand const &lhs, Operand const & rhs); // ** or dot product

//		void			setValues(std::vector<std::vector<double>> array);
		const std::vector<double>	getValues() const;
//		void			addValuesRow(std::vector<double> row);
//		void			assignValue(double value, size_t y, size_t x);

//		void			setColumns(size_t col);
		size_t			getColumnsCount() const;
//		void			setRows(size_t rows);
		size_t			getRowsCount() const;

		const std::vector<double>	getColumn(int col_index) const;
		const std::vector<double>	getRow(int row_index) const;

		Matrix			*solveAdd(const Matrix *a, const Matrix *b);
		Matrix			*solveAdd(const Matrix *a, double b);
		Matrix			*solveSub(const Matrix *a, const Matrix *b);
		Matrix			*solveSub(const Matrix *a, double b);
		Matrix			*solveMul(const Matrix *a, const Matrix *b);
		Matrix			*solveMul(const Matrix *a, double b);
		Matrix			*solveDiv(const Matrix *a, const Matrix *b);
		Matrix			*solveDiv(const Matrix *a, double b);
		Matrix			*solveMod(const Matrix *a, const Matrix *b);
		Matrix			*solveMod(const Matrix *a, double b);
		Matrix			*solveDot(const Matrix *a, const Matrix *b);

static std::ostream &print(std::ostream &o, Operand const &i);

};

std::ostream &operator<<(std::ostream &o, Matrix const &i);

#endif
