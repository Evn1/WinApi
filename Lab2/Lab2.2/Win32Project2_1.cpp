#include <Windows.h>
#include <tchar.h>
#include "stdafx.h"

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

TCHAR WinName2[] = _T("MainFrame2");
int x1 = 600;
int y1 = 600;
int WINAPI _tWinMain(HINSTANCE This,	// ���������� �������� ���������� 
					 HINSTANCE Prev, 	// � ����������� �������� ������ 0 
					 LPTSTR cmd, 		// ��������� ������ 
					 int mode) 			// ����� ����������� ����
{ 
	HWND hWnd;		// ���������� �������� ���� ��������� 
	MSG msg; 		// ��������� ��� �������� ��������� 
	WNDCLASS wc; 	// ����� ����
	// ����������� ������ ���� 
	wc.hInstance = This; 
	wc.lpszClassName = WinName2; 								// ��� ������ ���� 
	wc.lpfnWndProc = WndProc; 									// ������� ���� 
	wc.style = CS_HREDRAW | CS_VREDRAW; 						// ����� ���� 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 				// ����������� ������ 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 					// ����������� ������ 
	wc.lpszMenuName = NULL; 									// ��� ���� 
	wc.cbClsExtra = 0; 											// ��� �������������� ������ ������ 
	wc.cbWndExtra = 0; 											// ��� �������������� ������ ���� 
	wc.hbrBackground = CreateSolidBrush ( RGB ( 255, 255, 224)); 	// ���������� ���� ����� ������ 


	// ����������� ������ ����
	if (!RegisterClass(&wc)) return 0; 	

	// �������� ���� 
	hWnd = CreateWindow(WinName2,			// ��� ������ ���� 
	_T("���� 2"), 			// ��������� ���� 
	WS_OVERLAPPEDWINDOW, 		// ����� ���� 
	CW_USEDEFAULT,				// x 
	CW_USEDEFAULT, 				// y	 ������� ���� 
	x1, 				// width 
	y1, 				// Height 
	HWND_DESKTOP, 				// ���������� ������������� ���� 
	NULL, 						// ��� ���� 
	This, 						// ���������� ���������� 
	NULL); 						// �������������� ���������� ��� 

	ShowWindow(hWnd, mode); 				// �������� ����

	// ���� ��������� ��������� 
	while(GetMessage(&msg, NULL, 0, 0)) 
	{ 
		TranslateMessage(&msg); 		// ������� ���������� ����� ������� ������� 
		DispatchMessage(&msg); 		// �������� ��������� ������� WndProc() 
	} 
	return 0;
	}

	// ������� ������� ���������� ������������ ��������
	// � �������� ��������� �� ������� ��� ������� ����������

	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
	HWND des;


	switch(message)		 // ���������� ���������
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
