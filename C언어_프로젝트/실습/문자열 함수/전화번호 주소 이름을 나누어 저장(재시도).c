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

#define TOKEN " .-+_:;*&^%" // 전화번호를 저장할 때 어디에서 토큰화할지 기준이 되는 기호 모음 


void main() {

	char line[100]; // 정보를 입력받을 한 줄
	gets(line); // gets함수로 정보를 입력 받음


	 // line에 실제로 저장된 글자수 >> byte 크기, 위치X
	int number_of_characters = 0;
	for (int number = 0; number < 100; number++) {
		if (line[number] != NULL)	
			number_of_characters++;
		else break;
	}

	printf("총 글자 수는 %d\n", number_of_characters);


	char number_token[12] = { NULL, }; // 전화번호 저장 문자 배열, 11+1(NULL값)
	char address[70]; //주소 저장 문자 배열
	char name[7]; // 이름 저장 문자 배열, 배열 크기가 7인 이유는 (이름3글자*한글이 2byte)+NULL(1) = 7

	char* token1; // 전화번호 토큰(1)
	char* token2; // 전화번호 토큰(2)
	char* token3; // 전화번호 토큰(3)

	// 주소인지 확인할 때 사용할 정보 
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

	int number_of_address = 0; // address에 실제로 저장된 주소 길이

	int i = 0; // 전화번호를 전화번호 저장 문자배열인  number_token[12]에 넣을 때 필요한 인덱스
	int u = 0; // 이름을 이름 저장 문자배열인 name[7]에 넣을 때 필요한 인덱스 
	int m = 0; // 주소를 주소 저장 문자배열인 address[70]에 넣을 때 필요한 인덱스 


	// 전화번호로 시작하는지 확인(숫자로 시작하는지 확인하면 됨)
	if (line[0] == '0'|| line[0] == '1' || line[0] == '2' || line[0] == '3' || line[0] == '4' || line[0] == '5' || line[0] == '6' || line[0] == '7' || line[0] == '8' || line[0] == '9') {

		// 전화번호를 공백없이 출력하기
		// 조건: 전화번호 구분자가 무조건 2개 
		printf("전화번호로 시작\n");


		// 숫자 다음에는 무조건 문자가 나올 것임
		// 그 문자가 주소의 첫 글자인지, 이름의 첫 글자인지 파악해야 함

		/*=============================전화번호-주소-이름=============================*/
		if ((city1 - line) == 14 || (city2 - line) == 14 || (city3 - line) == 14 || (city4 - line) == 14 || (city5 - line) == 14 || (city6 - line) == 14 || (city7 - line) == 14 || (city8 - line) == 14 || (city9 - line) == 14 || (city10 - line) == 14 || (city11 - line) == 14 || (city12 - line) == 14 || (city13 - line) == 14 || (city14 - line) == 14) {

			for (int number = 14; number <= number_of_characters - 8; number++) {
				// null문자(1), 이름 (3*2=6), 띄어쓰기(1) 전까지 주소가 저장되어있음

				address[m] = line[number]; // line에서 받은 주소를 주소 배열에 저장하기 
				m++;
				number_of_address++; // 주소 몇 글자인지
			}

			printf("주소 글자 수: %d\n", number_of_address);


			//이름 저장
			for (int number = number_of_characters - 6; number <= number_of_characters; number++) {
				name[u] = line[number];
				u++;

			}

			//이름 출력
			printf("name에 저장된 이름: ");
			for (int i = 0; i <= 6; i++)
				printf("%c", name[i]);

			printf("\n");

		}


		/*=============================전화번호-이름-주소=============================*/
		else {
			printf("이름먼저\n");

			// 이름 저장하기
			for (int number = 14; number <= 20; number++) {
				name[u] = line[number];
				u++;
			}

			//이름 출력
			printf("name에 저장된 이름: ");
			for (int i = 0; i <= 6; i++)
				printf("%c", name[i]);

			printf("\n");

			// 주소 저장하기
			for (int number = 21; number <= number_of_characters; number++) {
				address[m] = line[number];
				m++;
			}

			// 주소 출력
			printf("address에 저장된 주소: ");
			for (int i = 0; i <= number_of_characters - 21; i++)
				printf("%c", address[i]);

			printf("\n");



		}

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

		// 주소 출력
		for (int i = 0; i <= number_of_address; i++)
			printf("%c", address[i]);

		printf("\n");



	}


	/*=============================문자로 시작=============================*/
	else {
		printf("문자로 시작");

		// 주소로 시작하는지 확인
		// 주소로 시작하는 것이 맞다면,
		/*=============================주소로 시작=============================*/
		if (city1 - line == 0 || city2 - line == 0 || city3 - line == 0 || city4 - line == 0 || city5 - line == 0 || city6 - line == 0 || city7 - line == 0 || city8 - line == 0 || city9 - line == 0 || city10 - line == 0 || city11 - line == 14 || city12 - line == 0 || city13 - line == 0 || city14 - line == 0) {

			// 주소-이름-전화번호인지 확인
			// 가장 마지막에 써진 문자가 숫자면 주소-이름-전화번호 확정
			/*=============================주소-이름-전화번호=============================*/
			if (line[number_of_characters-1] == '0' || line[number_of_characters-1] == '1' || line[number_of_characters-1] == '2' || line[number_of_characters-1]=='3' || line[number_of_characters-1] == '4' || line[number_of_characters-1] == '5' || line[number_of_characters-1] == '6' || line[number_of_characters-1] == '7' || line[number_of_characters-1] == '8' || line[number_of_characters-1] == '9') {


				// 주소 저장하기 + 주소 길이 계산
				//띄어쓰기(1) 이름(6) 띄어쓰기(1) 전화번호(11) 널문자(1) 
				for (int number = 0; number <= number_of_characters - 20; number++) {
					address[m] = line[number];
					m++;
					number_of_address++;
				}


				// 이름 저장하기
				// 이름(6) 띄어쓰기(1) 전화번호(11) 널문자(1)
				for (int number = number_of_characters - 20; number <= number_of_characters - 14; number++) {
					name[u] = line[number];
					u++;
				}

				// 전번 저장
				char temp_phonenumber[14]; // 임시로 전화번호를 저장해놓을 문자배열, 배열 크기가 14인 이유: 번호 11자리, -도 2개 있고, NULL값 하나 
				int r = 0; // temp_phonenumber에 전화번호를 저장할 때 필요한 인덱스 숫자 

				for (int number = number_of_characters - 13; number < number_of_characters; number++) {
					temp_phonenumber[r] = line[number];
					r++;
				}

				temp_phonenumber[13] = NULL;

				token1 = strtok(temp_phonenumber, TOKEN);
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

				printf("\n");

				//이름 출력
				printf("name에 저장된 이름: ");
				for (int i = 0; i <= 6; i++)
					printf("%c", name[i]);
				printf("\n");

				// 주소 출력
				printf("address에 저장된 주소: ");
				for (int i = 0; i <= number_of_characters - 21; i++)
					printf("%c", address[i]);
				printf("\n");

				// 전화번호 출력
				printf("number_toekn에 저장된 전화번호: %s\n", number_token);

			}

			/*=============================주소-전화번호-이름=============================*/
			else {

				// 주소 저장하기 + 주소 길이 계산
				// 주소(?) 띄어쓰기(1) 전화번호(13) 띄어쓰기(1) 이름(6) 널문자(1)
				for (int number = 0; number <= number_of_characters - 22; number++) {
					address[m] = line[number];
					m++;
					number_of_address++;
				}


				// 이름 저장하기
				// 이름(3*2=6) 널문자(1)
				for (int number = number_of_characters-6; number <= number_of_characters - 1; number++) {
					name[u] = line[number];
					u++;
				}

				// 전번 저장
				// 전화번호(13) 띄어쓰기(1) 이름(6) 널문자(1)
				char temp_phonenumber[14]; // 임시로 전화번호를 저장해놓을 문자배열, 배열 크기가 14인 이유: 번호 11자리, -도 2개 있고, NULL값 하나 
				int r = 0; // temp_phonenumber에 전화번호를 저장할 때 필요한 인덱스 숫자 

				for (int number = number_of_characters - 20; number <= number_of_characters-8; number++) {
					temp_phonenumber[r] = line[number];
					r++;
				}

				temp_phonenumber[13] = NULL;

				token1 = strtok(temp_phonenumber, TOKEN);
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

				printf("\n");

				//이름 출력
				printf("name에 저장된 이름: ");
				for (int i = 0; i <= 6; i++)
					printf("%c", name[i]);
				printf("\n");

				// 전화번호 출력
				printf("number_toekn에 저장된 전화번호: %s\n", number_token);

				// 주소 출력
				printf("address에 저장된 주소: ");
				for (int i = 0; i <= number_of_characters - 21; i++)
					printf("%c", address[i]);
				printf("\n");

				
				

				printf("주소 글자 수: %d\n", number_of_address);

			}
		}

		/*=============================이름으로 시작=============================*/
		else {

			/*=============================이름-전화번호-주소=============================*/
			if (line[9]=='0'|| line[9] == '1'||line[9] =='2'|| line[9] == '3' || line[9] == '4'|| line[9] == '5' || line[9] == '6' || line[9] == '7' || line[9] == '8' || line[9] == '9') {

				// 이름 저장하기
				// 이름(6) 띄어쓰기(1) 전화번호(11) 널문자(1)
				for (int number = 0; number <= 6; number++) {
					name[u] = line[number];
					u++;
				}

				// 전번 저장
				char temp_phonenumber[14]; // 임시로 전화번호를 저장해놓을 문자배열, 배열 크기가 14인 이유: 번호 11자리, -도 2개 있고, NULL값 하나 
				int r = 0; // temp_phonenumber에 전화번호를 저장할 때 필요한 인덱스 숫자 

				for (int number = 7; number <= 20; number++) {
					temp_phonenumber[r] = line[number];
					r++;
				}
				temp_phonenumber[13] = NULL;

				// 주소 저장하기 + 주소 길이 계산
				for (int number = 21; number <= number_of_characters; number++) {
					address[m] = line[number];
					m++;
					number_of_address++;
				}

				

				token1 = strtok(temp_phonenumber, TOKEN);
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

				printf("\n");

				//이름 출력
				printf("name에 저장된 이름: ");
				for (int i = 0; i <= 6; i++)
					printf("%c", name[i]);
				printf("\n");

				// 주소 출력
				printf("address에 저장된 주소: ");
				for (int i = 0; i <= number_of_characters - 21; i++)
					printf("%c", address[i]);
				printf("\n");

				// 전화번호 출력
				printf("number_toekn에 저장된 전화번호: %s\n", number_token);

				
			}

			/*=============================이름-주소-전화번호=============================*/
			else
			{
				// 이름 저장하기
				// 이름(6) 띄어쓰기(1) 전화번호(11) 널문자(1)
				for (int number = 0; number <= 6; number++) {
					name[u] = line[number];
					u++;
				}

				
				// 주소 저장하기 + 주소 길이 계산
				for (int number = 22; number <= number_of_characters; number++) {
					address[m] = line[number];
					m++;
					number_of_address++;
				}

				// 전번 저장
				char temp_phonenumber[14]; // 임시로 전화번호를 저장해놓을 문자배열, 배열 크기가 14인 이유: 번호 11자리, -도 2개 있고, NULL값 하나 
				int r = 0; // temp_phonenumber에 전화번호를 저장할 때 필요한 인덱스 숫자 

				for (int number = number_of_characters - 13; number < number_of_characters; number++) {
					temp_phonenumber[r] = line[number];
					r++;
				}
				temp_phonenumber[13] = NULL;




				token1 = strtok(temp_phonenumber, TOKEN);
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

				printf("\n");

				//이름 출력
				printf("name에 저장된 이름: ");
				for (int i = 0; i <= 6; i++)
					printf("%c", name[i]);
				printf("\n");

				// 주소 출력
				printf("address에 저장된 주소: ");
				for (int i = 0; i <= number_of_characters - 21; i++)
					printf("%c", address[i]);
				printf("\n");

				// 전화번호 출력
				printf("number_toekn에 저장된 전화번호: %s\n", number_token);

			}


		}
	}
}
