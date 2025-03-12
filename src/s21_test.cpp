#include <gtest/gtest.h>

#include "s21_matrix_oop.h"

// Тесты для конструктора копирования
TEST(S21MatrixTest, CopyConstructor) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(1, 1) = 2.0;

  S21Matrix copy(matrix);
  EXPECT_EQ(copy(0, 0), 1.0);
  EXPECT_EQ(copy(1, 1), 2.0);
}

// Тесты для конструктора перемещения
TEST(S21MatrixTest, MoveConstructor) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(1, 1) = 2.0;

  S21Matrix moved_matrix(std::move(matrix));
  EXPECT_EQ(moved_matrix(0, 0), 1.0);
  EXPECT_EQ(moved_matrix(1, 1), 2.0);
}

// Тесты для оператора сложения
TEST(S21MatrixTest, OperatorAddition) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix1(0, 0) = 1.0;
  matrix2(0, 0) = 2.0;

  S21Matrix result = matrix1 + matrix2;
  EXPECT_EQ(result(0, 0), 3.0);
}

// Тесты для оператора вычитания
TEST(S21MatrixTest, OperatorSubtraction) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix1(0, 0) = 5.0;
  matrix2(0, 0) = 3.0;

  S21Matrix result = matrix1 - matrix2;
  EXPECT_EQ(result(0, 0), 2.0);
}

// Тесты для оператора умножения на число
TEST(S21MatrixTest, OperatorMultiplicationByNumber) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(1, 1) = 2.0;

  S21Matrix result = matrix * 3.0;
  EXPECT_EQ(result(0, 0), 3.0);
  EXPECT_EQ(result(1, 1), 6.0);
}

// Тесты для оператора умножения на матрицу
TEST(S21MatrixTest, OperatorMultiplicationByMatrix) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix1(0, 0) = 1.0;
  matrix1(0, 1) = 2.0;
  matrix1(1, 0) = 3.0;
  matrix1(1, 1) = 4.0;
  matrix2(0, 0) = 2.0;
  matrix2(0, 1) = 0.0;
  matrix2(1, 0) = 1.0;
  matrix2(1, 1) = 2.0;

  S21Matrix result = matrix1 * matrix2;
  EXPECT_EQ(result(0, 0), 4.0);
  EXPECT_EQ(result(0, 1), 4.0);
  EXPECT_EQ(result(1, 0), 10.0);
  EXPECT_EQ(result(1, 1), 8.0);
}

// Тесты для оператора сравнения
TEST(S21MatrixTest, OperatorEquality) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix1(0, 0) = 1.0;
  matrix2(0, 0) = 1.0;

  EXPECT_TRUE(matrix1 == matrix2);
}

// Тесты для нахождения детерминанта
TEST(S21MatrixTest, DeterminantTest) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;

  double det = matrix.Determinant();
  EXPECT_DOUBLE_EQ(det, -2.0);
}

// Тесты для транспонирования
TEST(S21MatrixTest, TransposeTest) {
  S21Matrix matrix(2, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;

  S21Matrix transposed = matrix.Transpose();
  EXPECT_EQ(transposed(0, 1), 4.0);
  EXPECT_EQ(transposed(2, 0), 3.0);
}

TEST(MatrixTest, DefaultConstructor) {
  S21Matrix matrix;
  EXPECT_EQ(matrix.GetRows(), 3);
  EXPECT_EQ(matrix.GetCols(), 3);
}

TEST(MatrixTest, ParametrizedConstructor) {
  S21Matrix matrix(2, 3);
  EXPECT_EQ(matrix.GetRows(), 2);
  EXPECT_EQ(matrix.GetCols(), 3);
}

TEST(MatrixTest, InvalidConstructor) {
  EXPECT_THROW(S21Matrix matrix(-1, 3), std::invalid_argument);
}

TEST(MatrixTest, CopyConstructor) {
  S21Matrix original(2, 2);
  original(0, 0) = 1.0;
  S21Matrix copy(original);
  EXPECT_EQ(copy(0, 0), 1.0);
  EXPECT_EQ(copy.GetRows(), 2);
  EXPECT_EQ(copy.GetCols(), 2);
}

TEST(MatrixTest, MoveConstructor) {
  S21Matrix original(2, 2);
  original(0, 0) = 1.0;
  S21Matrix moved(std::move(original));
  EXPECT_EQ(moved(0, 0), 1.0);
  EXPECT_EQ(moved.GetRows(), 2);
  EXPECT_EQ(moved.GetCols(), 2);
  EXPECT_EQ(original.GetRows(), 0);
  EXPECT_EQ(original.GetCols(), 0);
}

// Операторы доступа
TEST(MatrixTest, OperatorAccessValid) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  EXPECT_EQ(matrix(0, 0), 1.0);
}

