// memcpy함수 사용 - 메모리 복사하기
#include <stdio.h>
#include <string.h>

void main() {
	char ch1[15] = "0123456789";
	char ch2[15] = "1234567890";


	memcpy(ch1 + 1, ch2 + 3, 3); //ch+1는 ch+2부터 3byte를 복사받아라 // 0456456789
	puts(ch1);
}
