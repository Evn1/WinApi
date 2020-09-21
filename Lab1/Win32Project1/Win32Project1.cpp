#include <Windows.h>
#include <tchar.h>
#include "stdafx.h"

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");

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
	wc.lpszClassName = WinName; 								// Имя класса окна 
	wc.lpfnWndProc = WndProc; 									// Функция окна 
	wc.style = CS_HREDRAW | CS_VREDRAW; 						// Стиль окна 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 				// Стандартная иконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 					// Стандартный курсор 
	wc.lpszMenuName = NULL; 									// Нет меню 
	wc.cbClsExtra = 0; 											// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 											// Нет дополнительных данных окна 
	wc.hbrBackground = CreateSolidBrush ( RGB ( 224, 254, 0)); 	// Заполнение окна белым цветом 


	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0; 	

	// Создание окна 
	hWnd = CreateWindow(WinName,			// Имя класса окна 
	_T("Лабораторная работа №1"), 			// Заголовок окна 
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
	INT click = 1;
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
	static HDC hDC;		// создаём дескриптор ориентации текста на экране
    PAINTSTRUCT ps;		// структура, сод-щая информацию о клиентской области (размеры, цвет и тп)
    RECT rect;			// стр-ра, определяющая размер клиентской области
	HFONT hFont;
	HBRUSH brush;
    static COLORREF colorText = RGB(254, 0, 255); // задаём цвет текста
	int StartX = 10;
	int StartY = 10;
	int EndX = 200;
	int EndY = 200;
	switch(message)		 // Обработчик сообщений
	{ 
		case WM_CREATE:
		{
			MessageBox
			(
				hWnd,
				L"Ведьгун Е.А\nИУ5-34\nВариант №3\nЦель работы: Вывод фигур по нажатию правой кнопки мыши и вывод их названий по левой",
				L"ЛР №1",
				MB_OK
			);
		}
		break;

		case WM_PAINT:
			hDC = BeginPaint(hWnd, &ps);	
		break;

		case WM_LBUTTONDOWN:
		{
			hDC = GetDC(hWnd);
			switch(click)
			{
			case 1:
			{
				brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)); 
				SelectObject(hDC, brush); 
				Rectangle(hDC,StartX,StartY,EndX,EndY);
				click++;
				break;
			}
			case 2:
			{
				brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)); 
				SelectObject(hDC, brush); 
				Ellipse(hDC,EndX+20,StartY,3*EndX,EndY);
				click++;
				break;
			}
			case 3:
			{
				brush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)); 
				SelectObject(hDC, brush); 
				POINT poly[3] = { {3*EndX,EndY },{ 3*EndX+200,EndY },{3*EndX+100,StartY} };
				Polygon(hDC, poly, 3);
				click++;
				break;
			}
			}
			break;
		}
		case WM_RBUTTONDOWN:
		{
			int xMouse = LOWORD(lParam);
			int yMouse = HIWORD(lParam);
			LOGFONT lf;
			lf.lfHeight = 20;
			lf.lfItalic = 0; // курсив
			lf.lfStrikeOut = 0; // зачеркнуто
			lf.lfUnderline = 0; //подчеркнуто
			lf.lfWidth = 7;
			lf.lfWeight = 40;
			lf.lfCharSet = DEFAULT_CHARSET; //значение по умолчанию
			lf.lfPitchAndFamily = DEFAULT_PITCH; //ширина символов и семейство
			lf.lfEscapement = 0;
			SelectObject(hDC, CreateFontIndirect(&lf));
			hDC = GetDC(hWnd);
			if(xMouse >= StartX && xMouse <= EndX && yMouse >= StartY && yMouse <= EndY)
			{
				SetTextColor(hDC, RGB(rand() % 255, rand() % 255, rand() % 255));
				SetBkMode(hDC, TRANSPARENT);
				TextOut(hDC, StartX, EndY+10, L"Прямоугольник: ", strlen("Прямоугольник: "));
			}
			else if(xMouse >= (EndX+20) && xMouse <= (3*EndX) && yMouse >= StartY && yMouse <= EndY)
			{
				SetTextColor(hDC, RGB(rand() % 255, rand() % 255, rand() % 255));
				SetBkMode(hDC, TRANSPARENT);
				TextOut(hDC, EndX+20, EndY+10, L"Эллипс: ", strlen("Эллипс: "));
			}
			else if(xMouse >= (3*EndX) && xMouse <= (3*EndX+200) && yMouse >= StartY && yMouse <= EndY)
			{
				SetTextColor(hDC, RGB(rand() % 255, rand() % 255, rand() % 255));
				SetBkMode(hDC, TRANSPARENT);
				TextOut(hDC, 3*EndX, EndY+10, L"Треугольник: ", strlen("Треугольник: "));
			}
			ReleaseDC(hWnd,hDC);
		}
		break;
		case WM_DESTROY : 
			PostQuitMessage(0); 
		break; 			
		default : 			
			return DefWindowProc(hWnd, message, wParam, lParam); 
		} 
	return 0;
}

