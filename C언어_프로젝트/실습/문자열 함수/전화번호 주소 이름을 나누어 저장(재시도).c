/********************************************
이름, 전화번호, 주소를 한 줄로 입력 
012-233-2334 홍길동 서울시 마포구
서울시 노원구 무슨동 155번지 홍길동 010-5653-2949
010 2344 8888 서울시 강남구 강남대로 155 홍길동

출력예시)
이름: 홍길동
전화번호: 010-1234-5654
주소: 서울시 강남구 강남대로 122
*************************************************/

// 이름, 전화번호, 주소를 '정보'라 칭함

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define TOKEN " .-_:;*&^%"


void main() {
	char line[100]; // 정보를 입력받을 한 줄
	gets(line); // gets함수로 정보를 입력 받음

	char* token1; // 전화번호 토큰(1)
	char* token2; // 전화번호 토큰(2)
	char* token3; // 전화번호 토큰(3)
	char number_token[12]={NULL,}; // 11+1(NULL값)

	int i = 0; //전화번호를 전화번호 저장 문자배열인  number_token[11]에 넣을 때 필요한 인덱스


	// 전화번호로 시작하는지 확인(숫자로 시작하는지 확인하면 됨)
	if (isdigit(line[1])) {

		// 전화번호를 공백없이 출력하기
		// 조건: 전화번호 구분자가 무조건 2개 
		printf("전화번호로 시작\n");
		token1 = strtok(line, TOKEN);
		printf("%s", token1);

		for (i = 0; i < strlen(token1); i++) {
			number_token[i] = token1[i];
		}
		int j = i; //다음에 number_token에 저장할 때 [i]첨자부터 시작해 저장하려고!


		token2 = strtok(NULL, TOKEN);
		printf("%s", token2);


		int ii = 0;
		for (i = j; i < j+strlen(token2); i++) {
			number_token[i] = token2[ii];
			ii++;
		}
		int k = j + strlen(token2);


		ii = 0;
		token3= strtok(NULL, TOKEN);
		printf("%s", token3);
		for (i = k; i < k+strlen(token3); i++) {
			number_token[i] = token3[ii];
			ii++;
		}

		puts("\n");

		printf("number_toekn에 저장된 전화번호: %s\n", number_token);



		// 숫자 다음에는 무조건 문자가 나올 것임
		// 그 문자가 주소의 첫 글자인지, 이름의 첫 글자인지 파악해야 함

		char* sido[14] = { "서울", "경기", "인천", "강원", "충청", "경상", "전라", "제주", "세종", "대전", "대구", "부산", "울산", "광주" };


	
		for (int h = 0; h < 20; h++) {
			if (strstr(line,sido[h]) != NULL)
				printf("시도 있다!");
			else printf("%d 시도 없다!\n",h);
		}
	
	

	}
	else {
		printf("문자로 시작");
	}

}