TEST(MatrixTest, OperatorAccessInvalid) {
  S21Matrix matrix(3, 3);
  EXPECT_THROW(matrix(5, 5), std::out_of_range);
}

// Операторы
TEST(MatrixTest, OperatorPlus) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix1(0, 0) = 1.0;
  matrix2(0, 0) = 2.0;
  S21Matrix result = matrix1 + matrix2;
  EXPECT_EQ(result(0, 0), 3.0);
}

TEST(MatrixTest, OperatorMinus) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix1(0, 0) = 3.0;
  matrix2(0, 0) = 2.0;
  S21Matrix result = matrix1 - matrix2;
  EXPECT_EQ(result(0, 0), 1.0);
}

TEST(MatrixTest, OperatorMultiplyNumber) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 2.0;
  S21Matrix result = matrix * 3.0;
  EXPECT_EQ(result(0, 0), 6.0);
}

TEST(MatrixTest, OperatorMultiplyMatrix) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix1(0, 0) = 2.0;
  matrix2(0, 0) = 3.0;
  S21Matrix result = matrix1 * matrix2;
  EXPECT_EQ(result(0, 0), 6.0);
}

// Функции
TEST(MatrixTest, SumMatrixValid) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix1(0, 0) = 1.0;
  matrix2(0, 0) = 2.0;
  matrix1.SumMatrix(matrix2);
  EXPECT_EQ(matrix1(0, 0), 3.0);
}

TEST(MatrixTest, SubMatrixValid) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix1(0, 0) = 3.0;
  matrix2(0, 0) = 2.0;
  matrix1.SubMatrix(matrix2);
  EXPECT_EQ(matrix1(0, 0), 1.0);
}

TEST(MatrixTest, MulNumberValid) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 2.0;
  matrix.MulNumber(3.0);
  EXPECT_EQ(matrix(0, 0), 6.0);
}

TEST(MatrixTest, MulMatrixValid) {
  S21Matrix matrix1(2, 2);
  S21Matrix matrix2(2, 2);
  matrix1(0, 0) = 2.0;
  matrix2(0, 0) = 3.0;
  matrix1.MulMatrix(matrix2);
  EXPECT_EQ(matrix1(0, 0), 6.0);
}

TEST(MatrixTest, TransposeValid) {
  S21Matrix matrix(2, 3);
  matrix(0, 1) = 1.0;
  S21Matrix result = matrix.Transpose();
  EXPECT_EQ(result(1, 0), 1.0);
}

TEST(MatrixTest, DeterminantValid) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(1, 0) = 3.0;
  matrix(1, 1) = 4.0;
  EXPECT_EQ(matrix.Determinant(), -2.0);
}

TEST(MatrixTest, CalcMinorValid) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(1, 1) = 1.0;
  S21Matrix minor = matrix.CalcMinor(0, 0);
  EXPECT_EQ(minor(0, 0), 1.0);
}

TEST(MatrixTest, InverseMatrixValid) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 4.0;
  matrix(0, 1) = 7.0;
  matrix(1, 0) = 2.0;
  matrix(1, 1) = 6.0;
  S21Matrix inverse = matrix.InverseMatrix();
  EXPECT_NEAR(inverse(0, 0), 0.6, 1e-7);
  EXPECT_NEAR(inverse(0, 1), -0.7, 1e-7);
  EXPECT_NEAR(inverse(1, 0), -0.2, 1e-7);
  EXPECT_NEAR(inverse(1, 1), 0.4, 1e-7);
}

