#include <stdio.h>
#include <malloc.h>
#define SIZE 100

void print_ary(int* ary, int height, int width);
void print_hint(int** ary, int height, int width);

int main() {
	FILE* drawfp;	//이진수로 되어있는 그림 파일 포인터 
	FILE* convertfp;//이진수그림을 □or■로 바꿔 저장하는 그림 파일 포인터 
	char buff[SIZE]; //fgets할 때 저장하는 버퍼 
	int width = 0;	//그림파일의 가로길이
	int height = 0;	//그림파일의 세로길이 

	drawfp = fopen("c:\\temp\\draw.txt", "r+");
	convertfp = fopen("c:\\temp\\convert.txt", "w+");

	if (drawfp == NULL)
	{
		perror("파일 읽기 개방 에러");
		return;
	}

	// 그림파일의 가로 계산하기 
	while (fgetc(drawfp) != '\n') {
		width++;
	}
	rewind(drawfp); //파일포인터 처음으로 

	// 그림파일의 세로 계산하기 
	while (!feof(drawfp)) {
		fgets(buff, SIZE, drawfp);
		height++;
	}
	rewind(drawfp);

	printf("가로개수: %d, 세로갯수: %d\n", width, height);


	// 숫자를 그림화하기 > 배열에 정보 저장하기 
	int** ary;	//이차원 배열 메모리 할당하기 
	ary = (int**)malloc(sizeof(int*) * width);
	for (int i = 0; i < width; i++)
	{
		ary[i] = (int*)malloc(sizeof(int) * height);
	}

	// 배열에 숫자 집어넣기 
	for (int i = 0; i < height; i++)
	{
		//fgets(buff, SIZE, drawfp);
		for (int j = 0; j < width; j++)
		{
			ary[i][j] = (int)fgetc(drawfp);
			if (ary[i][j] == 10) ary[i][j] = (int)fgetc(drawfp);

		}
	}

	int** new_ary;	//사용자가 그림을 그릴 이차원 배열 메모리 할당하기 
	new_ary = (int**)malloc(sizeof(int*) * width);
	for (int i = 0; i < width; i++)
	{
		new_ary[i] = (int*)malloc(sizeof(int) * height);
	}

	print_hint(ary, height, width); // 배열 출력

	fclose(drawfp);
	fclose(convertfp);

	for (int i = 0; i < width; i++) {
		free(ary[i]);
	}
	free(ary);
}

void print_hint(int** ary, int height, int width)
{
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
	printf("왼쪽 줄 커트 %d\n", left_blank_line);




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
		

		// 그림판 출력 
		for (int b = 0; b < width; b++)
		{
			if (ary[for_height][b] == '1') printf("■");
			else printf("□");
		}
		printf("\n");
		for_height++;
	}
	
}
