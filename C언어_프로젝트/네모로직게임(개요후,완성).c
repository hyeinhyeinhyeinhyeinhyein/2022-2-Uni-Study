#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <windows.h>
#define SIZE 100

void fileopen(FILE** drawfp, char* filename);
void print_newary(int* ary, int width, int height);
int cal_width(FILE** drawfp);
int cal_height(FILE** drawfp);
int** malloc_ary(int** aryname, int width, int height);
void putInfo(FILE** drawfp, int** ary, int width, int height);
void putnew(int** ary, int width, int height);
void print_hint(int** ary, int height, int width);
void change_itoa(int** ary, int width, int for_height);
void print_hint(int** ary, int** new_ary, int height, int width);
void game(int** ary, int** new_ary, int width, int height);
void chage_file(FILE** drawfp, int** ary, int width, int height);
boolean check(int** ary, int** new_ary, int width, int height);
FILE* drawfp;	//이진수로 되어있는 그림 파일 포인터 
int score = 0;

int main() {

	int choose_file;
	int choose_mode;
	int width, height;
	printf("모드를 선택하세요. [1]easy [2]normal [3]hard >> ");
	choose_file = getchar();
	printf("\n");

	switch (choose_file)
	{
	case '1':
		fileopen(&drawfp, "easy.txt"); break;
	case '2':
		fileopen(&drawfp, "normal.txt"); break;
	case '3':
		fileopen(&drawfp, "hard.txt"); break;
	default: printf("[1]~[3] 중에 선택하세요.\n");
	}

	width = cal_width(&drawfp);
	height = cal_height(&drawfp);
	//printf("가로개수: %d, 세로갯수: %d\n", width, height);

	int** ary = NULL; 	ary = malloc_ary(ary, width, height);
	int** new_ary = NULL;	new_ary = malloc_ary(new_ary, width, height);

	putInfo(&drawfp, ary, width, height);
	putnew(new_ary, width, height);

	printf("모드를 선택하세요. [1]일반모드 [2]타이머모드 [3]그림수정 >> ");
	choose_mode = getch();
	printf("\n");
	switch (choose_mode)
	{
	case '1': //일반 모드 
		printf("일반모드를 시작합니다. >>\n");
		print_hint(ary, new_ary, width, height);
		game(ary, new_ary, width, height);
		break;

	case '2': // 타이머 모드
		break;
	case '3': //그림 수정
		chage_file(drawfp, ary, width, height);
		break;

	default: printf("[1]~[3] 중에 선택하세요.\n"); break;
	}

	fclose(drawfp);

}


void fileopen(FILE** drawfp, const char* filename)
{
	*drawfp = fopen(filename, "r+");
	if (*drawfp == NULL)
	{
		perror("파일 읽기 개방 에러");
		return;
	};
}

int cal_width(FILE** drawfp) {
	int width = 0;
	while (fgetc(*drawfp) != '\n')	width++;
	rewind(*drawfp);
	return width;
}


int cal_height(FILE** drawfp) {
	int height = 0;
	char buff[SIZE];
	while (!feof(*drawfp)) {
		fgets(buff, SIZE, *drawfp);
		height++;
	}
	rewind(*drawfp);
	return height;
}

int** malloc_ary(int** aryname, int width, int height) {
	aryname = (int**)malloc(sizeof(int*) * width);
	for (int i = 0; i < width; i++)
	{
		aryname[i] = (int*)malloc(sizeof(int) * height);
	}
	return aryname;
}

void putInfo(FILE** drawfp, int** ary, int width, int height) {
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			ary[i][j] = (int)fgetc(*drawfp);
			if (ary[i][j] == 10) ary[i][j] = (int)fgetc(*drawfp);
		}
	}
}


void putnew(int** ary, int width, int height) {
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			ary[i][j] = 48;
		}
	}
}

