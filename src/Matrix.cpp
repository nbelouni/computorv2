#include "../inc/Matrix.hpp"

Matrix::Matrix()
{
    this->setType(MATRIX);
    columns_ = 0;
    rows_ = 0;
}

Matrix::Matrix(std::vector<double> values, size_t rows, size_t columns) : values_(std::move(values)),
                                                                          rows_(rows),
                                                                          columns_(columns)
{
    this->setType(MATRIX);
    if (columns_ * rows_ != values_.size())
    {
        throw std::logic_error(
                "in 'Matrix(std::vector<double> values, size_t columns, size_t rows)' number of values does not match rows * columns.");
    }
}

Matrix::Matrix(size_t rows, size_t columns)
{
    this->setType(MATRIX);
    this->values_.reserve(rows * columns);
    this->rows_ = rows;
    this->columns_ = columns;
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
            columns_ = dynamic_cast<const Matrix *>(&rhs)->getColumnsCount();
            rows_ = dynamic_cast<const Matrix *>(&rhs)->getRowsCount();
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
        if (this->getRowsCount() == dynamic_cast<const Matrix *>(&rhs)->getRowsCount() &&
            this->getColumnsCount() == dynamic_cast<const Matrix *>(&rhs)->getColumnsCount())
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
        if (this->getRowsCount() == dynamic_cast<const Matrix *>(&rhs)->getRowsCount() &&
            this->getColumnsCount() == dynamic_cast<const Matrix *>(&rhs)->getColumnsCount())
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
        if (this->getRowsCount() == dynamic_cast<const Matrix *>(&rhs)->getRowsCount() &&
            this->getColumnsCount() == dynamic_cast<const Matrix *>(&rhs)->getColumnsCount())
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

Operand *Matrix::operator/(Operand const &rhs)
{
    Matrix *tmp;

    if (rhs.getType() == MATRIX)
    {
        if (this->getRowsCount() == dynamic_cast<const Matrix *>(&rhs)->getRowsCount() &&
            this->getColumnsCount() == dynamic_cast<const Matrix *>(&rhs)->getColumnsCount())
        {
            tmp = solveDiv(this, dynamic_cast<const Matrix *>(&rhs));
        }
        else
        {
            throw std::logic_error(
                    "in 'Operand *Matrix::operator-(Operand const &rhs)' rhs is a Matrix with different size.");
        }
    }
    else if (rhs.getType() == RATIONAL)
    {
        tmp = solveDiv(this, dynamic_cast<const Rational *>(&rhs)->getValue());
    }
    else
    {
        throw std::invalid_argument(
                "in 'Operand *Matrix::operator/(Operand const &rhs)' rhs is not Matrix or Rational.");
    }
    return tmp;
}

Operand *Matrix::operator%(Operand const &rhs)
{
    Matrix *tmp;

    if (rhs.getType() == MATRIX)
    {
        if (this->getRowsCount() == dynamic_cast<const Matrix *>(&rhs)->getRowsCount() &&
            this->getColumnsCount() == dynamic_cast<const Matrix *>(&rhs)->getColumnsCount())
        {
            tmp = solveMod(this, dynamic_cast<const Matrix *>(&rhs));
        }
        else
        {
            throw std::logic_error(
                    "in 'Operand *Matrix::operator%(Operand const &rhs)' rhs is a Matrix with different size.");
        }
    }
    else if (rhs.getType() == RATIONAL)
    {
        tmp = solveMod(this, dynamic_cast<const Rational *>(&rhs)->getValue());
    }
    else
    {
        throw std::invalid_argument(
                "in 'Operand *Matrix::operator%(Operand const &rhs)' rhs is not Matrix or Rational.");
    }
    return tmp;
}

Operand *Matrix::dot(Operand const &lhs, Operand const &rhs)
{
    Matrix *tmp;

    if (lhs.getType() == MATRIX && rhs.getType() == MATRIX)
    {
        if (dynamic_cast<const Matrix *>(&lhs)->getColumnsCount() == dynamic_cast<const Matrix *>(&rhs)->getRowsCount())
        {
            // TODO https://en.wikipedia.org/wiki/Matrix_multiplication implement this shit.
            tmp = solveDot(this, dynamic_cast<const Matrix *>(&rhs));
        }
        else
        {
            throw std::logic_error("lhs columns != rhs rows.");
        }
    }
    else
    {
        throw std::invalid_argument(
                "in 'Operand *Matrix::dot(Operand const &lhs, Operand const &rhs)' can only apply this on Matrices.");
    }

    return tmp;
}

const std::vector<double> Matrix::getValues() const
{
    return this->values_;
}

size_t Matrix::getColumnsCount() const
{
    return this->columns_;
}

size_t Matrix::getRowsCount() const
{
    return this->rows_;
}

const std::vector<double> Matrix::getColumn(int col_index) const
{
    std::vector<double> vals;

    if (col_index < 0)
    {
        throw std::invalid_argument("Column access < 0.");
    }
    if (col_index >= this->getColumnsCount())
    {
        throw std::invalid_argument("Column access > than columns count.");
    }
    for (int iter_x = 0; iter_x < this->getRowsCount(); iter_x++)
    {
        for (int iter_y = 0; iter_y < this->getColumnsCount(); iter_y++)
        {
            if (iter_y == col_index)
            {
                vals.push_back(this->getValues()[iter_x * this->getColumnsCount() + iter_y]);
            }
        }
    }
    return vals;
}

const std::vector<double> Matrix::getRow(int row_index) const
{
    std::vector<double> vals;

    if (row_index < 0)
    {
        throw std::invalid_argument("Column access < 0.");
    }
    if (row_index >= this->getRowsCount())
    {
        throw std::invalid_argument("Column access > than columns count.");
    }
    for (int iter_x = 0; iter_x < this->getRowsCount(); iter_x++)
    {
        for (int iter_y = 0; iter_y < this->getColumnsCount(); iter_y++)
        {
            if (iter_x == row_index)
            {
                vals.push_back(this->getValues()[iter_x * this->getColumnsCount() + iter_y]);
            }
        }
    }
    return vals;
}

std::ostream &Matrix::print(std::ostream &o, Operand const &i)
{
    const auto *tmp = dynamic_cast<const Matrix *>(&i);
    size_t row = tmp->getRowsCount();
    size_t col = tmp->getColumnsCount();
    std::vector<double> val = tmp->getValues();

    o << "[MATRIX (" << row << ", " << col << ") | " << i.getSelf() << " | " << std::endl;
    if (!val.empty())
    {
        for (int iter_x = 0; iter_x < row; iter_x++)
        {
            for (int iter_y = 0; iter_y < col; iter_y++)
            {
                o << "[" << val[col * iter_x + iter_y] << "]";
            }
            o << std::endl;
        }
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

Matrix *Matrix::solveDiv(const Matrix *a, const Matrix *b)
{
    auto *tmp = new Matrix(a);

    for (int i = 0; i < b->getValues().size(); i++)
    {
        if (b->getValues()[i] != 0.0)
        {
            tmp->values_[i] /= b->getValues()[i];
        }
        else
        {
            throw std::logic_error(
                    "in 'Matrix *Matrix::solveDiv(const Matrix *a, const Matrix *b)' one of b values is 0.0, cannot divide by 0");
        }
    }
    return tmp;
}

Matrix *Matrix::solveDiv(const Matrix *a, double b)
{
    auto *tmp = new Matrix(a);

    for (int i = 0; i < tmp->getValues().size(); i++)
    {
        if (b != 0.0)
        {
            tmp->values_[i] /= b;
        }
        else
        {
            throw std::logic_error(
                    "in 'Matrix *Matrix::solveDiv(const Matrix *a, double b)' b == 0.0, cannot divide by 0");
        }
    }
    return tmp;
}

Matrix *Matrix::solveMod(const Matrix *a, const Matrix *b)
{
    auto *tmp = new Matrix(a);

    for (int i = 0; i < b->getValues().size(); i++)
    {
        if (b->getValues()[i] != 0.0)
        {
            if (isInteger(b->getValues()[i]))
            {
                tmp->values_[i] = static_cast<double>(static_cast<int>(tmp->values_[i] ) %
                                                      static_cast<int>(b->getValues()[i]));
            }
            else
            {
                throw std::logic_error(
                        "in 'Matrix *Matrix::solveMod(const Matrix *a, const Matrix *b)' one of b values not an integer.");
            }
        }
        else
        {
            throw std::logic_error(
                    "in 'Matrix *Matrix::solveMod(const Matrix *a, const Matrix *b)' one of b values is 0.0, cannot modulo by 0");
        }
    }
    return tmp;
}

Matrix *Matrix::solveMod(const Matrix *a, double b)
{
    auto *tmp = new Matrix(a);

    for (int i = 0; i < tmp->getValues().size(); i++)
    {
        if (b != 0.0)
        {
            if (isInteger(b))
            {
                tmp->values_[i] = static_cast<double>(static_cast<int>(tmp->values_[i]) % static_cast<int>(b));
            }
        }
        else
        {
            throw std::logic_error(
                    "in 'Matrix *Matrix::solveMod(const Matrix *a, double b)' b == 0.0, cannot modulo by 0");
        }
    }
    return tmp;
}

double Matrix::computeDotLine(std::vector<double> a, std::vector<double> b) const
{
    double res = 0.0;

    for (int i = 0; i < a.size(); i++)
    {
        res += a[i] * b[i];
    }
    return res;
}

Matrix *Matrix::solveDot(const Matrix *a, const Matrix *b)
{
    // col a == row b
    // size ==> row a * col b
    auto *tmp = new Matrix(a->getRowsCount(), b->getColumnsCount());

    for (int iter_x = 0; iter_x < tmp->getRowsCount(); iter_x++)
    {
        for (int iter_y = 0; iter_y < tmp->getColumnsCount(); iter_y++)
        {
            tmp->values_.push_back(computeDotLine(a->getRow(iter_x), b->getColumn(iter_y)));
        }
    }
    return tmp;
}

std::ostream &operator<<(std::ostream &o, Matrix const &i)
{
    Matrix::print(o, i);
    return (o);
}
