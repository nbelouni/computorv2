#include "../inc/Matrix.hpp"

Matrix::Matrix()
{
    this->setType(MATRIX);
    columns_ = 0;
    rows_ = 0;
}

Matrix::Matrix(std::vector<double> values, size_t columns, size_t rows) : values_(std::move(values)), columns_(columns),
                                                                          rows_(rows)
{
    this->setType(MATRIX);
    if (columns_ * rows_ != values_.size())
    {
        throw std::logic_error(
                "in 'Matrix(std::vector<double> values, size_t columns, size_t rows)' number of values does not match columns * rows.");
    }
}

Matrix::Matrix(Matrix &matrix)
{
    this->setType(MATRIX);
    *this = matrix;
}

Matrix::Matrix(const Matrix *matrix)
{
    this->setType(MATRIX);
    this->values_ = matrix->values_;
    this->columns_ = matrix->columns_;
    this->rows_ = matrix->rows_;
}

Matrix::~Matrix()
{
}

Operand *Matrix::operator=(Operand const &rhs)
{
    if (this != &rhs)
    {
        if (rhs.getType() == MATRIX)
        {
            values_ = dynamic_cast<const Matrix *>(&rhs)->getValues();
            columns_ = dynamic_cast<const Matrix *>(&rhs)->getColumns();
            rows_ = dynamic_cast<const Matrix *>(&rhs)->getRows();
        }
        else
        {
            throw std::invalid_argument("in 'Operand *Matrix::operator=(Operand const &rhs)' rhs is not Invalid.");
        }
    }
    return (dynamic_cast<Operand *>(this));
}

Operand *Matrix::operator+(Operand const &rhs)
{
    Matrix *tmp;

    if (rhs.getType() == MATRIX)
    {
        if (this->getRows() == dynamic_cast<const Matrix *>(&rhs)->getRows() &&
            this->getColumns() == dynamic_cast<const Matrix *>(&rhs)->getColumns())
        {
            tmp = solveAdd(this, dynamic_cast<const Matrix *>(&rhs));
        }
        else
        {
            throw std::logic_error(
                    "in 'Operand *Matrix::operator+(Operand const &rhs)' rhs is a Matrix with different size.");
        }
    }
    else if (rhs.getType() == RATIONAL)
    {
        tmp = solveAdd(this, dynamic_cast<const Rational *>(&rhs)->getValue());
    }
    else
    {
        throw std::invalid_argument(
                "in 'Operand *Matrix::operator+(Operand const &rhs)' rhs is not Matrix or Rational.");
    }
    return tmp;
}

Operand *Matrix::operator-(Operand const &rhs)
{
    Matrix *tmp;

    if (rhs.getType() == MATRIX)
    {
        if (this->getRows() == dynamic_cast<const Matrix *>(&rhs)->getRows() &&
            this->getColumns() == dynamic_cast<const Matrix *>(&rhs)->getColumns())
        {
            tmp = solveSub(this, dynamic_cast<const Matrix *>(&rhs));
        }
        else
        {
            throw std::logic_error(
                    "in 'Operand *Matrix::operator-(Operand const &rhs)' rhs is a Matrix with different size.");
        }
    }
    else if (rhs.getType() == RATIONAL)
    {
        tmp = solveSub(this, dynamic_cast<const Rational *>(&rhs)->getValue());
    }
    else
    {
        throw std::invalid_argument(
                "in 'Operand *Matrix::operator-(Operand const &rhs)' rhs is not Matrix or Rational.");
    }
    return tmp;
}

Operand *Matrix::operator*(Operand const &rhs)
{
    Matrix *tmp;

    if (rhs.getType() == MATRIX)
    {
        if (this->getRows() == dynamic_cast<const Matrix *>(&rhs)->getRows() &&
            this->getColumns() == dynamic_cast<const Matrix *>(&rhs)->getColumns())
        {
            tmp = solveMul(this, dynamic_cast<const Matrix *>(&rhs));
        }
        else
        {
            throw std::logic_error(
                    "in 'Operand *Matrix::operator-(Operand const &rhs)' rhs is a Matrix with different size.");
        }
    }
    else if (rhs.getType() == RATIONAL)
    {
        tmp = solveMul(this, dynamic_cast<const Rational *>(&rhs)->getValue());
    }
    else
    {
        throw std::invalid_argument(
                "in 'Operand *Matrix::operator*(Operand const &rhs)' rhs is not Matrix or Rational.");
    }
    return tmp;
}

Operand *Matrix::dot(Operand const &lhs, Operand const &rhs)
{
    Matrix *tmp;

    if (lhs.getType() == MATRIX && rhs.getType() == MATRIX)
    {
        if (dynamic_cast<const Matrix *>(&lhs)->getColumns() == dynamic_cast<const Matrix *>(&rhs)->getRows())
        {
            // TODO https://en.wikipedia.org/wiki/Matrix_multiplication implement this shit.
        }
        else
        {
            throw std::logic_error("lhs columns != rhs rows.");
        }
    }
    else
    {
        throw std::invalid_argument("in 'Operand *Matrix::dot(Operand const &lhs, Operand const &rhs)' can only apply this on Matrices.");
    }

    return tmp;
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

Matrix *Matrix::solveAdd(const Matrix *a, const Matrix *b)
{
    auto *tmp = new Matrix(a);

    for (int i = 0; i < b->getValues().size(); i++)
        tmp->values_[i] += b->getValues()[i];
    return tmp;
}

Matrix *Matrix::solveAdd(const Matrix *a, double b)
{
    auto *tmp = new Matrix(a);

    for (int i = 0; i < tmp->getValues().size(); i++)
        tmp->values_[i] += b;
    return tmp;
}

Matrix *Matrix::solveSub(const Matrix *a, const Matrix *b)
{
    auto *tmp = new Matrix(a);

    for (int i = 0; i < b->getValues().size(); i++)
        tmp->values_[i] -= b->getValues()[i];
    return tmp;
}

Matrix *Matrix::solveSub(const Matrix *a, double b)
{
    auto *tmp = new Matrix(a);

    for (int i = 0; i < tmp->getValues().size(); i++)
        tmp->values_[i] -= b;
    return tmp;
}

Matrix *Matrix::solveMul(const Matrix *a, const Matrix *b)
{
    auto *tmp = new Matrix(a);

    for (int i = 0; i < b->getValues().size(); i++)
        tmp->values_[i] *= b->getValues()[i];
    return tmp;
}

Matrix *Matrix::solveMul(const Matrix *a, double b)
{
    auto *tmp = new Matrix(a);

    for (int i = 0; i < tmp->getValues().size(); i++)
        tmp->values_[i] *= b;
    return tmp;
}

std::ostream &operator<<(std::ostream &o, Matrix const &i)
{
    Matrix::print(o, i);
    return (o);
}
