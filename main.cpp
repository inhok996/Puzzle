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

#define MOVE_L 0
#define MOVE_R 1
#define MOVE_U 2
#define MOVE_D 3

#define DIM 4 //4x4 ������� ũ��

static int x,y; //��ĭ�� ��ġ
static int moveNum; //�̵�ȸ��
static clock_t sTime; //���� �ð�

//���� Map �׸��� ���� ��ġ: �ʿ��ϴٸ� ��� ��ġ�� ������ �� ���� 
#define MAP_STARTX 20 
#define MAP_STARTY 2

//�̵� ȸ�� �� �ҿ�ð� ��� ��ġ: �ʿ��ϴٸ� ��� ��ġ�� ������ �� ���� 
#define SCORE_STARTX 22
#define SCORE_STARTY 8

//S
using namespace std;


void gotoXY(int x, int y); //�ܼ� ȭ�鿡�� Ŀ���� Ư�� ��ġ�� �̵�
void init(int (*m)[DIM]); //�ʱ�ȭ �Լ�; �ʿ�ÿ� �Ű������� �߰���
void gameDraw(int (*m)[DIM],int& moved); // ���� �ʰ� �ݺ�ȸ��, �ð� ����Լ�; MAP_STARTX, MAP_STARTY ����� �����ؼ� �׻� ���� ��ġ(gotoXY�Լ� ��뿡 ����ʿ�ÿ� �Ű������� �߰���
//                ȭ�� ��� ����
//                Fifteen Puzzle
//                  1  2  9  3
//                  6  8  7  4
//                  10    5  15
//                  13 14 12 11
//
//                  �̵� ȸ��: 10ȸ
//                  �ҿ� �ð�: 15.2��

void puzzleMove(int (*m)[DIM], int action); //���� �̵� �Լ�; �ʿ�ÿ� �Ű����� �߰���
void shuffle(int num, int(*map)[DIM]);//���� �� �ʱ�ȭ; 50ȸ ������ �̵�, �ʿ�ÿ� ���� �߰� �� �� ����

void swap(int di,int (*map)[DIM]);

int end_condition(int(*map)[DIM]);
int getAction(int (*m)[DIM]);//��� ������ �� ��ġ�� �ְų� ESCŰ�� ���������� ���� 0�� ��ȯ
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
   int moved = 1;
   clock_t cTime; //����ð�

   init(map);
   shuffle(10,map);
   gameDraw(map,moved);
   action = getAction(map);
   sTime = clock();
   while(action)
   {
      puzzleMove(map,action);
      gameDraw(map,moved);
	  action = getAction(map);
   }

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
void gameDraw(int (*m)[DIM],int& moved)
{
	if(moved == 1){ //�̵��� �Ͼ������ ���
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
		//�̵� ȸ��, �ҿ�ð� ���
		gotoXY(SCORE_STARTX,SCORE_STARTY);
		cout << "�̵� ȸ��: " << moveNum << "ȸ";
		gotoXY(SCORE_STARTX,SCORE_STARTY + 1);
		cout << "�ҿ� �ð�: ";
		moved = 0;
	}
	gotoXY(SCORE_STARTX + 11,SCORE_STARTY + 1);
	cout << sTime << "��";
	
}
void swap(int di,int (*map)[DIM])
{
   int temp;
   switch(di)
      {
      case MOVE_L:
         if(x>0)
         {
            temp=map[y][x];
            map[y][x]=map[y][x-1];
            map[y][x-1]=temp;
            x--;
         }
         break;
      case MOVE_R:
         if(x<3)
         {
            temp=map[y][x];
            map[y][x]=map[y][x+1];
            map[y][x+1]=temp;
            x++;
         }
         break;
      case MOVE_U:
         if(y>0)
         {
            temp=map[y][x];
            map[y][x]=map[y-1][x];
            map[y-1][x]=temp;
            y--;
         }
         break;
      case MOVE_D:
         if(y<3)
         {
            temp=map[y][x];
            map[y][x]=map[y+1][x];
            map[y+1][x]=temp;
            y++;
         }
         break;
      default: break;
      }
}
void puzzleMove(int(*map)[DIM],int action) //���� �̵� �Լ�; �ʿ�ÿ� �Ű����� �߰���
{
   int key_order=-1;

   if(action==LEFT) key_order=MOVE_L;
   else if(action==RIGHT) key_order=MOVE_R;
   else if(action==UP) key_order=MOVE_U;
   else if(action==DOWN) key_order=MOVE_D;

   swap(key_order, map);
}

void shuffle(int num, int(*map)[DIM])//���� �� �ʱ�ȭ; 50ȸ ������ �̵�, �ʿ�ÿ� ���� �߰� �� �� ����
{
   int direction;
   int moved = 1;
   srand((unsigned int)time(NULL));
   for(int i=0;i<num;i++)
   {
      gameDraw(map,moved);
      Sleep(100);
      direction = rand() % 4;
      swap(direction,map);
   }
}

int end_condition(int(*map)[DIM])
{
   int val=0;
   for(int i=0;i<DIM;i++)
      for(int j=0;j<DIM;j++)
         {
            if(map[i][j]==val) val++;
            else return 0;
         }
   return val;
}

int getAction(int(*map)[DIM])
{
   int key;   
   if(end_condition(map)) return 0;
   key = getDirectKey();
   //printf("key = %d\n",key);
   if((key == LEFT) || (key == RIGHT) || (key == DOWN) || (key == UP) || (key == ESC));
   else key = -1;
   if(key == ESC) return 0;
   return key;
}//��� ������ �� ��ġ�� �ְų� ESCŰ�� ���������� ���� 0�� ��ȯ
                   // ����Ű�� ������ ���� �ش� Ű���� ��ȯ(LEFT, RIGHT, DOWN, UP)
                   //�ʿ�ÿ� �Ű����� ���ڸ� �߰��� �� ����