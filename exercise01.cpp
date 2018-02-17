#include <iostream>
#include <armadillo>

using namespace std;
using namespace arma;

int main() {
	cout << "Armadillo version: " << arma_version::as_string() << endl;

	//1a
	mat A;
	A << 6. << 9 << 2 << endr
		<< 1 << 8 << 2 << endr
		<< -3 << 1 << -6 << endr;
	A.print("A:");
	mat B;
	B << -4 << 7 << -7 << endr
		<< -1 << 6 << -5 << endr
		<< 2. << -5 << -1 << endr;
	B.print("B:");

	// Exercise 1b
	cout << "A * B:" << endl;
	cout << A * B << endl;
	cout << "A^4:" << endl;
	cout << A * A*A*A << endl;
	cout << "A' * B^(-1):" << endl;
	cout << trans(A) * inv(B) << endl;
	cout << "B.^3:" << endl;
	cout << pow(B, 3) << endl;
	cout << "A./B:" << endl;
	cout << A / B << endl;

	// Exercise 1c
	cout << "A\B:" << endl;
	cout << solve(A, B) << endl;

	// Exercise 1d (C)
	cout << "Exercise d. (i.e. matrix C):" << endl;
	mat C = 2 * A;
	mat AplusB = A + B;
	for (int i = 0; i < AplusB.n_cols; i++) {
		for (int j = 0; j < AplusB.n_rows; j++) {
			if (AplusB(i, j) < 5) {
				C(i, j) = 0;
			}
		}
	}
	cout << C << endl;

	// Exercise 1e
	cout << "Exercise 1e (1)" << endl;
	cout << B.rows(0, 1) * A.cols(1, 2) << endl;

	cout << "Exercise 1e (2)" << endl;
	mat Ahelper = A;
	Ahelper.col(0) = ones(3, 1);
	cout << Ahelper * B.col(1) << endl;

	cout << "Exercise 1e (3)" << endl;
	Ahelper = A;
	Ahelper.swap_rows(1, 2);
	Ahelper.row(1) = B.row(2);
	cout << A.row(2) * Ahelper << endl;

	cin.get();

	return 0;
}
