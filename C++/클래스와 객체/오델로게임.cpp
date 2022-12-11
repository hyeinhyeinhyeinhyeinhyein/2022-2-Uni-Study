#include <iostream>
#include <windows.h>

using namespace std;

class Game {
	char board[8][8] = { {NULL},{NULL},{NULL},{NULL,NULL,NULL,'O','X',NULL,NULL,NULL},{NULL,NULL,NULL,'X','O',NULL,NULL,NULL},{NULL},{NULL},{NULL}};
	char copyboard[8][8];
	int me = 2;
	int you = 2;

public:
	void printBoard();
	void myturn();
	void yourturn();
};


void Game::printBoard() {
	



	cout << "┌──────┬──────┬──────┬──────┬──────┬──────┬──────┬──────┐" << endl;

	for (int i = 0; i < 8; i++) {
		cout << "│      │      │      │      │      │      │      │      │" << endl;
		for (int j = 0; j < 8; j++) {
			if(board[i][j]==NULL)
				cout << "│   " << "   ";
			else
				cout << "│ " << board[i][j] << "    ";
		}
		cout << endl;
		cout << "│      │      │      │      │      │      │      │      │" << endl;
		cout << "├──────┼──────┼──────┼──────┼──────┼──────┼──────┼──────┤" << endl;
	}
	cout << "└──────┴──────┴──────┴──────┴──────┴──────┴──────┴──────┘" << endl;
	
}

