#include "../inc/Matrix.hpp"

Matrix::Matrix()
{
}

Matrix::Matrix(t_matrix array, size_t columns, size_t rows): values_(array), columns_(columns), rows_(rows)
{
}

Matrix::Matrix(Matrix &matrix)
{
	*this = matrix;
}

Matrix::~Matrix()
{
	for (int i = 0; i < values_.size(); ++i)
	{
		values_[i].clear();
	}
	values_.clear();
}

Operand const * Matrix::operator=( Operand const & rhs )
{
	(void)rhs;
	return this;
}

Operand const * Matrix::operator+( Operand const & rhs ) // Sum
{
	(void)rhs;
	return this;
}

Operand const * Matrix::operator-( Operand const & rhs ) // Difference
{
	(void)rhs;
	return this;
}

Operand const * Matrix::operator*( Operand const & rhs ) // Product
{
	(void)rhs;
	return this;
}

Operand const * Matrix::operator/( Operand const & rhs ) // Quotient
{
	(void)rhs;
	return this;
}

Operand const * Matrix::operator%( Operand const & rhs ) // Modulo
{
	(void)rhs;
	return this;
}


void			Matrix::setValues(std::vector<std::vector<double>> array)
{
	values_ = array;	
}

const t_matrix	Matrix::getValues()
{
	return values_;
}

void			Matrix::addValuesRow(std::vector<double> row)
{
	values_.push_back(row);
}

void			Matrix::assignValue(double value, size_t y, size_t x)
{
	if (y < values_.size() && x < values_[y].size())
		values_[y][x] = value;
}

// voir si d'autres sont necessaires

void			Matrix::setColumns(size_t col)
{
	columns_ = col;
}

size_t			Matrix::getColumns()
{
	return columns_;
}

void			Matrix::setRows(size_t rows)
{
	rows_ = rows;
}

size_t			Matrix::getRows()
{
	return rows_;
}
