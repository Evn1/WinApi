#include <Windows.h>
#include <tchar.h>
#include "stdafx.h"

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

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
	wc.hbrBackground = CreateSolidBrush ( RGB ( 224, 254, 0)); 	// ���������� ���� ����� ������ 


	// ����������� ������ ����
	if (!RegisterClass(&wc)) return 0; 	

	// �������� ���� 
	hWnd = CreateWindow(WinName,			// ��� ������ ���� 
	_T("������������ ������ �1"), 			// ��������� ���� 
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
	INT click = 1;
	LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
	static HDC hDC;		// ������ ���������� ���������� ������ �� ������
    PAINTSTRUCT ps;		// ���������, ���-��� ���������� � ���������� ������� (�������, ���� � ��)
    RECT rect;			// ���-��, ������������ ������ ���������� �������
	HFONT hFont;
	HBRUSH brush;
    static COLORREF colorText = RGB(254, 0, 255); // ����� ���� ������
	int StartX = 10;
	int StartY = 10;
	int EndX = 200;
	int EndY = 200;
	switch(message)		 // ���������� ���������
	{ 
		case WM_CREATE:
		{
			MessageBox
			(
				hWnd,
				L"������� �.�\n��5-34\n������� �3\n���� ������: ����� ����� �� ������� ������ ������ ���� � ����� �� �������� �� �����",
				L"�� �1",
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
			lf.lfItalic = 0; // ������
			lf.lfStrikeOut = 0; // ����������
			lf.lfUnderline = 0; //�����������
			lf.lfWidth = 7;
			lf.lfWeight = 40;
			lf.lfCharSet = DEFAULT_CHARSET; //�������� �� ���������
			lf.lfPitchAndFamily = DEFAULT_PITCH; //������ �������� � ���������
			lf.lfEscapement = 0;
			SelectObject(hDC, CreateFontIndirect(&lf));
			hDC = GetDC(hWnd);
			if(xMouse >= StartX && xMouse <= EndX && yMouse >= StartY && yMouse <= EndY)
			{
				SetTextColor(hDC, RGB(rand() % 255, rand() % 255, rand() % 255));
				SetBkMode(hDC, TRANSPARENT);
				TextOut(hDC, StartX, EndY+10, L"�������������: ", strlen("�������������: "));
			}
			else if(xMouse >= (EndX+20) && xMouse <= (3*EndX) && yMouse >= StartY && yMouse <= EndY)
			{
				SetTextColor(hDC, RGB(rand() % 255, rand() % 255, rand() % 255));
				SetBkMode(hDC, TRANSPARENT);
				TextOut(hDC, EndX+20, EndY+10, L"������: ", strlen("������: "));
			}
			else if(xMouse >= (3*EndX) && xMouse <= (3*EndX+200) && yMouse >= StartY && yMouse <= EndY)
			{
				SetTextColor(hDC, RGB(rand() % 255, rand() % 255, rand() % 255));
				SetBkMode(hDC, TRANSPARENT);
				TextOut(hDC, 3*EndX, EndY+10, L"�����������: ", strlen("�����������: "));
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

