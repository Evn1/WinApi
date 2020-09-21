#include <Windows.h>
#include <tchar.h>
#include "stdafx.h"

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

TCHAR WinName1[] = _T("MainFrame1");
TCHAR WinName2[] = _T("MainFrame2");

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
	wc.lpszClassName = WinName1; 								// ��� ������ ���� 
	wc.lpfnWndProc = WndProc; 									// ������� ���� 
	wc.style = CS_HREDRAW | CS_VREDRAW; 						// ����� ���� 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 				// ����������� ������ 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 					// ����������� ������ 
	wc.lpszMenuName = NULL; 									// ��� ���� 
	wc.cbClsExtra = 0; 											// ��� �������������� ������ ������ 
	wc.cbWndExtra = 0; 											// ��� �������������� ������ ���� 
	wc.hbrBackground = CreateSolidBrush ( RGB (0, 255, 0)); 	


	// ����������� ������ ����
	if (!RegisterClass(&wc)) return 0; 	

	// �������� ���� 
	hWnd = CreateWindow(WinName1,			// ��� ������ ���� 
	_T("���� 1"), 			// ��������� ���� 
	WS_OVERLAPPEDWINDOW, 		// ����� ���� 
	CW_USEDEFAULT,				// x 
	CW_USEDEFAULT, 				// y	 ������� ���� 
	CW_USEDEFAULT, 				// width 
	CW_USEDEFAULT, 				// Height 
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
		case WM_LBUTTONDOWN:
			des = FindWindow(WinName2, NULL);
			if (des == NULL)
				MessageBox(hWnd, _T("���� 2 �� �������!"), _T("�� �������"), MB_OK);
			else
			{
				SendMessage(des, WM_USER + 1, WPARAM(hWnd), NULL);
			}
		return DefWindowProc(hWnd, message, wParam, lParam);
		case WM_RBUTTONDOWN:
			des = FindWindow(WinName2, NULL);
			if (des == NULL)
				MessageBox(hWnd, _T("���� 2 �� �������!"), _T("�� �������"), MB_OK);
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
