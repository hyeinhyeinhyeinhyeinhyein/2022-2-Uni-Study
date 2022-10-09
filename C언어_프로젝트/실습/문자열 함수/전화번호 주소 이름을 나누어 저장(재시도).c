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

	// line에 실제로 저장된 글자수 
	int number_of_characters = 0;

	for (int number = 0; number < 100; number++) {
		if (line[number] != NULL)
			number_of_characters++;
		else break;
	}

	printf("총 글자 수는 %d\n", number_of_characters);



	char address[70]; //주소 저장 문자 배열





	char* token1; // 전화번호 토큰(1)
	char* token2; // 전화번호 토큰(2)
	char* token3; // 전화번호 토큰(3)
	char number_token[12] = { NULL, }; // 전화번호 저장 문자 배열, 11+1(NULL값)

	int i = 0; //전화번호를 전화번호 저장 문자배열인  number_token[11]에 넣을 때 필요한 인덱스


	// 전화번호로 시작하는지 확인(숫자로 시작하는지 확인하면 됨)
	if (isdigit(line[1])) {

		// 전화번호를 공백없이 출력하기
		// 조건: 전화번호 구분자가 무조건 2개 
		printf("전화번호로 시작\n");
		


		// 숫자 다음에는 무조건 문자가 나올 것임
		// 그 문자가 주소의 첫 글자인지, 이름의 첫 글자인지 파악해야 함


		char* city1 = strstr(line, "서울");
		char* city2 = strstr(line, "경기");
		char* city3 = strstr(line, "인천");
		char* city4 = strstr(line, "강원");
		char* city5 = strstr(line, "충청");
		char* city6 = strstr(line, "경상");
		char* city7 = strstr(line, "전라");
		char* city8 = strstr(line, "제주");
		char* city9 = strstr(line, "세종");
		char* city10 = strstr(line, "대전");
		char* city11 = strstr(line, "대구");
		char* city12 = strstr(line, "부산");
		char* city13 = strstr(line, "울산");
		char* city14 = strstr(line, "광주");

		int number_of_address = 0; //주소 길이

			if ((city1 - line) == 14 || (city2 - line) == 14|| (city3 - line) == 14 || (city4 - line) == 14 || (city5 - line) == 14 || (city6 - line) == 14 || (city7 - line) == 14 || (city8 - line) == 14 || (city9 - line) == 14 || (city10 - line) == 14 || (city11 - line) == 14 || (city12 - line) == 14 || (city13 - line) == 14 || (city14 - line) == 14) {
				int m = 0;
				for (int number = 14; number < number_of_characters - 5; number++) {
					// null문자(1), 이름 (3), 띄어쓰기(1)


					address[m] = line[number];
					printf("%c\n", address[m]);
					m++;
				}

				// 주소가 몇 글자인지
				for (int number = 0; number < 70; number++) {
					if (address[number] != NULL)
						number_of_address++;
					else break;
				}


				printf("주소길이: %d\n", number_of_address);


				// 주소 출력
				for (int i=0;i<= number_of_address;i++)
					printf("%c",address[i]);
			}
		
		else printf("이름먼저");




			// 저장하기, 출력하기


		// 전번 저장
			token1 = strtok(line, TOKEN);
			printf("%s", token1);

			for (i = 0; i < strlen(token1); i++) {
				number_token[i] = token1[i];
			}
			int j = i; //다음에 number_token에 저장할 때 [i]첨자부터 시작해 저장하려고!


			token2 = strtok(NULL, TOKEN);
			printf("%s", token2);


			int ii = 0;
			for (i = j; i < j + strlen(token2); i++) {
				number_token[i] = token2[ii];
				ii++;
			}
			int k = j + strlen(token2);


			ii = 0;
			token3 = strtok(NULL, TOKEN);
			printf("%s", token3);
			for (i = k; i < k + strlen(token3); i++) {
				number_token[i] = token3[ii];
				ii++;
			}

			puts("\n");

			printf("number_toekn에 저장된 전화번호: %s\n", number_token);



		

	}

		else {
			printf("문자로 시작");
		}

	}
