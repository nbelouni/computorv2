#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Computorv2.hpp"
#include <utility>

class Matrix: public Operand
{
	private:
	    std::vector<double>     values_;
		size_t                  columns_;
		size_t                  rows_;

	public:
		Matrix();
		Matrix(std::vector<double> values, size_t columns, size_t rows);
		Matrix(Matrix &matrix);
		~Matrix();

//		Operand const * operator=( Operand const & rhs ); // Sum
//		Operand const * operator+( Operand const & rhs ); // Sum
//		Operand const * operator-( Operand const & rhs ); // Difference
//		Operand const * operator*( Operand const & rhs ); // Product
//		Operand const * operator/( Operand const & rhs ); // Quotient
//		Operand const * operator%( Operand const & rhs ); // Modulo

//		void			setValues(std::vector<std::vector<double>> array);
		const std::vector<double>	getValues() const;
//		void			addValuesRow(std::vector<double> row);
//		void			assignValue(double value, size_t y, size_t x);

//		void			setColumns(size_t col);
		size_t			getColumns() const;
//		void			setRows(size_t rows);
		size_t			getRows() const;

static std::ostream &print(std::ostream &o, Operand const &i);

};

std::ostream &operator<<(std::ostream &o, Matrix const &i);

#endif
