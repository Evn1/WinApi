#include <Windows.h>
#include <tchar.h>
#include "stdafx.h"

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

TCHAR WinName2[] = _T("MainFrame2");
int x1 = 600;
int y1 = 600;
int WINAPI _tWinMain(HINSTANCE This,	// Дескриптор текущего приложения 
					 HINSTANCE Prev, 	// В современных системах всегда 0 
					 LPTSTR cmd, 		// Командная строка 
					 int mode) 			// Режим отображения окна
{ 
	HWND hWnd;		// Дескриптор главного окна программы 
	MSG msg; 		// Структура для хранения сообщения 
	WNDCLASS wc; 	// Класс окна
	// Определение класса окна 
	wc.hInstance = This; 
	wc.lpszClassName = WinName2; 								// Имя класса окна 
	wc.lpfnWndProc = WndProc; 									// Функция окна 
	wc.style = CS_HREDRAW | CS_VREDRAW; 						// Стиль окна 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 				// Стандартная иконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 					// Стандартный курсор 
	wc.lpszMenuName = NULL; 									// Нет меню 
	wc.cbClsExtra = 0; 											// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 											// Нет дополнительных данных окна 
	wc.hbrBackground = CreateSolidBrush ( RGB ( 255, 255, 224)); 	// Заполнение окна белым цветом 


	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0; 	

	// Создание окна 
	hWnd = CreateWindow(WinName2,			// Имя класса окна 
	_T("Окно 2"), 			// Заголовок окна 
	WS_OVERLAPPEDWINDOW, 		// Стиль окна 
	CW_USEDEFAULT,				// x 
	CW_USEDEFAULT, 				// y	 Размеры окна 
	x1, 				// width 
	y1, 				// Height 
	HWND_DESKTOP, 				// Дескриптор родительского окна 
	NULL, 						// Нет меню 
	This, 						// Дескриптор приложения 
	NULL); 						// Дополнительной информации нет 

	ShowWindow(hWnd, mode); 				// Показать окно

	// Цикл обработки сообщений 
	while(GetMessage(&msg, NULL, 0, 0)) 
	{ 
		TranslateMessage(&msg); 		// Функция трансляции кодов нажатой клавиши 
		DispatchMessage(&msg); 		// Посылает сообщение функции WndProc() 
	} 
	return 0;
	}

	// Оконная функция вызывается операционной системой
	// и получает сообщения из очереди для данного приложения

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
	HWND des;


	switch(message)		 // Обработчик сообщений
	{ 
		case WM_USER + 1:
		{
			x1-=50;
			y1-=50;
			SetWindowPos(hWnd, HWND_BOTTOM, 0, 0, x1, y1, SWP_NOMOVE);
		return DefWindowProc(hWnd, message, wParam, lParam); 
		}
		case WM_USER + 2:
		{
			x1+=50;
			y1+=50;
			SetWindowPos(hWnd, HWND_BOTTOM, 0, 0, x1, y1, SWP_NOMOVE);
		return DefWindowProc(hWnd, message, wParam, lParam);
		}
		case WM_DESTROY:
			PostQuitMessage(0);
		break; 
		default : 			
			return DefWindowProc(hWnd, message, wParam, lParam); 
		} 
	return 0;
}
