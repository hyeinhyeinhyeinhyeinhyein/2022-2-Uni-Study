#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class Histogram {
	string full_sentence;
	string string_content;
	char char_content;
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

	int theNumber = 0;

	for (int i = 97; i <= 122; i++) {
		for (int j = 0; j < full_sentence.length(); j++) {
			if(full_sentence[j] == (char)i)
				theNumber++;
		}
		cout << (char)i << "(" << theNumber << ")"<<"	"<<": ";
		for (int m = 0; m < theNumber; m++) {
			cout << "*";
		}
		cout << "\n";
		theNumber= 0;
	}

}

void main() {
	Histogram elvisHistro("Wise men say, only fools rush in But I can't help, ");
	elvisHistro.put("falling in love with you");
	elvisHistro.putc('-');
	elvisHistro.put("Elvis Presley");
	elvisHistro.print();



}
