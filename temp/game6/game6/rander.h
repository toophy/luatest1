#pragma once

#include <windows.h>

//设置窗口位置和大小，为了让程序运行得更好看
void console();

//设置光标输出的位置函数。坐标不能为负数, X表示横坐标，Y表示纵坐标。
void gotoxy(int x, int y);

//退出前保存最高分
void my_exit();

//右面板显示
void my_print();


void clrscr(void);
void clreol(void);
void clreoscr(void);