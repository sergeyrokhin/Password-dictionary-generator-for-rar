#pragma once
#ifndef MyConsoleFrame
#define MyConsoleFrame
#include <iostream>
#include <map>
#include <conio.h>
#include <windows.h>

using namespace std;

template <class T>

class ConsoleFrame
{
public:

	ConsoleFrame();
	//~ConsoleFrame();
	void AddPoint(T, unsigned short X, unsigned short Y);
	void Slide(short dY);
    void SetCursor(T name);
    void Print(T name, const char* text);
	HANDLE hStdout;
	map<T, COORD> output_point;
	//private:
	unsigned y_zero;
};

//template <class T1, class T2>
//void Print(ConsoleFrame<T1> Console, T1 name, T2 text);

//Реализация

template <class T>
ConsoleFrame <T>::ConsoleFrame() : y_zero(0)
{
    CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    if (!GetConsoleScreenBufferInfo(hStdout, &csbiInfo))
    {
        printf("GetConsoleScreenBufferInfo (%d)\n", GetLastError());
        return;
    }
    y_zero = csbiInfo.dwCursorPosition.Y;
}

template <class T>
void ConsoleFrame <T>::AddPoint(T name, unsigned short X, unsigned short Y)
{
    COORD scrn;

    scrn.X = X;
    scrn.Y = Y;
    output_point[name] = scrn;
}

template <class T>
void ConsoleFrame <T>::Slide(short dY)
{
    int new_Y = (int)y_zero + dY;
    y_zero = new_Y > 0 ? new_Y : 0;
}

template <class T>
void ConsoleFrame <T>::Print(T name, const char* text)
{
    COORD point = output_point.at(name);
    point.Y += y_zero;
    SetConsoleCursorPosition(hStdout, point);
    cout << text;
}

template <class T>
void ConsoleFrame <T>::SetCursor(T name)
{
    COORD point = output_point.at(name);
    point.Y += y_zero;
    SetConsoleCursorPosition(hStdout, point);
}

//template <class T1, class T2>
//void Print(ConsoleFrame<T1> Console, T1 name, T2 text)
//{
//    COORD point = Console.output_point.at(name);
//    point.Y += Console.y_zero;
//    SetConsoleCursorPosition(Console.hStdout, point);
//    cout << text;
//}

#endif