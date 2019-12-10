#include "../inc/Matrix.hpp"

Matrix::Matrix()
{
}

Matrix::Matrix(std::vector<double> values, size_t columns, size_t rows) : values_(std::move(values)), columns_(columns),
                                                                          rows_(rows)
{
}

Matrix::Matrix(Matrix &matrix)
{
    *this = matrix;
}

Matrix::~Matrix()
{
}

const std::vector<double> Matrix::getValues() const
{
    return this->values_;
}

size_t Matrix::getColumns() const
{
    return this->columns_;
}

size_t Matrix::getRows() const
{
    return this->rows_;
}

std::ostream &Matrix::print(std::ostream &o, Operand const &i)
{
    const auto *tmp = dynamic_cast<const Matrix *>(&i);
    size_t col = tmp->getColumns();
    size_t row = tmp->getRows();
    std::vector<double> val = tmp->getValues();

    o << "[MATRIX (" << col << ", " << row << ") | " << i.getSelf() << " | " << std::endl;
    for (int iter_y = 0; iter_y < col; iter_y++)
    {
        for (int iter_x = 0; iter_x < row; iter_x++)
        {
            o << "[" << val[row * iter_y + iter_x] << "]";
        }
        o << std::endl;
    }
    return (o);
}

std::ostream &operator<<(std::ostream &o, Matrix const &i)
{
    Matrix::print(o, i);
    return (o);
}
