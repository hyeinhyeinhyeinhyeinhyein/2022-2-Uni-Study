#include <iostream>
using namespace std;

class Matrix {
	int element1;
	int element2;
	int element3;
	int element4;
public:
	Matrix(int element1=0, int element2 = 0, int element3 = 0, int element4 = 0);

	void show();
	Matrix operator+ (Matrix op2);
	Matrix& operator+= (Matrix op2);
	bool operator== (Matrix op2);
};

Matrix::Matrix(int element1, int element2, int element3, int element4) {
	this->element1 = element1;
	this->element2 = element2;
	this->element3 = element3;
	this->element4 = element4;
}

void Matrix::show() {
	cout << "Matrix = { " << this->element1 << " " << this->element2 << " " << this->element3 << " " << this->element4 << " }" << endl;;
}

Matrix Matrix::operator+(Matrix op2) {
	Matrix tmp;
	tmp.element1 = element1 + op2.element1;
	tmp.element2 = element2 + op2.element2;
	tmp.element3 = element3 + op2.element3;
	tmp.element4 = element4 + op2.element4;
	return tmp;
}

Matrix& Matrix::operator+=(Matrix op2) {
	element1 = element1 + op2.element1;
	element2 = element2 + op2.element2;
	element3 = element3 + op2.element3;
	element4 = element4 + op2.element4;
	return *this;
}

bool Matrix::operator==(Matrix op2) {
	if (element1 == op2.element1 && element2 == op2.element2 && element3 == op2.element3 && element4 == op2.element4)
		return true;
	else return false;
}

int main() {
	Matrix a(1, 2, 3, 4), b(2, 3, 4, 5), c;
	c = a + b;
	a += b;
	a.show(), b.show(), c.show();
	if(a==c)
		cout << "a and c are the same" << endl;
}
