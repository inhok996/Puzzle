#include <iostream>
#include <windows.h> //GetStdHandle(), Sleep(), SetConsoleCursorPosition() �Լ� ���
#include <conio.h> //getch()�� kbhit() �Լ� ���
#include <ctime> //clock() �Լ� ���
#include <iomanip> //setw() �Լ� ���

#define ESC 27 //���� ����
#define LEFT 75 //���� ȭ��ǥ Ű ASCII��
#define RIGHT 77 // ������ ȭ��ǥ Ű ASCII��
#define DOWN 80 //�Ʒ� ȭ��ǥ Ű ASCII��
#define UP 72 //���� ȭ��ǥ Ű ASCII��

#define DIM 4 //4x4 ������� ũ��

static int x,y; //��ĭ�� ��ġ
static int moveNum; //�̵�ȸ��
static clock_t sTime; //���� �ð�

//���� Map �׸��� ���� ��ġ: �ʿ��ϴٸ� ��� ��ġ�� ������ �� ���� 
#define MAP_STARTX 20 
#define MAP_STARTY 2

//�̵� ȸ�� �� �ҿ�ð� ��� ��ġ: �ʿ��ϴٸ� ��� ��ġ�� ������ �� ���� 
#define SCORE_STARTX 45
#define SCORE_STARTY 21

using namespace std;


void gotoXY(int x, int y); //�ܼ� ȭ�鿡�� Ŀ���� Ư�� ��ġ�� �̵�
void init(int (*m)[DIM]); //�ʱ�ȭ �Լ�; �ʿ�ÿ� �Ű������� �߰���
void gameDraw(int (*m)[DIM]); // ���� �ʰ� �ݺ�ȸ��, �ð� ����Լ�; MAP_STARTX, MAP_STARTY ����� �����ؼ� �׻� ���� ��ġ(gotoXY�Լ� ��뿡 ����ʿ�ÿ� �Ű������� �߰���
//                ȭ�� ��� ����
//                Fifteen Puzzle
//                  1  2  9  3
//                  6  8  7  4
//                  10    5  15
//                  13 14 12 11
//
//                  �̵� ȸ��: 10ȸ
//                  �ҿ� �ð�: 15.2��

void puzzleMove(); //���� �̵� �Լ�; �ʿ�ÿ� �Ű����� �߰���
void shuffle(int num);//���� �� �ʱ�ȭ; 50ȸ ������ �̵�, �ʿ�ÿ� ���� �߰� �� �� ����
int getAction();//��� ������ �� ��ġ�� �ְų� ESCŰ�� ���������� ���� 0�� ��ȯ
                   // ����Ű�� ������ ���� �ش� Ű���� ��ȯ(LEFT, RIGHT, DOWN, UP)
                   //�ʿ�ÿ� �Ű����� ���ڸ� �߰��� �� ����

int getDirectKey(){
    if(kbhit()!= 0) //Ű���带 �������� Ȯ����
      return getch() == 224 ? getch():-1;   //Ư�� Ű�� ������ �� ���ۿ� 2Byte�� �߻���, ù��° ���� 224���� �߻��ϰ� �ι�° ���� Ư��Ű�� ���� �ٸ�
                                           //Ư�� Ű�� Ȯ���ϱ� ���� 2���� getch()�Լ��� ȣ���ؾ� ��
} 


int main(void)
{
   int map[DIM][DIM];
   int action = 1;

   init(map);
   shuffle(50);
   gameDraw(map);
   action = getAction();
   // while(action)
   //{
   //   puzzleMove();
   //   gameDraw(map); 
   //  action = getAction();
   //}

   return 0;
}

//�ܼ� ȭ�鿡�� Ŀ���� Ư�� ��ġ�� �̵�
void gotoXY(int x, int y) 
{
 COORD Pos = {x, y};
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// �׿� �Լ����� ������

void init(int (*m)[DIM]) //�ʱ�ȭ �Լ�; �ʿ�ÿ� �Ű������� �߰���
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
void gameDraw(int (*m)[DIM])
{
	gotoXY(MAP_STARTX,MAP_STARTY);
	cout << "fifteen Puzzle";
	int x = MAP_STARTX;
	int y = MAP_STARTY + 1;
	gotoXY(x,y);
	for(int i = 0 ; i < DIM ; i++){
		for(int j = 0 ; j < DIM; j++){
			cout << setw(3) << m[i][j] << " ";
		}
		gotoXY(x,++y);
	}
	//�̵� ȸ��, �ҿ�ð� ���
	y = y + 1;
	gotoXY(x,y);
	cout << "�̵� ȸ��: " << moveNum << "ȸ";
	
}
void puzzleMove() //���� �̵� �Լ�; �ʿ�ÿ� �Ű����� �߰���
{}
void shuffle(int num)//���� �� �ʱ�ȭ; 50ȸ ������ �̵�, �ʿ�ÿ� ���� �߰� �� �� ����
{}
int getAction(){return 1;}//��� ������ �� ��ġ�� �ְų� ESCŰ�� ���������� ���� 0�� ��ȯ
                   // ����Ű�� ������ ���� �ش� Ű���� ��ȯ(LEFT, RIGHT, DOWN, UP)
                   //�ʿ�ÿ� �Ű����� ���ڸ� �߰��� �� ����