void Game::myturn() {
	// 판 복사본 만들기 
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			copyboard[i][j] = board[i][j];
		}
	}
	int xtmp;
	int ytmp;
	int numberO = 0;
	int weight;
	int flipinfo[8][5]; //x좌표 y좌표 어디x 어디y부터 몇개뒤집 
	for (int i = 0; i < 8; i++) {
		ytmp = i;
		for (int j = 0; j < 8; j++) {
			xtmp = j;
			//cout << "board[" << i << "][" << j << "]" << endl;
			if (board[ytmp][xtmp] == 'X') {
				//왼쪽
				if (board[ytmp][--xtmp] == 'O') {
					numberO++;
					while (board[i][--xtmp] == 'O')
					{
						if (xtmp == 0) break;
						numberO++;
					}
					if (board[ytmp][xtmp] == NULL) {
						flipinfo[0][0] = ytmp;
						flipinfo[0][1] = xtmp;
						flipinfo[0][2] = i;
						flipinfo[0][3] = j - 1;
						flipinfo[0][4] = numberO;
						board[ytmp][xtmp] = numberO + 48;
					}
				}
				numberO = 0;
				ytmp = i;
				xtmp = j;
				//오른쪽
				if (board[ytmp][++xtmp] == 'O') {
					numberO++;
					while (board[ytmp][++xtmp] == 'O')
					{

						if (xtmp == 7) break;
						numberO++;
					}
					if (board[ytmp][xtmp] == NULL) {
						flipinfo[1][0] = ytmp;
						flipinfo[1][1] = xtmp;
						flipinfo[1][2] = i;
						flipinfo[1][3] = j+1;
						flipinfo[1][4] = numberO;
						board[ytmp][xtmp] = numberO + 48;
					}
				}
				numberO = 0;
				ytmp = i;
				xtmp = j;
				
				//위쪽
				if (board[--ytmp][xtmp] == 'O') {
					numberO++;
					while (board[--ytmp][xtmp] == 'O')
					{
						if (ytmp == 0) break;
						numberO++;
					}
					if (board[ytmp][xtmp] == NULL) {
						flipinfo[2][0] = ytmp;
						flipinfo[2][1] = xtmp;
						flipinfo[2][2] = i-1;
						flipinfo[2][3] = j;
						flipinfo[2][4] = numberO;
						board[ytmp][xtmp] = numberO + 48;
					}
				}
				numberO = 0;
				ytmp = i;
				xtmp = j;
				
				//아래
				if (board[++ytmp][xtmp] == 'O') {
					numberO++;
					while (board[++ytmp][xtmp] == 'O')
					{
						if (ytmp == 7) break;
						numberO++;
					}
					if (board[ytmp][xtmp] == NULL) {
						flipinfo[3][0] = ytmp;
						flipinfo[3][1] = xtmp;
						flipinfo[3][2] = i+1;
						flipinfo[3][3] = j;
						flipinfo[3][4] = numberO;
						board[ytmp][xtmp] = numberO + 48;
					}
				}
				numberO = 0;
				ytmp = i;
				xtmp = j;
				
				//왼쪽대각선아래 
				if (board[++ytmp][--xtmp] == 'O') {
					numberO++;
					while (board[++ytmp][--xtmp] == 'O')
					{
						if (ytmp == 7 || xtmp == 0) break;
						numberO++;
					}
					if (board[ytmp][xtmp] == NULL) {
						flipinfo[4][0] = ytmp;
						flipinfo[4][1] = xtmp;
						flipinfo[4][2] = i + 1;
						flipinfo[4][3] = j-1;
						flipinfo[4][4] = numberO;
						board[ytmp][xtmp] = numberO + 48;
					}
				}
				numberO = 0;
				ytmp = i;
				xtmp = j;
			
				//오른쪽대각선아래 
				if (board[++ytmp][++xtmp] == 'O') {
					numberO++;
					while (board[++ytmp][++xtmp] == 'O')
					{
						if (ytmp == 7 || xtmp == 7) break;
						numberO++;
					}
					if (board[ytmp][xtmp] == NULL) {
						flipinfo[5][0] = ytmp;
						flipinfo[5][1] = xtmp;
						flipinfo[5][2] = i + 1;
						flipinfo[5][3] = j+1;
						flipinfo[5][4] = numberO;
						board[ytmp][xtmp] = numberO + 48;
					}
				}
				numberO = 0;
				ytmp = i;
				xtmp = j;
				
				//왼쪽대각선위
				if (board[--ytmp][--xtmp] == 'O') {
					numberO++;
					while (board[--ytmp][--xtmp] == 'O')
					{
						if (ytmp == 0 || xtmp == 0) break;
						numberO++;
					}
					if (board[ytmp][xtmp] == NULL) {
						flipinfo[6][0] = ytmp;
						flipinfo[6][1] = xtmp;
						flipinfo[6][2] = i - 1;
						flipinfo[6][3] = j-1;
						flipinfo[6][4] = numberO;
						board[ytmp][xtmp] = numberO + 48;
					}
				}
				numberO = 0;
				ytmp = i;
				xtmp = j;
				//오른쪽대각선위
				if (board[--ytmp][++xtmp] == 'O') {
					numberO++;
					while (board[--ytmp][++xtmp] == 'O')
					{
						if (ytmp == 0 || j == 7) break;
						numberO++;
					}
					if (board[ytmp][j] == NULL) {
						flipinfo[7][0] = ytmp;
						flipinfo[7][1] = xtmp;
						flipinfo[7][2] = i - 1;
						flipinfo[7][3] = j+1;
						flipinfo[7][4] = numberO;
						board[ytmp][j] = numberO + 48;
					}
				}
				
				else break;

			}
			numberO = 0;
		
		}


	}
	system("cls");
	printBoard();
	// 판 복사본 만들기 
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j]= copyboard[i][j];
		}
	}
	int xpos; //돌의 x좌표
	int ypos; //돌의 x좌표
	cout << "x좌표를 입력하세요.>> ";
	cin >> ypos;
	cout << "y좌표를 입력하세요.>> ";
	cin >> xpos;

	board[xpos][ypos] = 'X';

	for (int findx = 0; findx < 8; findx++) {
		//cout << "findx:" << findx;
		if (flipinfo[findx][0] == xpos && flipinfo[findx][1] == ypos) {
			cout << "findx:" << findx;
			if (findx == 0) {//왼쪽
				for (int i = 0; i < flipinfo[findx][4]; i++) {
					board[flipinfo[findx][2]][flipinfo[findx][3] - i] = 'X';
				}
			}
			if (findx == 1) {//오른쪽
				for (int i = 0; i < flipinfo[findx][4]; i++) {
					board[flipinfo[findx][2]][flipinfo[findx][3] + i] = 'X';
				}
			}
			if (findx == 2) {//위쪽
				for (int i = 0; i < flipinfo[findx][4]; i++) {
					board[flipinfo[findx][2]-i][flipinfo[findx][3]] = 'X';
				}
			}
			if (findx == 3) {//아래쪽
				for (int i = 0; i < flipinfo[findx][4]; i++) {
					board[flipinfo[findx][2]+i][flipinfo[findx][3]] = 'X';
				}
			}
			if (findx == 4) {////왼쪽대각선아래 
				for (int i = 0; i < flipinfo[findx][4]; i++) {
					board[flipinfo[findx][2]+i][flipinfo[findx][3] -i] = 'X';
				}
			}
			if (findx == 5) {//오른쪽대각선아래 
				for (int i = 0; i < flipinfo[findx][4]; i++) {
					board[flipinfo[findx][2] + i][flipinfo[findx][3] + i] = 'X';
				}
			}
			if (findx == 6) {//왼쪽대각선위
				for (int i = 0; i < flipinfo[findx][4]; i++) {
					board[flipinfo[findx][2] - i][flipinfo[findx][3] - i] = 'X';
				}
			}
			if (findx == 7) {//오른쪽대각선위
				for (int i = 0; i < flipinfo[findx][4]; i++) {
					board[flipinfo[findx][2] - i][flipinfo[findx][3] + i] = 'X';
				}
			}






		}
	}

	system("cls");
	printBoard();
}

