/********************************************
사용자 입력 문자열에 exit가 입력될 때까지 한줄씩 입력
이름 전화번호 주소를 임의의 순서로 입력받아서 모두 구조체 배열에 저장
address.txt파일이 C:\temp\에 존재하면 텍스트 파일의 내용을 콘솔에 출력
파일이 존재하지 않으면, 콘솔에 입력한 '이름\t주소\t전화번호\t'를 txt파일에 입력해 저장
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
#define NUMBER_OF_BOOK 10 // 구조체 배열 개수 


// 정보를 저장할 구조체
typedef struct Phonebook {
	char bookname[30];
	char bookphone[20];
	char bookaddress[100];
}Phonebook;


void main() {
	char line[100]; // 정보를 입력받을 한 줄
	Phonebook hyeinbook[NUMBER_OF_BOOK] = { NULL };
	int p = 0; // 구조체 배열 인덱스 

	FILE* fp; // 전화번호부 파일 포인터 
	char* path = "c:\\temp\\address.txt"; // 전화번호부가 저장될 위치
	char buffer[100]; // 파일 내용을 출력할 때 필요한 버퍼


	// 파일에서 내용을 읽어올 때 이용하는 토큰들
	char* fname;	// 파일에서 fgets로 받아왔을 때 첫 토큰이 이름일텐데, 이름을 가리키는 문자열 포인터 
	char* fnumber;	// 파일에서 fgets로 받아왔을 때 두 번째 토큰이 전화번호일텐데, 전화번호를 가리키는 문자열 포인터 
	char* faddress;		// 파일에서 fgets로 받아왔을 때 세 번째 토큰이 주소일텐데, 주소를 가리키는 문자열 포인터 

	if (_access(path, 0) == 0)	// address.txt가 존재하면
	{
		fp = fopen("c:\\temp\\address.txt", "r");	// address.txt 파일을 연다

		p = 0;	// 구조체 배열의 인덱스 

		while (!feof(fp)) { // 파일 포인터가 파일의 끝을 가리키기 전까지 아래의 동작을 반복
			fgets(buffer, 100, fp);	// 한 줄씩(최대 99byte) 문자열 버퍼에 저장 

			fname = strtok(buffer, FTOKEN);	// 버퍼에 저장된 문자열을 \t를 기준으로 토큰화한다. 첫 번째 토큰화된 문자열은 이름
			fnumber = strtok(NULL, FTOKEN); // 두 번째 토큰화된 문자열은 전화번호
			faddress = strtok(NULL, FTOKEN); // 세 번째 토큰화된 문자열은 주소 
			// 사실 메모리 덜 차지하게 하나의 char*로 써도 되긴하지만 가독성이 더 나은 것 같아 이렇게 함

			strcpy(hyeinbook[p].bookname, fname);	// 첫 번째 토큰화 했던 문자열을 구조체의 이름멤버에 복사한다. 
			strcpy(hyeinbook[p].bookphone, fnumber);
			strcpy(hyeinbook[p].bookaddress, faddress);
			p++; //// 구조체 배열 인덱스가 +1됨

		}
		fclose(fp); // 파일에서 다 읽어왔으면 파일을 닫음

		// 파일에서 읽어온 정보들을 구조체에 저장했고, 저장해둔 내용을 콘솔에 출력하기 위해 다음과 같이 동작함 
		for (int i = 0; i < p; i++) {
			printf("이름: %s\n", hyeinbook[i].bookname);
			printf("전화번호: %s\n", hyeinbook[i].bookphone);
			printf("주소: %s\n", hyeinbook[i].bookaddress);
			printf("\n");
		}
	}

	else if (_access(path, 0) == -1) { 	// address.txt가 존재하지 않으면 

		printf("이름-주소-전화번호를 순서 상관없이 입력하세요.\n");	
		printf("단, 전화번호는 구분자를 넣어 총 13자리를 입력하세요. \n");
		printf("입력을 멈추고 싶다면 exit를 입력하세요.\n\n");

		while (gets(line)) {	// exit를 입력할 때까지 정보를 무한(NUMBER_OF_BOOK개까지)으로 입력할 수 있다.  

			if (line[0] == 'e' && line[1] == 'x' && line[2] == 'i' && line[3] == 't') {
				if (p < 5) printf("아직 정보 5개 이상을 입력하지 않았습니다. %d개를 더 입력하세요.\n", 5 - p);
				else break; // exit 입력되면 프로그램 종료}
			}

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

				p++; // 몇 개의 구조체 배열이 필요한지 계산 p이 개수, p-1은 인덱스

				printf("\n\n");
			}

		}

		fp = fopen("c:\\temp\\address.txt", "w");

		// 구조체 저장된 정보를 콘솔에 출력
		for (int j = 0; j < p - 1; j++) {
			printf("----------------%d번째 전화번호부----------------\n", j + 1);
			printf("이름: %s\n", hyeinbook[j].bookname);
			printf("전화번호: %s\n", hyeinbook[j].bookphone);
			printf("주소: %s\n", hyeinbook[j].bookaddress);
			printf("\n");

			fprintf(fp, "%s\t", hyeinbook[j].bookname);
			fprintf(fp, "%s\t", hyeinbook[j].bookphone);
			fprintf(fp, "%s\t\n", hyeinbook[j].bookaddress); // p-1전까지는 마지막에 줄 바꿈을 넣음
		}

		printf("----------------%d번째 전화번호부----------------\n", p);
		printf("이름: %s\n", hyeinbook[p - 1].bookname);
		printf("전화번호: %s\n", hyeinbook[p - 1].bookphone);
		printf("주소: %s\n", hyeinbook[p - 1].bookaddress);
		printf("\n");

		fprintf(fp, "%s\t", hyeinbook[p - 1].bookname);
		fprintf(fp, "%s\t", hyeinbook[p - 1].bookphone);
		fprintf(fp, "%s\t", hyeinbook[p - 1].bookaddress); // 마지막 줄이 줄바꿈되지 않게 p-1에서 끝에 줄바꿈을 넣지 않음
	}
}
