#include <iostream>
using namespace std;

class Circle { //Circle 클래스 선언부
public:
	int radius;
	Circle(); // 기본 생성자
	Circle(int r); // 매개변수가 있는 생성자 (같은 이름의 함수가 있지만 매개변수가 있음으로써 다른 함수로 판정)
	double getArea();
};

Circle::Circle() { 
	radius = 1;
	cout << "반지름 " << radius << " 원 생성" << endl;
} // 선언 

Circle::Circle(int r) {
	radius = r;	// 매개변수를 활용할 수 있음
	cout << "반지름 " << radius << " 원 생성" << endl;
}


double Circle::getArea() { // 클래스 구현부 
	return 3.14 * radius * radius;
}

int main() {
	Circle donut;	// 객체 donut 생성
	double area = donut.getArea();
	cout << "donut의 면적은 " << area << endl;

	Circle pizza(30);
	area = pizza.getArea();
	cout << "pizza 면적은 " << area << endl;
}
