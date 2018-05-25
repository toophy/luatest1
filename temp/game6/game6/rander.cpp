
#include <windows.h>
#include <stdio.h>

#include "rander.h"

//设置窗口位置和大小，为了让程序运行得更好看
void console()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// 获取标准输出设备句柄
	CONSOLE_SCREEN_BUFFER_INFO bInfo; // 窗口缓冲区信息
	GetConsoleScreenBufferInfo(hOut, &bInfo);// 获取窗口缓冲区信息
	SetConsoleTitle(L"俄罗斯方块"); // 设置窗口的标题
	COORD size = { 128, 64 };//不能小于默认大小（80，25）
	SetConsoleScreenBufferSize(hOut, size); // 重新设置缓冲区大小*/
	SMALL_RECT rc = { 0, 0, 128 - 1, 64 - 1 }; //不能大于缓冲区大小
	SetConsoleWindowInfo(hOut, true, &rc);// 重置窗口大小
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 }; //第一个参数光标百分比大小。第二个参数是否可见。
	SetConsoleCursorInfo(hOut, &cursor_info);//设置控制台光标
}

//设置光标输出的位置函数。坐标不能为负数,X表示横坐标，Y表示纵坐标。
void gotoxy(int x, int y)
{
	if (x<0 || y<0) {
		return;
	}

	HANDLE app;
	COORD  pos;
	pos.X = x;
	pos.Y = y;
	app = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(app, pos);
}

//退出前保存最高分
void my_exit()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
	gotoxy(12, 12); printf("================================");
	gotoxy(12, 13); printf("||  游戏已退出 按任意键关闭！ ||");
	gotoxy(12, 14); printf("================================");
	gotoxy(0, 30);
	Sleep(1000);
	exit(0);
}

//右面板显示
void my_print()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);//黑底亮蓝字。
	for (int i = 1; i < 30; i++)
		printf("■\t\t\t\t■ |                           |\n");
	printf("■■■■■■■■■■■■■■■■■ |---------------------------|\n");//框架
	gotoxy(36, 0);
	printf("---------------------------");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);//黑底亮黄字。
	gotoxy(40, 2);
	printf("关  卡： %d", 1);
	gotoxy(40, 3);
	printf("分  数： %d", 1);
	gotoxy(40, 4);
	printf("最高分： %d", 1);
	gotoxy(36, 6);
	printf("下一个方块：");
	gotoxy(36, 14);
	printf("操作方法：");
	gotoxy(40, 16);
	printf("↑：旋转 ↓：沉淀");
	gotoxy(40, 18);
	printf("→：右移 ←：左移");
	gotoxy(39, 20);
	printf("空格键：开始 / 暂停");
	gotoxy(39, 22);
	printf("    Esc：退出");
	gotoxy(36, 25);
	printf("关 于：");
	gotoxy(40, 26);
	printf("俄罗斯方块 1.2.0");
	gotoxy(49, 27);
	printf("作者：鼠标猎人");
	gotoxy(50, 28);
	printf("2015年1月19日");
}


void clrscr(void)
{
	CONSOLE_SCREEN_BUFFER_INFO    csbiInfo;
	HANDLE    hConsoleOut;
	COORD    Home = { 0, 0 };
	DWORD    dummy;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

/*********************************************************************************/

void clreol(void)
{
	CONSOLE_SCREEN_BUFFER_INFO    csbiInfo;
	HANDLE    hConsoleOut;
	COORD    Home, pos;
	DWORD    dummy;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
	Home = csbiInfo.dwCursorPosition;
	pos.X = 80 - csbiInfo.dwCursorPosition.X;
	FillConsoleOutputCharacter(hConsoleOut, ' ', pos.X, Home, &dummy);
}

/*********************************************************************************/

void clreoscr(void)
{
	CONSOLE_SCREEN_BUFFER_INFO    csbiInfo;
	HANDLE    hConsoleOut;
	COORD    Home;
	DWORD    dummy;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
	Home = csbiInfo.dwCursorPosition;
	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
}
