
#include <windows.h>
#include <stdio.h>

#include "rander.h"

//���ô���λ�úʹ�С��Ϊ���ó������еø��ÿ�
void console()
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);// ��ȡ��׼����豸���
	CONSOLE_SCREEN_BUFFER_INFO bInfo; // ���ڻ�������Ϣ
	GetConsoleScreenBufferInfo(hOut, &bInfo);// ��ȡ���ڻ�������Ϣ
	SetConsoleTitle(L"����˹����"); // ���ô��ڵı���
	COORD size = { 128, 64 };//����С��Ĭ�ϴ�С��80��25��
	SetConsoleScreenBufferSize(hOut, size); // �������û�������С*/
	SMALL_RECT rc = { 0, 0, 128 - 1, 64 - 1 }; //���ܴ��ڻ�������С
	SetConsoleWindowInfo(hOut, true, &rc);// ���ô��ڴ�С
	CONSOLE_CURSOR_INFO cursor_info = { 1, 0 }; //��һ���������ٷֱȴ�С���ڶ��������Ƿ�ɼ���
	SetConsoleCursorInfo(hOut, &cursor_info);//���ÿ���̨���
}

//���ù�������λ�ú��������겻��Ϊ����,X��ʾ�����꣬Y��ʾ�����ꡣ
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

//�˳�ǰ������߷�
void my_exit()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
	gotoxy(12, 12); printf("================================");
	gotoxy(12, 13); printf("||  ��Ϸ���˳� ��������رգ� ||");
	gotoxy(12, 14); printf("================================");
	gotoxy(0, 30);
	Sleep(1000);
	exit(0);
}

//�������ʾ
void my_print()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);//�ڵ������֡�
	for (int i = 1; i < 30; i++)
		printf("��\t\t\t\t�� |                           |\n");
	printf("���������������������������������� |---------------------------|\n");//���
	gotoxy(36, 0);
	printf("---------------------------");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);//�ڵ������֡�
	gotoxy(40, 2);
	printf("��  ���� %d", 1);
	gotoxy(40, 3);
	printf("��  ���� %d", 1);
	gotoxy(40, 4);
	printf("��߷֣� %d", 1);
	gotoxy(36, 6);
	printf("��һ�����飺");
	gotoxy(36, 14);
	printf("����������");
	gotoxy(40, 16);
	printf("������ת ��������");
	gotoxy(40, 18);
	printf("�������� ��������");
	gotoxy(39, 20);
	printf("�ո������ʼ / ��ͣ");
	gotoxy(39, 22);
	printf("    Esc���˳�");
	gotoxy(36, 25);
	printf("�� �ڣ�");
	gotoxy(40, 26);
	printf("����˹���� 1.2.0");
	gotoxy(49, 27);
	printf("���ߣ��������");
	gotoxy(50, 28);
	printf("2015��1��19��");
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
