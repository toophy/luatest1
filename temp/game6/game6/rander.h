#pragma once

#include <windows.h>

//���ô���λ�úʹ�С��Ϊ���ó������еø��ÿ�
void console();

//���ù�������λ�ú��������겻��Ϊ����, X��ʾ�����꣬Y��ʾ�����ꡣ
void gotoxy(int x, int y);

//�˳�ǰ������߷�
void my_exit();

//�������ʾ
void my_print();


void clrscr(void);
void clreol(void);
void clreoscr(void);