#include <windows.h>
#include <conio.h>

#include "rander.h"
//
//void main()
//{
//	console();
//	my_print();
//
//	while (true)
//	{
//		if (_kbhit()) {
//			char key = _getch();//���񰴼�
//			switch (key)
//			{
//			case char('\x1b'):
//			case char('q') :
//				my_exit();
//				break;
//			}
//		}
//	}
//}

#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;
HANDLE hOut;
//�������
void cle(COORD ClPos)
{
	SetConsoleCursorPosition(hOut, ClPos);
	cout << "            " << endl;
}
//��ӡ����
void prin(COORD PrPos)
{
	SetConsoleCursorPosition(hOut, PrPos);
	cout << "hello world!" << endl;
}
//�ƶ�����
void Move(COORD *MoPos, int key)
{
	switch (key)
	{
	case 72: MoPos->Y--; break;
	case 75: MoPos->X--; break;
	case 77: MoPos->X++; break;
	case 80: MoPos->Y++; break;
	default: break;
	}
}

int main()
{
	cout << "�÷�����ƶ������������" << endl;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);//ȡ���
	COORD CrPos = { 0, 1 };//��������Ϣ
	prin(CrPos);//��ӡ
	//�ȴ�������
	while (1)
	{
		if (kbhit())
		{
			cle(CrPos);//���ԭ�����
			Move(&CrPos, getch());
			prin(CrPos);
		}
		Sleep(30);
	}
	return 0;
}
