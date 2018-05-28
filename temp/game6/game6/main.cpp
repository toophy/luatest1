#include <windows.h>
#include <conio.h>

#include "rander.h"
#include "randerx.h"
//
//void main()
//{
//	console();
//	my_print();
//
//	while (true)
//	{
//		if (_kbhit()) {
//			char key = _getch();//捕获按键
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
//清除函数
void cle(COORD ClPos)
{
	SetConsoleCursorPosition(hOut, ClPos);
	cout << "            " << endl;
}
//打印函数
void prin(COORD PrPos)
{
	SetConsoleCursorPosition(hOut, PrPos);
	cout << "hello world!" << endl;
}
//移动函数
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

using namespace randerx;

int main()
{
	ssr buff_string = "■■■\n"
					  "■■■\n"
					  "■■■\n";
	GetImageMgr()->LoadFromBuffer("man", buff_string.c_str(), buff_string.size(), true);


	cout << "用方向键移动下行输出内容" << endl;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);//取句柄
	COORD CrPos = { 1, 1 };//保存光标信息
	prin(CrPos);//打印
	//等待键按下
	while (1)
	{
		if (_kbhit())
		{
			cle(CrPos);//清除原有输出
			Move(&CrPos, _getch());
			prin(CrPos);
		}
		Sleep(30);
	}
	return 0;
}