void Game::yourturn() {
	// 판 복사본 만들기 
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			copyboard[i][j] = board[i][j];
		}
	}
	int xtmp;
	int ytmp;
	int numberO = 0;
	int weight;
	int startxpos;
	int flipinfo[8][5]; //x좌표 y좌표 어디x 어디y부터 몇개뒤집 
	for (int i = 0; i < 8; i++) {
		ytmp = i;
		for (int j = 0; j < 8; j++) {
			xtmp = j;
			//cout << "board[" << i << "][" << j << "]" << endl;
			if (board[ytmp][xtmp] == 'O') {
				//왼쪽
				if (board[ytmp][--xtmp] == 'X') {
					numberO++;
					while (board[i][--xtmp] == 'X')
					{
						if (xtmp == 0) break;
						numberO++;
					}
					if (board[ytmp][xtmp] == NULL) {
						flipinfo[0][0] = ytmp;
						flipinfo[0][1] = xtmp;
						flipinfo[0][2] = i;
						flipinfo[0][3] = j-1;
						flipinfo[0][4] = numberO;
						board[ytmp][xtmp] = numberO + 48;
					}
				}
				numberO = 0;
				ytmp = i;
				xtmp = j;
				//오른쪽
				if (board[ytmp][++xtmp] == 'X') {
					numberO++;
					while (board[ytmp][++xtmp] == 'X')
					{

						if (xtmp == 7) break;
						numberO++;
					}
					if (board[ytmp][xtmp] == NULL) {

						board[ytmp][xtmp] = numberO + 48;
					}
				}
				numberO = 0;
				ytmp = i;
				xtmp = j;

				//아래쪽
				if (board[--ytmp][xtmp] == 'X') {
					numberO++;
					while (board[--ytmp][xtmp] == 'X')
					{
						if (ytmp == 0) break;
						numberO++;
					}
					if (board[ytmp][xtmp] == NULL) {
						board[ytmp][xtmp] = numberO + 48;
					}
				}
				numberO = 0;
				ytmp = i;
				xtmp = j;

				//위쪽
				if (board[++ytmp][xtmp] == 'X') {
					numberO++;
					while (board[++ytmp][xtmp] == 'X')
					{
						if (ytmp == 7) break;
						numberO++;
					}
					if (board[ytmp][xtmp] == NULL) {
						board[ytmp][xtmp] = numberO + 48;
					}
				}
				numberO = 0;
				ytmp = i;
				xtmp = j;

				//왼쪽대각선아래 
				if (board[++ytmp][--xtmp] == 'X') {
					numberO++;
					while (board[++ytmp][--xtmp] == 'X')
					{
						if (ytmp == 7 || xtmp == 0) break;
						numberO++;
					}
					if (board[ytmp][xtmp] == NULL) {
						board[ytmp][xtmp] = numberO + 48;
					}
				}
				numberO = 0;
				ytmp = i;
				xtmp = j;

				//오른쪽대각선아래 
				if (board[++ytmp][++xtmp] == 'X') {
					numberO++;
					while (board[++ytmp][++xtmp] == 'X')
					{
						if (ytmp == 7 || xtmp == 7) break;
						numberO++;
					}
					if (board[ytmp][xtmp] == NULL) {
						board[ytmp][xtmp] = numberO + 48;
					}
				}
				numberO = 0;
				ytmp = i;
				xtmp = j;

				//왼쪽대각선위
				if (board[--ytmp][--xtmp] == 'X') {
					numberO++;
					while (board[--ytmp][--xtmp] == 'X')
					{
						if (ytmp == 0 || xtmp == 0) break;
						numberO++;
					}
					if (board[ytmp][xtmp] == NULL) {
						board[ytmp][xtmp] = numberO + 48;
					}
				}
				numberO = 0;
				ytmp = i;
				xtmp = j;
				//오른쪽대각선위
				if (board[--ytmp][++xtmp] == 'X') {
					numberO++;
					while (board[--ytmp][++xtmp] == 'X')
					{
						if (ytmp == 0 || j == 7) break;
						numberO++;
					}
					if (board[ytmp][j] == NULL) {
						board[ytmp][j] = numberO + 48;
					}
				}

				else break;

			}
			numberO = 0;

		}


	}
	printBoard();
	// 판 복사본 만들기 
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			board[i][j] = copyboard[i][j];
		}
	}
	int xpos; //돌의 x좌표
	int ypos; //돌의 x좌표
	cout << "x좌표를 입력하세요.>> ";
	cin >> xpos;
	cout << "y좌표를 입력하세요.>> ";
	cin >> ypos;

	board[xpos][ypos] = 'X';

}


int main() {
	Game play;
	play.printBoard();
	play.myturn();
	//play.printBoard();
	//play.yourturn();


}
