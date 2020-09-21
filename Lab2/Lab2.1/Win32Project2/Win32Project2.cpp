#include <Windows.h>
#include <tchar.h>
#include "stdafx.h"

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

TCHAR WinName1[] = _T("MainFrame1");
TCHAR WinName2[] = _T("MainFrame2");

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
	wc.lpszClassName = WinName1; 								// Имя класса окна 
	wc.lpfnWndProc = WndProc; 									// Функция окна 
	wc.style = CS_HREDRAW | CS_VREDRAW; 						// Стиль окна 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 				// Стандартная иконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 					// Стандартный курсор 
	wc.lpszMenuName = NULL; 									// Нет меню 
	wc.cbClsExtra = 0; 											// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 											// Нет дополнительных данных окна 
	wc.hbrBackground = CreateSolidBrush ( RGB (0, 255, 0)); 	


	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0; 	

	// Создание окна 
	hWnd = CreateWindow(WinName1,			// Имя класса окна 
	_T("Окно 1"), 			// Заголовок окна 
	WS_OVERLAPPEDWINDOW, 		// Стиль окна 
	CW_USEDEFAULT,				// x 
	CW_USEDEFAULT, 				// y	 Размеры окна 
	CW_USEDEFAULT, 				// width 
	CW_USEDEFAULT, 				// Height 
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
		case WM_LBUTTONDOWN:
			des = FindWindow(WinName2, NULL);
			if (des == NULL)
				MessageBox(hWnd, _T("Окно 2 не найдено!"), _T("Не найдено"), MB_OK);
			else
			{
				SendMessage(des, WM_USER + 1, WPARAM(hWnd), NULL);
			}
		return DefWindowProc(hWnd, message, wParam, lParam);
		case WM_RBUTTONDOWN:
			des = FindWindow(WinName2, NULL);
			if (des == NULL)
				MessageBox(hWnd, _T("Окно 2 не найдено!"), _T("Не найдено"), MB_OK);
			else
			{
				SendMessage(des, WM_USER + 2, WPARAM(hWnd), NULL);
			}
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
		case WM_DESTROY : 
			PostQuitMessage(0); 
		break; 			
		default : 			
			return DefWindowProc(hWnd, message, wParam, lParam); 
		} 
	return 0;
}