// Тесты для обратной матрицы
TEST(S21MatrixTest, InverseMatrixTest) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 4.0;
  matrix(0, 1) = 7.0;
  matrix(1, 0) = 2.0;
  matrix(1, 1) = 6.0;

  S21Matrix inverse = matrix.InverseMatrix();
  EXPECT_NEAR(inverse(0, 0), 0.6, 1e-7);
  EXPECT_NEAR(inverse(1, 0), -0.2, 1e-7);
}

TEST(S21MatrixTest, Determinant_3x3) {
  // Инициализация матрицы 3x3
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 0.0;
  matrix(1, 1) = 1.0;
  matrix(1, 2) = 4.0;
  matrix(2, 0) = 5.0;
  matrix(2, 1) = 6.0;
  matrix(2, 2) = 0.0;

  // Ожидаемый результат
  double expected_det = 1.0 * (1.0 * 0.0 - 4.0 * 6.0) -
                        2.0 * (0.0 * 0.0 - 4.0 * 5.0) +
                        3.0 * (0.0 * 6.0 - 1.0 * 5.0);

  // Проверка результата
  ASSERT_DOUBLE_EQ(matrix.Determinant(), expected_det);
}

// Тест для вычисления определителя 2x2 матрицы
TEST(S21MatrixTest, Determinant_2x2) {
  S21Matrix matrix(2, 2);
  matrix(0, 0) = 3.0;
  matrix(0, 1) = 8.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 6.0;

  double expected_det = 3.0 * 6.0 - 8.0 * 4.0;

  ASSERT_DOUBLE_EQ(matrix.Determinant(), expected_det);
}

// Тест для вычисления определителя 1x1 матрицы
TEST(S21MatrixTest, Determinant_1x1) {
  S21Matrix matrix(1, 1);
  matrix(0, 0) = 5.0;

  double expected_det = 5.0;

  ASSERT_DOUBLE_EQ(matrix.Determinant(), expected_det);
}

// Тест для вырожденной матрицы (нулевой определитель)
TEST(S21MatrixTest, Determinant_SingularMatrix) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1.0;
  matrix(0, 1) = 2.0;
  matrix(0, 2) = 3.0;
  matrix(1, 0) = 4.0;
  matrix(1, 1) = 5.0;
  matrix(1, 2) = 6.0;
  matrix(2, 0) = 7.0;
  matrix(2, 1) = 8.0;
  matrix(2, 2) = 9.0;

  // Определитель вырожденной матрицы должен быть 0
  ASSERT_DOUBLE_EQ(matrix.Determinant(), 0.0);
}

TEST(S21MatrixTest, OperatorPlusEqual) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);

  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  B(0, 0) = 5.0;
  B(0, 1) = 6.0;
  B(1, 0) = 7.0;
  B(1, 1) = 8.0;

  A += B;

  EXPECT_DOUBLE_EQ(A(0, 0), 6.0);
  EXPECT_DOUBLE_EQ(A(0, 1), 8.0);
  EXPECT_DOUBLE_EQ(A(1, 0), 10.0);
  EXPECT_DOUBLE_EQ(A(1, 1), 12.0);
}

