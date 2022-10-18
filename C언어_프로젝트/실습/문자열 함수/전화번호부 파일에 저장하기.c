/********************************************
사용자 입력 문자열에 exit가 입력될 때까지 한줄씩 입력
이름 전화번호 주소를 임의의 순서로 입력받아서 모두 구조체 배열에 저장
저장 후 이름 전화번호 주소를 순차 출력
*************************************************/

// 이름, 전화번호, 주소를 '정보'라 칭함

// 정보를 받을 때, 조건이 있음.
// 주소-이름-번호 사이에는 '한 칸'의 여유만 있음.
// 번호는 010-5650-2802 처럼 구분자가 있어야 하며 총 13자리를 써야함

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TOKEN " .-+_:;*&^%" // 전화번호를 저장할 때 어디에서 토큰화할지 기준이 되는 기호 모음 
#define FTOKEN "\t" // 파일에서 입력받은 줄을 토큰화할 때 필요함



typedef struct Phonebook {
	char bookname[30];
	char bookphone[20];
	char bookaddress[100];
}Phonebook;


void main() {
	char line[100]; // 정보를 입력받을 한 줄
	Phonebook hyeinbook[10] = { NULL };
	int p = 0;

	FILE* fp; // 전화번호부 파일 포인터 
	char* path = "c:\\temp\\address.txt"; // 전화번호부가 저장될 위치
	char buffer[100]; // 파일 내용을 출력할 때 필요한 버퍼

	if (_access(path, 0) == 0)// address.txt가 존재하면
	{
		fp = fopen("c:\\temp\\address.txt", "r");

		fgets(buffer, 100, fp);
		puts(buffer);

		while (!feof(fp)) { // 파일 끝에 도달하면 feof 값은 0, 도달하지 않았으면 0이 아닌 수 반환
			fgets(buffer, 100, fp);
			puts(buffer);
		};

		puts("이제끝!");
		fclose(fp);
	}

	else if (_access(path, 0) == -1) {

		while (gets(line)) {
			if (line[0] == 'e' && line[1] == 'x' && line[2] == 'i' && line[3] == 't') break; // exit 입력되면 프로그램 종료

			else { // 전화번호부에 정보를 나눠 저장하기 

				// line에 실제로 저장된 byte 크기, 위치X(위치는 -1)
				int number_of_characters = 0;

				char number_token[12] = { NULL }; // 전화번호 저장 문자 배열, 11+1(NULL값)
				char address[70] = { NULL }; //주소 저장 문자 배열
				char name[7] = { NULL }; // 이름 저장 문자 배열, 배열 크기가 7인 이유는 (이름3글자*한글이 2byte)+NULL(1) = 7

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

				// 총 바이트 구하기
				for (int number = 0; number < 100; number++) {
					if (line[number] != NULL)
						number_of_characters++;
					else break;
				}

				/*-----------------------------------------------------------------------------------------------------*/
				// 전화번호로 시작하는지 확인(숫자로 시작하는지 확인하면 됨)
				if (line[0] == '0' || line[0] == '1' || line[0] == '2' || line[0] == '3' || line[0] == '4' || line[0] == '5' || line[0] == '6' || line[0] == '7' || line[0] == '8' || line[0] == '9') {

					// 숫자 다음에는 무조건 문자가 나올 것임
					// 그 문자가 주소의 첫 글자인지, 이름의 첫 글자인지 파악해야 함

					/*=============================전화번호-주소-이름=============================*/
					if ((city1 - line) == 14 || (city2 - line) == 14 || (city3 - line) == 14 || (city4 - line) == 14 || (city5 - line) == 14 || (city6 - line) == 14 || (city7 - line) == 14 || (city8 - line) == 14 || (city9 - line) == 14 || (city10 - line) == 14 || (city11 - line) == 14 || (city12 - line) == 14 || (city13 - line) == 14 || (city14 - line) == 14) {

						//이름 저장
						for (int number = number_of_characters - 6; number <= number_of_characters - 1; number++) {
							name[u] = line[number];
							u++;
						}

						// 주소 저장
						for (int number = 14; number <= number_of_characters - 8; number++) { // null문자(1), 이름 (3*2=6), 띄어쓰기(1) 전까지 주소가 저장되어있음
							address[m] = line[number]; // line에서 받은 주소를 주소 배열에 저장하기 
							m++;
							number_of_address++; // 주소 몇 바이트인지
						}
					}
					/*=============================전화번호-이름-주소=============================*/
					else {
						// 이름 저장하기
						for (int number = 14; number <= 19; number++) {
							name[u] = line[number];
							u++;
						}

						// 주소 저장하기
						for (int number = 21; number <= number_of_characters; number++) {
							address[m] = line[number];
							m++;
						}
					}

					// 전번 저장
					token1 = strtok(line, TOKEN); // 010

					for (i = 0; i < strlen(token1); i++) { // 전화번호 배열에 번호 저장
						number_token[i] = token1[i];
					}

					int j = i; //다음에 number_token에 저장할 때 [i]첨자부터 시작해 저장하려고!
					token2 = strtok(NULL, TOKEN);
					int ii = 0;
					for (i = j; i < j + strlen(token2); i++) {
						number_token[i] = token2[ii];
						ii++;
					}

					int k = j + strlen(token2);
					token3 = strtok(NULL, TOKEN);
					ii = 0;
					for (i = k; i < k + strlen(token3); i++) {
						number_token[i] = token3[ii];
						ii++;
					}


				}

				/*=============================문자로 시작=============================*/
				else {	// 주소로 시작하는지 확인
					/*=============================주소로 시작=============================*/
					if (city1 - line == 0 || city2 - line == 0 || city3 - line == 0 || city4 - line == 0 || city5 - line == 0 || city6 - line == 0 || city7 - line == 0 || city8 - line == 0 || city9 - line == 0 || city10 - line == 0 || city11 - line == 14 || city12 - line == 0 || city13 - line == 0 || city14 - line == 0) {

						// 가장 마지막에 써진 문자가 숫자면 주소-이름-전화번호 확정
						/*=============================주소-이름-전화번호=============================*/
						if (line[number_of_characters - 1] == '0' || line[number_of_characters - 1] == '1' || line[number_of_characters - 1] == '2' || line[number_of_characters - 1] == '3' || line[number_of_characters - 1] == '4' || line[number_of_characters - 1] == '5' || line[number_of_characters - 1] == '6' || line[number_of_characters - 1] == '7' || line[number_of_characters - 1] == '8' || line[number_of_characters - 1] == '9') {

							// 주소 저장하기 + 주소 크기(바이트) 계산
							//띄어쓰기(1) 이름(6) 띄어쓰기(1) 전화번호(11) 널문자(1) 
							for (int number = 0; number <= number_of_characters - 21; number++) {
								address[m] = line[number];
								m++;
								number_of_address++;
							}

							// 이름 저장하기
							// 이름(6) 띄어쓰기(1) 전화번호(11) 널문자(1)
							for (int number = number_of_characters - 20; number <= number_of_characters - 15; number++) {
								name[u] = line[number];
								u++;
							}

							// 전화번호 저장
							char temp_phonenumber[14]; // 임시로 전화번호를 저장해놓을 문자배열, 배열 크기가 14인 이유: 번호 11자리, -도 2개 있고, NULL값 하나 
							int r = 0; // temp_phonenumber에 전화번호를 저장할 때 필요한 인덱스 숫자 

							for (int number = number_of_characters - 13; number < number_of_characters; number++) {
								temp_phonenumber[r] = line[number];
								r++;
							}

							temp_phonenumber[13] = NULL;

							token1 = strtok(temp_phonenumber, TOKEN);
							for (i = 0; i < strlen(token1); i++) {
								number_token[i] = token1[i];
							}

							int j = i; //다음에 number_token에 저장할 때 [i]첨자부터 시작해 저장하려고!
							token2 = strtok(NULL, TOKEN);
							int ii = 0;
							for (i = j; i < j + strlen(token2); i++) {
								number_token[i] = token2[ii];
								ii++;
							}

							int k = j + strlen(token2);
							token3 = strtok(NULL, TOKEN);
							ii = 0;
							for (i = k; i < k + strlen(token3); i++) {
								number_token[i] = token3[ii];
								ii++;
							}
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
							for (int number = number_of_characters - 6; number <= number_of_characters - 1; number++) {
								name[u] = line[number];
								u++;
							}

							// 전번 저장
							// 전화번호(13) 띄어쓰기(1) 이름(6) 널문자(1)
							char temp_phonenumber[14]; // 임시로 전화번호를 저장해놓을 문자배열, 배열 크기가 14인 이유: 번호 11자리, -도 2개 있고, NULL값 하나 
							int r = 0; // temp_phonenumber에 전화번호를 저장할 때 필요한 인덱스 숫자 

							for (int number = number_of_characters - 20; number <= number_of_characters - 8; number++) {
								temp_phonenumber[r] = line[number];
								r++;
							}

							temp_phonenumber[13] = NULL;

							token1 = strtok(temp_phonenumber, TOKEN);

							for (i = 0; i < strlen(token1); i++) {
								number_token[i] = token1[i];
							}
							int j = i; //다음에 number_token에 저장할 때 [i]첨자부터 시작해 저장하려고!


							token2 = strtok(NULL, TOKEN);

							int ii = 0;
							for (i = j; i < j + strlen(token2); i++) {
								number_token[i] = token2[ii];
								ii++;
							}
							int k = j + strlen(token2);

							ii = 0;
							token3 = strtok(NULL, TOKEN);

							for (i = k; i < k + strlen(token3); i++) {
								number_token[i] = token3[ii];
								ii++;
							}
						}
					}

					/*=============================이름으로 시작=============================*/
					else {

						/*=============================이름-전화번호-주소=============================*/
						if (line[9] == '0' || line[9] == '1' || line[9] == '2' || line[9] == '3' || line[9] == '4' || line[9] == '5' || line[9] == '6' || line[9] == '7' || line[9] == '8' || line[9] == '9') {

							// 이름 저장하기
							// 이름(6) 띄어쓰기(1) 전화번호(11) 널문자(1)
							for (int number = 0; number <= 5; number++) {
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

							for (i = 0; i < strlen(token1); i++) {
								number_token[i] = token1[i];
							}
							int j = i; //다음에 number_token에 저장할 때 [i]첨자부터 시작해 저장하려고!

							token2 = strtok(NULL, TOKEN);

							int ii = 0;
							for (i = j; i < j + strlen(token2); i++) {
								number_token[i] = token2[ii];
								ii++;
							}
							int k = j + strlen(token2);

							ii = 0;
							token3 = strtok(NULL, TOKEN);

							for (i = k; i < k + strlen(token3); i++) {
								number_token[i] = token3[ii];
								ii++;
							}
						}
						/*=============================이름-주소-전화번호=============================*/
						else
						{
							// 이름 저장하기
							// 이름(6) 띄어쓰기(1) 전화번호(11) 널문자(1)
							for (int number = 0; number <= 5; number++) {
								name[u] = line[number];
								u++;
							}

							// 주소 저장하기 + 주소 길이 계산
							for (int number = 7; number <= number_of_characters - 14; number++) {
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

							for (i = 0; i < strlen(token1); i++) {
								number_token[i] = token1[i];
							}
							int j = i; //다음에 number_token에 저장할 때 [i]첨자부터 시작해 저장하려고!

							token2 = strtok(NULL, TOKEN);

							int ii = 0;
							for (i = j; i < j + strlen(token2); i++) {
								number_token[i] = token2[ii];
								ii++;
							}
							int k = j + strlen(token2);

							ii = 0;
							token3 = strtok(NULL, TOKEN);
							for (i = k; i < k + strlen(token3); i++) {
								number_token[i] = token3[ii];
								ii++;
							}
						}
					}
				}


				// 구조체에 내용 저장 
				strcpy(hyeinbook[p].bookname, name);
				strcpy(hyeinbook[p].bookphone, number_token);
				strcpy(hyeinbook[p].bookaddress, address);

				p++;

				printf("\n\n");
			}

		}
		fp = fopen("c:\\temp\\address.txt", "w");

		for (int j = 0; j < 10; j++) {
			printf("----------------%d번째 전화번호부----------------\n", j + 1);
			printf("이름: %s\n", hyeinbook[j].bookname);
			printf("전화번호: %s\n", hyeinbook[j].bookphone);
			printf("주소: %s\n", hyeinbook[j].bookaddress);
			printf("\n");

			fprintf(fp, "%s\t", hyeinbook[j].bookname);
			fprintf(fp, "%s\t", hyeinbook[j].bookphone);
			fprintf(fp, "%s\n", hyeinbook[j].bookaddress);

		}

	}

		
}
