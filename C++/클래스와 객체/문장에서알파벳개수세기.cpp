#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class Histogram {
	string full_sentence;	// 최종적으로 알파벳 개수 검사할 문장
public:
	Histogram(string full_sentence);
	void put(string string_content);
	void putc(char char_content);
	void print();
};

Histogram::Histogram(string full_sentence) {
	this->full_sentence = full_sentence;
}

void Histogram::put(string string_content) {
	full_sentence.append(string_content);
}

void Histogram::putc(char char_content) {
	full_sentence += char_content;

}

void Histogram::print() {
	cout << full_sentence<<"\n"<< "\n";
	cout << "총 알파벳 수 " << full_sentence.length() << "\n" << "\n";
	
	for (int i = 0; i < full_sentence.length(); i++) { // 알파벳 비교 예정이라 대문자->소문자로 바꿈
		full_sentence[i] = tolower(full_sentence[i]);
	}

	int theNumber = 0;	//full_sentence에 들어있는 알파벳 개수 

	for (int i = 97; i <= 122; i++) {	// 'a'의 아스키코드: 97, 'z'의 아스키코드: 122
		for (int j = 0; j < full_sentence.length(); j++) { // full_sentence의 문자마다 반복문으로 돌아가는 알파벳의 아스키코드가 같은지를 체크함
			if(full_sentence[j] == (char)i)
				theNumber++;
		}
		cout << (char)i << "(" << theNumber << ")"<<"	"<<": ";
		for (int m = 0; m < theNumber; m++) {
			cout << "*";
		}
		cout << "\n";
		theNumber= 0; // 0으로 초기화 시켜주어야 다음 알파벳에서 출력되는 별 개수가 누적되지 않음
	}

}

void main() {
	Histogram elvisHistro("Wise men say, only fools rush in But I can't help, ");
	elvisHistro.put("falling in love with you");
	elvisHistro.putc('-');
	elvisHistro.put("Elvis Presley");
	elvisHistro.print();
}
