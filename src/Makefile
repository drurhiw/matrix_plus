CC=g++ -std=c++17 -Wall -Werror -Wextra -pedantic -g
CHECKFLAGS=-lgtest
REPORTDIR=gcov_report
GCOV=--coverage
OS = $(shell uname)

all: s21_matrix_oop.a test gcov_report

s21_matrix_oop.a:
	$(CC) -c s21_matrix_oop.cpp -o matrix_oop.o
	ar rcs matrix_oop.a matrix_oop.o

test: clean
	$(CC) $(GCOV) -c s21_matrix_oop.cpp 
	$(CC) -c s21_test.cpp $(CHECKFLAGS)
	$(CC) $(GCOV) -o matrix_test s21_test.o s21_matrix_oop.o $(CHECKFLAGS)
	./matrix_test

format:
	cp ../materials/linters/.clang-format ../src
	clang-format -i s21_matrix_oop.cpp
	clang-format -i s21_matrix_oop.h
	clang-format -i *.h s21_test.cpp
	clang-format -n s21_matrix_oop.cpp
	clang-format -n s21_matrix_oop.h
	clang-format -n *.h s21_test.cpp
	rm .clang-format

clang-format:
	cp ../materials/linters/.clang-format ../src
	clang-format -n s21_matrix_oop.cpp
	clang-format -n s21_matrix_oop.h
	clang-format -n *.h s21_test.cpp
	rm .clang-format

leaks: test
ifeq ($(OS), Linux)
	CK_FORK=no valgrind --tool=memcheck --leak-check=full ./matrix_test
else
	leaks -atExit -- ./matrix_test
endif

gcov_report:
	@$(CC) $(CFLAGS) s21_test.cpp s21_matrix_oop.cpp -lgtest --coverage -o report.out
	@./report.out
	@lcov -t "report" -o report.info --no-external -c -d .
	@genhtml -o ./report report.info
	@rm -rf *.gcda *.gcno *.info *.out
	@open ./report/src/index.html

clean:
	rm -rf ./*.o ./*.a ./a.out ./*.gcno ./*.gcda ./$(REPORTDIR) *.info ./*.info report matrix_test matrix_oop

rebuild: clean all