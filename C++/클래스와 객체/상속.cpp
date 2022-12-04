#include <iostream>
using namespace std;

class BaseArray{
private:
	int capacity;
	int* mem;
protected:
	BaseArray(int capacity = 100) {
		this->capacity = capacity;
		mem = new int[capacity];	//인수만큼 메모리 할당
	}
	~BaseArray() { delete[] mem; }//생성자 소멸될 때, 메모리 해제
	void put(int index, int val) { mem[index] = val; }
	int get(int index) { return mem[index]; }
	int getCapacity() { return capacity; }
};

class Myqueue: public BaseArray {
private:
	int front;
	int rear;
public:
	Myqueue(int capacity = 100): BaseArray(capacity) { front = 0; rear = 0; }	// 명시적인 기본 클래스의 생성자 선택(p. 393)
	void enqueue(int val) { put(rear, val); rear++;	}
	int dequeue() {	return get(front++);}	
	int capacity() {return getCapacity();}
	int length() {return rear-front;}	

};

int main() {
	Myqueue mQ(100);
	int n;
	cout << "큐에 삽입할 5개의 정수를 입력하라>> ";
	for (int i = 0; i < 5; i++) {
		cin >> n;
		mQ.enqueue(n);
	}

	cout << "큐의 용량: " << mQ.capacity() << ", 큐의 크기: " << mQ.length() << endl;
	cout << "큐의 원소를 순서대로 제거하여 출력한다>> ";
	while (mQ.length() != 0) {
		cout << mQ.dequeue() << ' ';
	}
	cout << endl << "큐의 현재 크기: " << mQ.length() << endl;
}
