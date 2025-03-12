#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <cmath>
#include <exception>
#include <iostream>
#define S21_EPS 1e-7

class S21Matrix {
 private:
  int rows_, cols_;
  double **matrix_;

  void AllocateMemory(int rows, int cols);
  void FreeMemory();

 public:
  int GetRows() const;
  int GetCols() const;
  // Конструкторы и деструктор
  S21Matrix();  // Конструктор по умолчанию
  S21Matrix(int rows, int cols);  // Конструктор с параметрами
  S21Matrix(const S21Matrix &other);  // Конструктор копирования
  S21Matrix(S21Matrix &&other) noexcept;  // Конструктор перемещения
  ~S21Matrix();                           // Деструктор

  // Методы для работы с матрицами
  bool EqMatrix(const S21Matrix &other) const;
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose() const;
  S21Matrix CalcMinor(int row, int col) const;
  S21Matrix CalcComplements() const;
  double Determinant() const;
  S21Matrix InverseMatrix() const;

  // Операторы
  S21Matrix operator+(const S21Matrix &other) const;
  S21Matrix operator-(const S21Matrix &other) const;
  S21Matrix operator*(double num) const;
  S21Matrix operator*(const S21Matrix &other) const;
  bool operator==(const S21Matrix &other) const;
  S21Matrix &operator=(const S21Matrix &other);
  S21Matrix &operator+=(const S21Matrix &other);
  S21Matrix &operator-=(const S21Matrix &other);
  S21Matrix &operator*=(double num);
  S21Matrix &operator*=(const S21Matrix &other);
  double &operator()(int i, int j);
  const double &operator()(int i, int j) const;
};

#endif  // S21_MATRIX_OOP_H