#include "s21_matrix_oop.h"

// Private

void S21Matrix::AllocateMemory(int rows, int cols) {
  matrix_ = new double*[rows];
  for (int i = 0; i < rows; ++i) {
    matrix_[i] = new double[cols]();
  }
}

void S21Matrix::FreeMemory() {
  for (int i = 0; i < rows_; ++i) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

// Constructor

S21Matrix::S21Matrix() : rows_(3), cols_(3) { AllocateMemory(rows_, cols_); }

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0) {
    throw std::invalid_argument("Invalid matrix size");
  }
  AllocateMemory(rows_, cols_);
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : rows_(other.rows_), cols_(other.cols_) {
  AllocateMemory(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other) noexcept
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix::~S21Matrix() {
  if (matrix_ != nullptr) {
    FreeMemory();
  }
}

// Public Methods

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrices must have the same dimensions");
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > S21_EPS) {
        throw std::invalid_argument("Matrices are not equal");
      }
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrices must have the same dimensions");
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument("Matrices must have the same dimensions");
  }

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Number of columns in the first matrix must match number of rows in "
        "the second matrix");
  }

  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < other.cols_; ++j) {
      result(i, j) = 0;
      for (int k = 0; k < cols_; ++k) {
        result(i, j) += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = result;
}

S21Matrix S21Matrix::Transpose() const {
  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

S21Matrix S21Matrix::CalcMinor(int row, int col) const {
  if (rows_ != cols_ || rows_ < 2) {
    throw std::invalid_argument(
        "Matrix must be square and have at least 2 dimensions");
  }

  S21Matrix result(rows_ - 1, cols_ - 1);
  int minor_row = 0;

  for (int i = 0; i < rows_; ++i) {
    if (i == row) continue;

    int minor_col = 0;
    for (int j = 0; j < cols_; ++j) {
      if (j == col) continue;

      result.matrix_[minor_row][minor_col] = matrix_[i][j];
      minor_col++;
    }
    minor_row++;
  }
  return result;
}

S21Matrix S21Matrix::CalcComplements() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix must be square");
  }

  S21Matrix result(rows_, cols_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      S21Matrix minor = CalcMinor(i, j);
      double minor_det = minor.Determinant();
      result.matrix_[i][j] = minor_det * ((i + j) % 2 == 0 ? 1 : -1);
    }
  }
  return result;
}

double S21Matrix::Determinant() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix must be square");
  }

  if (rows_ == 1) {
    return matrix_[0][0];
  }

  if (rows_ == 2) {
    return matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  }

  double det = 0.0;
  for (int j = 0; j < cols_; ++j) {
    S21Matrix minor = CalcMinor(0, j);
    double minor_det = minor.Determinant();
    det += matrix_[0][j] * minor_det * ((j % 2 == 0) ? 1 : -1);
  }

  return det;
}

S21Matrix S21Matrix::InverseMatrix() const {
  if (rows_ != cols_) {
    throw std::invalid_argument("Matrix must be square");
  }

  double determinant = Determinant();
  if (fabs(determinant) < 1e-7) {
    throw std::invalid_argument("Matrix is singular and cannot be inverted");
  }

  S21Matrix complements = CalcComplements();
  S21Matrix transposed = complements.Transpose();
  S21Matrix result(rows_, cols_);

  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      result.matrix_[i][j] = transposed.matrix_[i][j] / determinant;
    }
  }

  return result;
}

// Operators

S21Matrix S21Matrix::operator+(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(double num) const {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) const {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    if (matrix_ != nullptr) {
      FreeMemory();
    }
    rows_ = other.rows_;
    cols_ = other.cols_;
    AllocateMemory(rows_, cols_);
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = other.matrix_[i][j];
      }
    }
  }
  return *this;
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(double num) {
  MulNumber(num);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

double& S21Matrix::operator()(int row, int col) {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::out_of_range("Index out of range");
  }
  return matrix_[row][col];
}

const double& S21Matrix::operator()(int row, int col) const {
  if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
    throw std::out_of_range("Index out of range");
  }
  return matrix_[row][col];
}