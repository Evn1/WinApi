#include <Windows.h>
#include <tchar.h>
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include "resource.h"
using namespace std;
#define _CRT_SECURE_NO_WARNINGS

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);
HWND textbox;
TCHAR WinName[] = _T("MainFrame");

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
	wc.lpszClassName = WinName; 								// ��� ������ ���� 
	wc.lpfnWndProc = WndProc; 									// ������� ���� 
	wc.style = CS_HREDRAW | CS_VREDRAW; 						// ����� ���� 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 				// ����������� ������ 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 					// ����������� ������ 
	wc.lpszMenuName = NULL; 									// ��� ���� 
	wc.cbClsExtra = 0; 											// ��� �������������� ������ ������ 
	wc.cbWndExtra = 0; 											// ��� �������������� ������ ���� 
	wc.hbrBackground = CreateSolidBrush ( RGB ( 255, 100, 150)); 	


	// ����������� ������ ����
	if (!RegisterClass(&wc)) return 0; 	

	// �������� ���� 
	hWnd = CreateWindow(WinName,			// ��� ������ ���� 
	_T("������������ ������ �3"), 			// ��������� ���� 
	WS_OVERLAPPEDWINDOW, 		// ����� ���� 
	CW_USEDEFAULT,				// x 
	CW_USEDEFAULT, 				// y	 ������� ���� 
	CW_USEDEFAULT, 				// width 
	CW_USEDEFAULT, 				// Height 
	HWND_DESKTOP, 				// ���������� ������������� ���� 
	NULL, 						// ��� ���� 
	This, 						// ���������� ���������� 
	NULL); 						// �������������� ���������� ��� 
	
	HMENU menu = CreateMenu();
	HMENU popmenu = CreatePopupMenu();
	AppendMenu(menu, MF_STRING | MF_POPUP, (UINT)popmenu, L"����");
	{
		AppendMenu(popmenu, MF_STRING, 1, L"�������");
		AppendMenu(popmenu, MF_STRING, 2, L"�������");
		AppendMenu(popmenu, MF_STRING, 3, L"���������");
	}
	AppendMenu(menu, MF_STRING, 4, L"��������");
	AppendMenu(menu, MF_STRING, 5, L"����������");
	AppendMenu(menu, MF_STRING, 6, L"��������");
	AppendMenu(menu, MF_STRING, 7, L"��������");
	SetMenu(hWnd, menu);
	ShowWindow(hWnd, mode); 				
	
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
	char* txt = "text.txt";
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		switch(message)		 // ���������� ���������
		{ 
			case WM_CREATE:
	{
		    textbox = CreateWindow(
			_T("EDIT"),
			_T(""),
			WS_BORDER | WS_VSCROLL | WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_MULTILINE,
			10, // x
			10, // y
			650,
			500,
			hWnd,
			(HMENU) 11,
			NULL,
			NULL
		);
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case 1:
		{
			ofstream fout;
			txt = "text1.txt";
			fout.open(txt);
			fout.close();
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}
		case 2:
		{
			ifstream fin;
			static char buf[1000];
			static wchar_t wbuf[1000];
			fin.open(txt);
			if (!fin.is_open())
				MessageBox(hWnd, L"��������� ���� �� ������!", L"������", MB_OK);
			else
			{
				for (int i = 0; i < 1000; i++)
				{
				        fin.seekg(0, ios::beg);
						fin.read(buf, i);
				}
			}
			fin.close();
			MultiByteToWideChar(CP_UTF8, 0, buf, -1, wbuf, 1000);
			SendMessage(textbox, WM_SETTEXT, 1000, (LPARAM)wbuf);
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}
		case 3:
		{
			ofstream fout;
			static char buf[1000];
			static wchar_t wbuf[1000];
			SendMessage(textbox, WM_GETTEXT, 1000, (LPARAM)wbuf);
			WideCharToMultiByte(CP_ACP, 0, wbuf, -1, buf, 1000, nullptr, nullptr);
			if (txt == "text.txt")
			    fout.open("text.txt");
			else if (txt == "text1.txt")
				fout.open("text1.txt");
			for (int i = 0; i < 1000; i++)
			{
				fout.seekp(0, ios::beg);
				fout.write(buf, i);
			}
			fout.close();
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}
		case 4:
			SendMessage(textbox, WM_CUT, 0, 0);
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		case 5:
			SendMessage(textbox, WM_COPY, 0, 0);
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		case 6:
			SendMessage(textbox, WM_PASTE, 0, 0);
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		case 7:
			SendMessage(textbox, WM_CLEAR, 0, 0);
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		default: 			// ��������� ��������� �� ��������� 
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
			case WM_DESTROY : 
				PostQuitMessage(0); 
			break; 			
			default : 			
				return DefWindowProc(hWnd, message, wParam, lParam); 
			} 
		return 0;
	}
