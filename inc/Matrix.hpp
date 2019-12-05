#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "Computorv2.hpp"

typedef std::vector<std::vector<double>> t_matrix;

class Matrix: public Operand
{
	private:
	    t_matrix	_values;
		size_t		_columns;
		size_t		_rows;

	public:
		Matrix();
		Matrix(t_matrix array, size_t columns, size_t rows);
		Matrix(Matrix &matrix);
		~Matrix();

		Operand const * operator=( Operand const & rhs ); // Sum
		Operand const * operator+( Operand const & rhs ); // Sum
		Operand const * operator-( Operand const & rhs ); // Difference
		Operand const * operator*( Operand const & rhs ); // Product
		Operand const * operator/( Operand const & rhs ); // Quotient
		Operand const * operator%( Operand const & rhs ); // Modulo

		void			setValues(std::vector<std::vector<double>> array);
		const t_matrix	getValues();
		void			addValuesRow(std::vector<double> row);
		void			assignValue(double value, size_t y, size_t x);
		// voir si d'autres sont necessaires

		void			setColumns(size_t col);
		size_t			getColumns();
		void			setRows(size_t rows);
		size_t			getRows();
};

#endif
