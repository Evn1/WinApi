#include <Windows.h>
#include "stdafx.h"
#include <tchar.h>
#include <wchar.h>
#include <time.h>
#include <iostream>
using namespace std;

#pragma warning(disable:4996)
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
TCHAR WinName2[] = _T("MainFrame2");

int WINAPI _tWinMain(HINSTANCE This,		 // Дескриптор текущего приложения 
	HINSTANCE Prev, 	// В современных системах всегда 0 
	LPTSTR cmd, 		// Командная строка 
	int mode) 		// Режим отображения окна
{
	HWND hWnd;		// Дескриптор главного окна программы 
	MSG msg; 		// Структура для хранения сообщения 
	WNDCLASS wc; 	// Класс окна
	// Определение класса окна 
	wc.hInstance = This;
	wc.lpszClassName = WinName2; 				// Имя класса окна 
	wc.lpfnWndProc = WndProc; 					// Функция окна 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// Стиль окна 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// Стандартная иконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// Стандартный курсор 
	wc.lpszMenuName = NULL; 					// Нет меню 
	wc.cbClsExtra = 0; 						// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 						// Нет дополнительных данных окна 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); 	// Заполнение окна белым цветом 



	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0;

	// Создание окна 
	hWnd = CreateWindow(WinName2,			// Имя класса окна 
		_T("Лабораторная работа №4"), 		// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
		300,				// x 
		70, 				// y	 Размеры окна 
		800, 				// width 
		600, 				// Height 
		HWND_DESKTOP, 				// Дескриптор родительского окна 
		NULL, 						// Нет меню 
		This, 						// Дескриптор приложения 
		NULL); 					// Дополнительной информации нет 
	ShowWindow(hWnd, mode); 				// Показать окно
	/*HMENU MainMenu = CreateMenu();
	HMENU hPopupMenu = CreatePopupMenu();
	HMENU hPopupMenu2 = CreatePopupMenu();
	AppendMenu(MainMenu, MF_STRING | MF_POPUP, (UINT)hPopupMenu2, L"&Поток 1");
	{
		AppendMenu(hPopupMenu2, MF_STRING, 1003, L"Запустить");
		AppendMenu(hPopupMenu2, MF_SEPARATOR, 0, L"");
		AppendMenu(hPopupMenu2, MF_STRING, 1004, L"Приостановить");
	}
	AppendMenu(MainMenu, MF_STRING | MF_POPUP, (UINT)hPopupMenu, L"&Поток 2");
	{
		AppendMenu(hPopupMenu, MF_STRING, 1001, L"Запустить");
		AppendMenu(hPopupMenu, MF_SEPARATOR, 0, L"");
		AppendMenu(hPopupMenu, MF_STRING, 1002, L"Приостановить");
	}
	SetMenu(hWnd, MainMenu);*/

	// Цикл обработки сообщений 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// Функция трансляции кодов нажатой клавиши 
		DispatchMessage(&msg); 		// Посылает сообщение функции WndProc() 
	}
	return 0;
}
DWORD WINAPI Thread1(LPVOID t);
HANDLE hThread1;
HWND textbox;
HWND button;
RECT clientRect= { 0,0,400,800 };
int msec = 0;
void Thread(HWND hWnd)
{
	HDC hdc = GetDC(hWnd);
	HBRUSH hBrush;
	RECT rect1 = { 0,0,400,800 };
	FillRect(hdc, &rect1, CreateSolidBrush(RGB(rand()%255, rand()%255, rand()%255)));
	hBrush = CreateSolidBrush(RGB(0, 0, 0));
	HBRUSH old = (HBRUSH)SelectObject(hdc, hBrush);
	Ellipse(hdc, 100, 200, 300, 400);
	DeleteObject(SelectObject(hdc, hBrush));
	ReleaseDC(hWnd, hdc);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_DESTROY:
		{
			TerminateThread(hThread1, 0);
			PostQuitMessage(0);
			break;
		}
		default: 			// Обработка сообщения по умолчанию 
			return DefWindowProc(hWnd, message, wParam, lParam);
		case WM_CREATE:
			{
				textbox = CreateWindow
				(
					_T("EDIT"),
					_T(""),
					WS_BORDER | WS_VSCROLL | WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_NUMBER,
					50, // x
					80, // y
					60,
					20,
					hWnd,
					NULL,
					NULL,
					NULL
				);
				button = CreateWindow
				(
					L"BUTTON", 
					L"OK",
					 WS_CHILD | WS_VISIBLE | WS_BORDER,
					 120, 
					 80, 
					 60, 
					 20, 
					 hWnd,
					 NULL, 
					 NULL, 
					 NULL
				 );
			break;
			}
		case WM_COMMAND:
		{
			if (lParam == (LPARAM)button)    // если нажали на кнопку
			{
				TCHAR StrA[20];
				int len;
				len = GetWindowText(textbox, StrA, 20);
				msec = _wtoi(StrA);
				Thread(hWnd);
				SetTimer(hWnd, 0,(msec*1000) , 0);
				hThread1 = CreateThread(NULL, 0, Thread1, hWnd, 0, NULL);
			}
			break;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps); 
			TextOut(hdc, 50, 40, L"Введите время переключения фона в секундах", 50);
			EndPaint(hWnd, &ps); // конец перерисовки
		break;
		}
		case WM_TIMER:
		{
			Thread(hWnd);
		break;
		}
	}
}

DWORD WINAPI Thread1(LPVOID t)
{
	while(1)
	{
		PAINTSTRUCT ps;
		TCHAR buff[300];
		HDC hdc1 = GetDC(HWND(t));
		RECT clientRect = {  400,0,800,800 };
		InvalidateRect((HWND)t, &clientRect, TRUE);
		UpdateWindow((HWND)t);
		_stprintf(buff, TEXT("%d"), GetCurrentTime());
		SetTextColor(hdc1, RGB(0,0,0));
		TextOut(hdc1, 420, 250, buff, _tcslen(buff));
		EndPaint(HWND(t), &ps);
	}
	return 0;
}