TEST(S21MatrixTest, OperatorMinusEqual) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);

  A(0, 0) = 10.0;
  A(0, 1) = 8.0;
  A(1, 0) = 6.0;
  A(1, 1) = 4.0;

  B(0, 0) = 1.0;
  B(0, 1) = 2.0;
  B(1, 0) = 3.0;
  B(1, 1) = 4.0;

  A -= B;

  EXPECT_DOUBLE_EQ(A(0, 0), 9.0);
  EXPECT_DOUBLE_EQ(A(0, 1), 6.0);
  EXPECT_DOUBLE_EQ(A(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(A(1, 1), 0.0);
}

TEST(S21MatrixTest, OperatorMultiplyEqualNumber) {
  S21Matrix A(2, 2);

  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  A *= 2.0;

  EXPECT_DOUBLE_EQ(A(0, 0), 2.0);
  EXPECT_DOUBLE_EQ(A(0, 1), 4.0);
  EXPECT_DOUBLE_EQ(A(1, 0), 6.0);
  EXPECT_DOUBLE_EQ(A(1, 1), 8.0);
}

TEST(S21MatrixTest, OperatorMultiplyEqualMatrix) {
  S21Matrix A(2, 2);
  S21Matrix B(2, 2);

  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  B(0, 0) = 5.0;
  B(0, 1) = 6.0;
  B(1, 0) = 7.0;
  B(1, 1) = 8.0;

  A *= B;

  EXPECT_DOUBLE_EQ(A(0, 0), 19.0);
  EXPECT_DOUBLE_EQ(A(0, 1), 22.0);
  EXPECT_DOUBLE_EQ(A(1, 0), 43.0);
  EXPECT_DOUBLE_EQ(A(1, 1), 50.0);
}

TEST(S21MatrixTest, OperatorAccessNormalCase) {
  S21Matrix A(2, 2);

  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  EXPECT_DOUBLE_EQ(A(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(A(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(A(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(A(1, 1), 4.0);
}

TEST(S21MatrixTest, OperatorAccessOutOfRange) {
  S21Matrix A(2, 2);

  // Установка элементов матрицы
  A(0, 0) = 1.0;
  A(0, 1) = 2.0;
  A(1, 0) = 3.0;
  A(1, 1) = 4.0;

  // Проверка на исключение при выходе за пределы
  EXPECT_THROW(A(2, 1), std::out_of_range);  // Ряд вне диапазона
  EXPECT_THROW(A(1, 2), std::out_of_range);  // Колонка вне диапазона
  EXPECT_THROW(A(-1, 0), std::out_of_range);  // Отрицательный ряд
  EXPECT_THROW(A(0, -1), std::out_of_range);  // Отрицательная колонка
}

// Тест для проверки исключения на неверные размеры матрицы в конструкторе
TEST(S21MatrixTest, ConstructorInvalidSize) {
  EXPECT_THROW(S21Matrix(-2, 3), std::invalid_argument);
  EXPECT_THROW(S21Matrix(3, -2), std::invalid_argument);
  EXPECT_THROW(S21Matrix(0, 0), std::invalid_argument);
}

// Тест для проверки исключения при доступе к элементам вне диапазона
TEST(S21MatrixTest, OutOfRangeAccess) {
  S21Matrix matrix(3, 3);

  // Проверка на попытку доступа к недопустимым индексам
  EXPECT_THROW(matrix(-1, 0), std::out_of_range);
  EXPECT_THROW(matrix(0, -1), std::out_of_range);
  EXPECT_THROW(matrix(3, 0), std::out_of_range);
  EXPECT_THROW(matrix(0, 3), std::out_of_range);

  // Для константной версии оператора
  const S21Matrix const_matrix(3, 3);
  EXPECT_THROW(const_matrix(-1, 0), std::out_of_range);
  EXPECT_THROW(const_matrix(0, -1), std::out_of_range);
  EXPECT_THROW(const_matrix(3, 0), std::out_of_range);
  EXPECT_THROW(const_matrix(0, 3), std::out_of_range);
}

// Тест для проверки исключения при суммировании матриц разного размера
TEST(S21MatrixTest, SumMatrixInvalidSize) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(2, 2);

  // Проверка на попытку сложить матрицы разных размеров
  EXPECT_THROW(matrix1 += matrix2, std::invalid_argument);
  EXPECT_THROW(matrix1.SumMatrix(matrix2), std::invalid_argument);
}

// Тест для проверки исключения при вычитании матриц разного размера
TEST(S21MatrixTest, SubMatrixInvalidSize) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(2, 2);

  // Проверка на попытку вычесть матрицы разных размеров
  EXPECT_THROW(matrix1 -= matrix2, std::invalid_argument);
  EXPECT_THROW(matrix1.SubMatrix(matrix2), std::invalid_argument);
}

// Тест для проверки исключения при умножении матриц с несовместимыми размерами
TEST(S21MatrixTest, MulMatrixInvalidSize) {
  S21Matrix matrix1(3, 2);
  S21Matrix matrix2(3, 3);

  // Проверка на попытку умножить несовместимые матрицы
  EXPECT_THROW(matrix1 *= matrix2, std::invalid_argument);
  EXPECT_THROW(matrix1.MulMatrix(matrix2), std::invalid_argument);
}

// Тест для проверки исключения при вычислении определителя неквадратной матрицы
TEST(S21MatrixTest, DeterminantNonSquareMatrix) {
  S21Matrix matrix(3, 2);

  // Проверка на попытку вычислить определитель для неквадратной матрицы
  EXPECT_THROW(matrix.Determinant(), std::invalid_argument);
}

// Тест для проверки исключения при инверсии матрицы, которая не является
// обратимой
TEST(S21MatrixTest, InverseMatrixSingular) {
  S21Matrix matrix(3, 3);
  matrix(0, 0) = 1;
  matrix(1, 1) = 0;  // Делает матрицу необратимой (с определителем 0)

  // Проверка на попытку инверсии сингулярной матрицы
  EXPECT_THROW(matrix.InverseMatrix(), std::invalid_argument);
}

TEST(S21MatrixTest, CalcComplementsThrowsErrorWhenNotSquare) {
  S21Matrix matrix(2, 3);  // Неквадратная матрица 2x3

  try {
    matrix.CalcComplements();
    FAIL() << "Expected std::invalid_argument";  // Ожидаем выброс исключения
  } catch (const std::invalid_argument& e) {
    EXPECT_EQ(std::string(e.what()), "Matrix must be square");
  } catch (...) {
    FAIL() << "Expected std::invalid_argument";  // Если выброшено другое
                                                 // исключение
  }
}

TEST(S21MatrixTest, CalcMinorThrowsErrorWhenNotSquareOrSmall) {
  // Тест для неквадратной матрицы
  S21Matrix non_square_matrix(2, 3);  // Неквадратная матрица 2x3
  try {
    non_square_matrix.CalcMinor(0, 0);
    FAIL() << "Expected std::invalid_argument";  // Ожидаем выброс исключения
  } catch (const std::invalid_argument& e) {
    EXPECT_EQ(std::string(e.what()),
              "Matrix must be square and have at least 2 dimensions");
  } catch (...) {
    FAIL() << "Expected std::invalid_argument";  // Если выброшено другое
                                                 // исключение
  }

  // Тест для матрицы меньшей чем 2x2
  S21Matrix small_matrix(1, 1);  // Матрица 1x1
  try {
    small_matrix.CalcMinor(0, 0);
    FAIL() << "Expected std::invalid_argument";  // Ожидаем выброс исключения
  } catch (const std::invalid_argument& e) {
    EXPECT_EQ(std::string(e.what()),
              "Matrix must be square and have at least 2 dimensions");
  } catch (...) {
    FAIL() << "Expected std::invalid_argument";  // Если выброшено другое
                                                 // исключение
  }
}

TEST(S21MatrixTest, InverseMatrixThrowsErrorWhenNotSquare) {
  // Создаем неквадратную матрицу 2x3
  S21Matrix non_square_matrix(2, 3);

  // Ожидаем, что будет выброшено исключение std::invalid_argument
  try {
    non_square_matrix.InverseMatrix();
    FAIL()
        << "Expected std::invalid_argument";  // Если исключение не выброшено,
                                              // тест должен упасть
  } catch (const std::invalid_argument& e) {
    // Проверяем, что сообщение об ошибке соответствует ожидаемому
    EXPECT_EQ(std::string(e.what()), "Matrix must be square");
  } catch (...) {
    // Если выброшено другое исключение, тест должен упасть
    FAIL() << "Expected std::invalid_argument";
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