void print_hint(int** ary, int** new_ary, int height, int width) {
	// 상단 힌트 계산 변수 
	int hint = 0;
	int hindex = 0;
	int windex = 0;
	int blank_line = 0;
	int count_blank = 0; //count_blank == width라면 그제부터는 다 0이라는 이야기

	// 왼쪽 힌트 계산 변수 
	int left_hint = 0;
	int left_hindex = 0;
	int left_windex = 0;
	int left_count_blank = 0;
	int left_blank_line = 0;

	// 상단 힌트를 저장하는 배열 메모리 할당하기
	int** hint_ary = (int**)malloc(sizeof(int*) * width);
	for (int i = 0; i < width; i++)
	{
		hint_ary[i] = (int*)malloc(sizeof(int) * height);
	}
	// 상단 힌트 저장 배열 초기화 
	for (int j = 0; j < width; j++)
	{
		for (int i = 0; i < height; i++)
		{
			hint_ary[i][j] = NULL;
		}
	}

	// 왼쪽 힌트를 저장하는 배열 메모리 할당하기 
	int** left_hint_ary = (int**)malloc(sizeof(int*) * width);
	for (int i = 0; i < width; i++)
	{
		left_hint_ary[i] = (int*)malloc(sizeof(int) * height);
	}
	// 왼쪽 힌트 저장 배열 초기화 
	for (int j = 0; j < width; j++)
	{
		for (int i = 0; i < height; i++)
		{
			left_hint_ary[i][j] = NULL;
		}
	}

	// 상단 힌트를 배열에 저장하기
	for (int j = 0; j < width; j++)
	{
		for (int i = 0; i < height; i++)
		{
			if (ary[i][j] == '1') {
				hint++;
			}
			else {
				if (hint != 0)
				{
					hint_ary[hindex][windex] = hint;
					hint = 0;
					hindex++;
				}
			}
		}
		hint_ary[hindex][windex] = hint;
		hint = 0;
		windex++;
		hindex = 0;
	}
	// 상단 힌트 줄 커트 	
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (hint_ary[i][j] == NULL)
				count_blank++;
		}
		if (count_blank == width)
		{
			blank_line = i;
			break;
		}
		count_blank = 0;
	}


	// 왼쪽힌트를 배열에 저장하기
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			if (ary[j][i] == '1') {
				left_hint++;
			}
			else {
				if (left_hint != 0)
				{
					left_hint_ary[left_hindex][left_windex] = left_hint;
					left_hint = 0;
					left_windex++;
				}
			}
		}
		left_hint_ary[left_hindex][left_windex] = left_hint;
		left_hint = 0;
		left_hindex++;
		left_windex = 0;
	}


	// 왼쪽 힌트 줄 커트 
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			if (left_hint_ary[i][j] == NULL)
				left_count_blank++;
		}

		if (left_count_blank == height)
		{
			left_blank_line = j;
			break;
		}

		left_count_blank = 0;
	}
	//printf("왼쪽 줄 커트 %d\n", left_blank_line);


	// 상단 힌트 출력
	for (int i = 0; i < blank_line; i++)
	{
		for (int t = 0; t < left_blank_line; t++)
			printf("  ");

		for (int j = 0; j < width; j++)
		{
			if (hint_ary[i][j] != NULL)	printf("%d|", hint_ary[i][j]);
			else {
				int blank_line = 0;

				printf(" |");
			}
		}
		printf("\n");


	}



	int for_height = 0;
	// 왼쪽 힌트 출력

	for (int i = 0; i < width; i++)
	{
		// 숫자 힌트 출력
		for (int j = 0; j < left_blank_line; j++)
		{
			if (left_hint_ary[i][j] != NULL)
			{
				printf("%d|", left_hint_ary[i][j]);
			}

			else
			{
				printf(" |");
			}
		}


		change_itoa(new_ary, width, for_height);
		for_height++;

	}
	printf("현재 점수: %d\n", score);
}

void change_itoa(int** ary, int width, int for_height) {
	for (int b = 0; b < width; b++)
	{
		if (ary[for_height][b] == '1') printf("■");
		else printf("□");
	}
	printf("\n");
}

void game(int** ary, int** new_ary, int width, int height) {
	int mode;
	int x = 0;
	int y = 0;
	printf("\n");
	char buffer[3];
	while (1) {
		printf("모드를 선택하세요. [1]좌표입력 [2]재시작 [3]종료 ");

		mode = getch();
		printf("\n");
		switch (mode)
		{
		case '1': //좌표입력
			printf("좌표를 입력하세요. >> ");
			scanf("%d %d", &x, &y);

			if (new_ary[x][y] == 48) new_ary[x][y] = 49;
			else  new_ary[x][y] = 48;


			if (check(ary, new_ary, width, height) == 1) {
				system("cls");
				print_hint(ary, new_ary, width, height);
				printf("네모로직 풀기에 성공하셨습니다! 축하합니다!");
				exit(0);
			}
			printf("new_ary[x][y]: %d / ary[x][y]: %d", new_ary[x][y], ary[x][y]);
			if ((char)new_ary[x][y] == ary[x][y]) {
				printf("맞았습니다.");
				score++;
			}
			else {
				printf("틀렸습니다.");
				score--;
			}
			system("cls");
			print_hint(ary, new_ary, width, height);
			break;
		case '2':
			system("cls");
			score = 0;
			putnew(new_ary, width, height);
			print_hint(ary, new_ary, width, height);
			break;
		case '3':
			exit(0); break;
		default:
			printf("[1]~[3]중에 선택하세요.\n");
			break;
		}
	}
}
void chage_file(FILE** drawfp, int** ary, int width, int height) {

	int mode=0;
	int x = 0;
	int y = 0;


	while (1) {
		print_hint(ary, ary, height, width);
		printf("[1]좌표입력 [2]파일저장 >> ");
		mode = getch();
		switch (mode) {
		case '1':
			printf("좌표를 입력하세요. >> ");
			scanf("%d %d", &x, &y);
			if (x == 'q' && y == 'q') exit(0);

			if (ary[x][y] == 48) ary[x][y] = 49;
			else ary[x][y] = 48;
			system("cls");
			break;

		case '2':
			rewind(drawfp);
			for (int i=0; i < height-1; i++) {
				for (int j = 0; j < width; j++) {
					fprintf(drawfp,"%c", ary[i][j]);
				}
				fprintf(drawfp,"\n");
			} 	
			for(int j=0;j<width;j++)
				fprintf(drawfp, "%c", ary[height-1][j]);
			exit(0);
			break;

		defalut: break;

		}
	}
}

boolean check(int** ary, int** new_ary, int width, int height) {
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (ary[i][j] != new_ary[i][j]) return 0;
		}
	}
	return 1;
}
