#include <iostream>
using namespace std;

class Rectangle {
public: // 멤버에 대한 접근 지정자
	int width;
	int height;
	int getArea();
}; // 클래스 선언부를 닫는 괄호에는 ; 

int Rectangle::getArea() {
	return width * height;
} // 클래스 구현부: 클래스 선언부에 선언된 멤버 함수 코드 구현 

int main() {
	Rectangle rect;	// 객체 rect 생성
	rect.width = 3;
	rect.height = 5;
	cout << "사각형의 면적은 " << rect.getArea() << endl;
}
