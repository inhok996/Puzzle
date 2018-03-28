#include <iostream>
#include <windows.h> //GetStdHandle(), Sleep(), SetConsoleCursorPosition() 함수 사용
#include <conio.h> //getch()와 kbhit() 함수 사용
#include <ctime> //clock() 함수 사용
#include <iomanip> //setw() 함수 사용

#define ESC 27 //게임 종료
#define LEFT 75 //왼쪽 화살표 키 ASCII값
#define RIGHT 77 // 오른쪽 화살표 키 ASCII값
#define DOWN 80 //아래 화살표 키 ASCII값
#define UP 72 //위쪽 화살표 키 ASCII값

#define DIM 4 //4x4 퍼즐맵의 크기

static int x,y; //빈칸의 위치
static int moveNum; //이동회수
static clock_t sTime; //시작 시간

//게임 Map 그리기 시작 위치: 필요하다면 출력 위치를 조정할 수 있음 
#define MAP_STARTX 20 
#define MAP_STARTY 2

//이동 회수 및 소요시간 출력 위치: 필요하다면 출력 위치를 조정할 수 있음 
#define SCORE_STARTX 22
#define SCORE_STARTY 8

//S
using namespace std;


void gotoXY(int x, int y); //콘솔 화면에서 커서를 특정 위치로 이동
void init(int (*m)[DIM]); //초기화 함수; 필요시에 매개변수를 추가함
void gameDraw(int (*m)[DIM],int moved); // 게임 맵과 반복회수, 시간 출력함수; MAP_STARTX, MAP_STARTY 상수를 참조해서 항상 고정 위치(gotoXY함수 사용에 출력필요시에 매개변수를 추가함
//                화면 출력 예시
//                Fifteen Puzzle
//                  1  2  9  3
//                  6  8  7  4
//                  10    5  15
//                  13 14 12 11
//
//                  이동 회수: 10회
//                  소요 시간: 15.2초

void puzzleMove(); //퍼즐 이동 함수; 필요시에 매개변수 추가함
void shuffle(int num);//퍼즐 맵 초기화; 50회 무작위 이동, 필요시에 인자 추가 할 수 있음
int getAction(int (*m)[DIM]);//모든 퍼즐이 제 위치에 있거나 ESC키가 눌러졌으면 정수 0을 반환
                   // 방향키를 눌렀을 때는 해당 키값을 반환(LEFT, RIGHT, DOWN, UP)
                   //필요시에 매개변수 인자를 추가할 수 있음

int getDirectKey(){
    if(kbhit()!= 0) //키보드를 눌렀는지 확인함
      return getch() == 224 ? getch():-1;   //특수 키를 눌렀을 때 버퍼에 2Byte가 발생함, 첫번째 값은 224값을 발생하고 두번째 값은 특수키에 따라 다름
                                           //특수 키를 확인하기 위해 2번의 getch()함수를 호출해야 함
} 


int main(void)
{
   int map[DIM][DIM];
   int action = 1;

   init(map);
   shuffle(50);
   gameDraw(map,1);
   map[0][1] = 3;
   action = getAction(map);
   while(action)
   {
      puzzleMove();
      gameDraw(map,0);
	  action = getAction(map);
   }

   return 0;
}

//콘솔 화면에서 커서를 특정 위치로 이동
void gotoXY(int x, int y) 
{
 COORD Pos = {x, y};
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 그외 함수들을 정의함

void init(int (*m)[DIM]) //초기화 함수; 필요시에 매개변수를 추가함
{
	int val = 0;
	for(int i = 0 ; i< DIM ; i++){
		for(int j = 0 ; j < DIM ; j++){
			m[i][j] = val++;
		}
	}
	x = 0;
	y = 0;
	moveNum = 0;
}
void gameDraw(int (*m)[DIM],int moved)
{
	if(moved == 1){ //이동이 일어났을때만 출력
	gotoXY(MAP_STARTX,MAP_STARTY);
	cout << "fifteen Puzzle";
	int x = MAP_STARTX;
	int y = MAP_STARTY + 1;
		gotoXY(x,y);
		for(int i = 0 ; i < DIM ; i++){
			for(int j = 0 ; j < DIM; j++){
				if(m[i][j] == 0) cout << "  * " ;
				else cout << setw(3) << m[i][j] << " ";
			}
			gotoXY(x,++y);
		}
		//이동 회수, 소요시간 출력
		gotoXY(SCORE_STARTX,SCORE_STARTY);
		cout << "이동 회수: " << moveNum << "회";
		gotoXY(SCORE_STARTX,SCORE_STARTY + 1);
		cout << "소요 시간: ";
	}
	gotoXY(SCORE_STARTX + 11,SCORE_STARTY + 1);
	cout << sTime << "초";
	
}
void puzzleMove() //퍼즐 이동 함수; 필요시에 매개변수 추가함
{}
void shuffle(int num)//퍼즐 맵 초기화; 50회 무작위 이동, 필요시에 인자 추가 할 수 있음
{}
int getAction(int (*m)[DIM]){
	//맞는지 체크
	int flag = 1;
	int cnt = 0;
	for(int i = 0 ; i < DIM ; i++){
		for(int j = 0 ; j < DIM ; j++){
			if(m[i][j] != cnt++){
				flag = 0;
				break;
			}
		}
	}
	if(flag == 1) return 0; // 다 맞았을때 return 0
	int cmd;
	int ret_val = 0;
	
	cmd = getDirectKey();
	//printf("\ncmd = %d\n",cmd);
	switch(cmd){
	case -1: ret_val = 0; break;
	case LEFT: ret_val = LEFT; break;
	case RIGHT: ret_val = RIGHT; break;
	case DOWN: ret_val = DOWN; break;
	case UP: ret_val = UP; break;
	default : ret_val = -1; break; //아무입력도 없을시 cmd = 0
	}
	//printf("return val = %d\n",ret_val);
	return ret_val;
}