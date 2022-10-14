#include <iostream>
#include <cstring>
#include <stdlib.h> // rand함수 사용 
#include <time.h> // rand의 seed 기준을 현재 시간으로 잡아 난수를 매 실행마다 다르게 설정 
using namespace std;

class Game {
public:
	Game(); // 생성자함수

	string input_answer; // 사용자가 입력한 숫자를 저장
	int user_answer[3]; // string으로 입력받은 숫자를 나눠서 배열에 저장 

private:
	int score = 1; // 사용자의 게임 횟수(사용자가 숫자를 몇 번 입력했는지)
	int strike = 0; // 사용자의 스트라이크 수
	int ball = 0; // 사용자의  볼 

	// 사용자가 맞춰야할 난수 생성
	int answer1 = rand() % 10; // 첫 번째 난수 문자
	int answer2 = rand() % 10; // 두 번째 난수 문자 
	int answer3 = rand() % 10; // 세 번째 난수 문자 

	int answer[3] = { answer1,answer2,answer3 }; // 난수로 발생된 숫자(배열)

public:
	void playgame(); // 사용자가 야구 게임을 하는 메서드
};



Game::Game() {
	cout << "게임시작\n\n"; // 딱히 값을 초기화 시킬 게 없어서 게임 시작을 알리는 문구를 출력하며 시작
}


void Game::playgame() {

	// 게임을 시작하기 앞서 난수가 서로 다른지 확인
	if (answer2 == answer1) {	// answer2가 answer1과 같으면 새롭게 난수를 받음
		answer2 = rand() % 10; 
		while (answer2 == answer1) // 새롭게 난수를 생성했음에도 두 값이 같으면 두 값이 달라질 때까지 난수를 받음 
			answer2 = rand() % 10;
	}

	if (answer3 == answer1 || answer3 == answer2) { 
		answer3 = rand() % 10;	// answer3이 answer1이나 answer2와 같으면 새롭게 난수를 받음
		while ((answer3 == answer1) && (answer3 == answer2))  // 그조차도 같으면 두 값이 달라질 때까지 난수를 받음
			answer3 = rand() % 10;
	}


	// 사용자가 정답을 맞출 때까지 무한 반복(숫자 입력받고 스트라이크볼 알려주기를 반복)
	while (1) {

		if (input_answer[0] == 'e' && input_answer[1] == 'x' && input_answer[2] == 'i' && input_answer[3] == 't') {
			cout << "프로그램이 종료되었습니다.";
			break;
		}

		cout << "3자리 숫자를 입력하세요: ";
		cin >> input_answer;
		user_answer[0] = input_answer[0] - '0';
		user_answer[1] = input_answer[1] - '0';
		user_answer[2] = input_answer[2] - '0';

		strike = 0; // 스트라이크 수
		ball = 0;   // 볼 수

		// 스트라이크와 볼 수를 계산
		
		for (int i = 0; i <= 2; i++) {	// 정답의 i 번째 숫자와 사용자에게 입력받은 3개의 숫자를 비교
			for (int j = 0; j <= 2; j++) {
				if (answer[i] == user_answer[j]) {	// 만약 정답의 i번째 숫자와 사용자에게 입력받은 3개의 숫자 중에 같은 숫자가 있을 때
					if (i == j) {	// 인덱스가 같으면 숫자와 자리를 모두 맞췄다는 이야기이므로 
						strike++; // strike 값을 +1
					}
					else ball++; // 인덱스가 같지 않으면 숫자만 맞췄다는 이야기이므로  ball 값을 +1
				}
			}
		}

		// 숫자를 모두 맞췄을 때는 3스트라이크라는 것을 이용해 프로그램 종료 
		if (strike == 3) { 
			cout << "============================\n";
			cout << score << "회 만에 정답을 맞췄습니다!\n";
			cout << "정답: " << answer[0] << answer[1] << answer[2] << "\n";
			cout << "=============================\n";
			exit(0);
		}

		cout << "============================\n";
		cout << user_answer[0] << user_answer[1] << user_answer[2] << ": " << strike << "스트라이크 " << ball << "볼";
		cout << "\n============================\n" << "\n";

		score++; // 사용자가 입력한 수에 대해 결과까지 나왔으니 실행횟수 증가
	};
}

int main()
{
	srand((unsigned int)time(NULL));
	Game User; //User라는 객체를 생성 
	User.playgame();  //User가 게임을 할 수 있게 실행하는 메서드 
}
