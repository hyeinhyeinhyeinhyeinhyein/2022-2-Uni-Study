#include <iostream>
using namespace std;

class MyIntStack {
	int p[10];
	int tos;
public:
	MyIntStack(); //생성자 함수
	bool push(int n); 
	bool pop(int& n); 
};

MyIntStack::MyIntStack() {
	tos = -1;
}

bool MyIntStack::push(int n) {
	if (tos > 8) return false;	// ++tos(전위연산자)라 이미 9가 되어있을 예정 
	else {
		p[++tos] = n;
		return true;
	}
}

bool MyIntStack::pop(int& n) {
		if (tos < 0) return false;
		else {
			n = p[tos--];
			return true;
		}
}

int main() {
	MyIntStack a;	//스택 바구니no.1
	for (int i = 0; i < 11; i++) {	//반복문 11번 도는 거임
		if (a.push(i)) cout << i << ' ';	//푸시된 값 에코
		else cout << endl << i + 1 << " 번째 stack full" << endl; 
	}
	int n;
	for (int i = 0; i < 11; i++) {	//반복문 11번 도는 거임
		if (a.pop(n)) cout << n << ' '; 
		else cout << endl << i + 1 << " 번째 stack empty" << endl; 
	}
	cout << endl;
}
