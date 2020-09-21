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

int WINAPI _tWinMain(HINSTANCE This,		 // ���������� �������� ���������� 
	HINSTANCE Prev, 	// � ����������� �������� ������ 0 
	LPTSTR cmd, 		// ��������� ������ 
	int mode) 		// ����� ����������� ����
{
	HWND hWnd;		// ���������� �������� ���� ��������� 
	MSG msg; 		// ��������� ��� �������� ��������� 
	WNDCLASS wc; 	// ����� ����
	// ����������� ������ ���� 
	wc.hInstance = This;
	wc.lpszClassName = WinName2; 				// ��� ������ ���� 
	wc.lpfnWndProc = WndProc; 					// ������� ���� 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// ����� ���� 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// ����������� ������ 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// ����������� ������ 
	wc.lpszMenuName = NULL; 					// ��� ���� 
	wc.cbClsExtra = 0; 						// ��� �������������� ������ ������ 
	wc.cbWndExtra = 0; 						// ��� �������������� ������ ���� 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); 	// ���������� ���� ����� ������ 



	// ����������� ������ ����
	if (!RegisterClass(&wc)) return 0;

	// �������� ���� 
	hWnd = CreateWindow(WinName2,			// ��� ������ ���� 
		_T("������������ ������ �4"), 		// ��������� ���� 
		WS_OVERLAPPEDWINDOW, 		// ����� ���� 
		300,				// x 
		70, 				// y	 ������� ���� 
		800, 				// width 
		600, 				// Height 
		HWND_DESKTOP, 				// ���������� ������������� ���� 
		NULL, 						// ��� ���� 
		This, 						// ���������� ���������� 
		NULL); 					// �������������� ���������� ��� 
	ShowWindow(hWnd, mode); 				// �������� ����
	/*HMENU MainMenu = CreateMenu();
	HMENU hPopupMenu = CreatePopupMenu();
	HMENU hPopupMenu2 = CreatePopupMenu();
	AppendMenu(MainMenu, MF_STRING | MF_POPUP, (UINT)hPopupMenu2, L"&����� 1");
	{
		AppendMenu(hPopupMenu2, MF_STRING, 1003, L"���������");
		AppendMenu(hPopupMenu2, MF_SEPARATOR, 0, L"");
		AppendMenu(hPopupMenu2, MF_STRING, 1004, L"�������������");
	}
	AppendMenu(MainMenu, MF_STRING | MF_POPUP, (UINT)hPopupMenu, L"&����� 2");
	{
		AppendMenu(hPopupMenu, MF_STRING, 1001, L"���������");
		AppendMenu(hPopupMenu, MF_SEPARATOR, 0, L"");
		AppendMenu(hPopupMenu, MF_STRING, 1002, L"�������������");
	}
	SetMenu(hWnd, MainMenu);*/

	// ���� ��������� ��������� 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// ������� ���������� ����� ������� ������� 
		DispatchMessage(&msg); 		// �������� ��������� ������� WndProc() 
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
		default: 			// ��������� ��������� �� ��������� 
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
			if (lParam == (LPARAM)button)    // ���� ������ �� ������
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
			TextOut(hdc, 50, 40, L"������� ����� ������������ ���� � ��������", 50);
			EndPaint(hWnd, &ps); // ����� �����������
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




