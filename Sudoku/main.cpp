#include "globals.h"
#define FILE_MENU_NEW 1
#define FILE_MENU_OPEN 2
#define FILE_MENU_EXIT 3
#define FILE_MENU_Upload 4

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void AddMenus(HWND hWnd);
HMENU hMenu;
HWND title;
void drawEasy(HDC hdc);
void drawHard(HDC hdc);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow)
{
	// Initialize GDI+
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
	WNDCLASSW wc = { 0 };
	//wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	HBRUSH hb = ::CreateSolidBrush(RGB(222, 231, 249));
	wc.hbrBackground = hb;

	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hInstance = hInst;
	wc.lpszClassName = L"SudokoSolver";
	wc.lpfnWndProc = WindowProcedure;

	if (!RegisterClassW(&wc))
		return -1;

	CreateWindowW(L"SudokoSolver", L"Sudoko Solver", WS_SYSMENU | WS_VISIBLE, 100, 100, 500, 500,
		NULL, NULL, NULL, NULL);




	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, NULL, NULL))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

	}
	Gdiplus::GdiplusShutdown(gdiplusToken);

	return 0;
}




void open_file(HWND hWnd)
{
	OPENFILENAME ofn;
	char file_name[100];
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hWnd;
	ofn.lpstrFile = file_name;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = 100;
	ofn.lpstrFilter = "All files\0*.*\0Source Files\0*.CPP\0Text Files\0*.TXT\0";
	ofn.nFilterIndex = 1;

	GetOpenFileName(&ofn);

	MessageBox(NULL, ofn.lpstrFile, "", MB_OK);

}
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
	HDC hdc;
	PAINTSTRUCT ps;
	int val;
	ReadFromFile r("input.txt");

	if (r.sizeOfBoard == 4)
	{
		hdc = BeginPaint(hWnd, &ps);
		drawEasy(hdc);
		SetBkMode(hdc, TRANSPARENT);

		int count = 0;
		int board[4][4];
		graph g(r);
		g.greedyColoring();
		g.getAll();
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				board[i][j] = g.color[count];
				count++;
			}
		}
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				int x;
				if (i == 0) x = 70;
				else if (i == 1) x = 125;
				else if (i == 2) x = 175;
				else if (i == 3) x = 225;
				if (board[i][j] != -1)
				{
					if (j == 0)
						TextOut(hdc, 70, x, to_string(board[i][j]).c_str(), 1);
					else if (j == 1)
						TextOut(hdc, 125, x, to_string(board[i][j]).c_str(), 1);
					else if (j == 2)
						TextOut(hdc, 175, x, to_string(board[i][j]).c_str(), 1);
					else if (j == 3)
						TextOut(hdc, 225, x, to_string(board[i][j]).c_str(), 1);

				}

			}
		}

		EndPaint(hWnd, &ps);
	}
	else
	{
		hdc = BeginPaint(hWnd, &ps);
		drawHard(hdc);
		SetBkMode(hdc, TRANSPARENT);

		int count = 0;
		int board[9][9];
		graph g(r);
		g.greedyColoring();
		g.getAll();
		ReadFromFile r2("outputSingle.txt");
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				if (r2.vectorBoard[i][j] < 10 && r2.vectorBoard[i][j]>0)
				{
					board[i][j] = r2.vectorBoard[i][j];
					count++;
				}
			}
		}
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				int x;
				if (i == 0) x = 60;
				else if (i == 1) x = 100;
				else if (i == 2) x = 140;
				else if (i == 3) x = 180;
				else if (i == 4) x = 220;
				else if (i == 5) x = 260;
				else if (i == 6) x = 300;
				else if (i == 7) x = 340;
				else if (i == 8) x = 380;
				else if (i == 9) x = 420;

				if (j == 0)
					TextOut(hdc, 40, x, to_string(board[i][j]).c_str(), 1);
				else if (j == 1)
					TextOut(hdc, 70, x, to_string(board[i][j]).c_str(), 1);
				else if (j == 2)
					TextOut(hdc, 120, x, to_string(board[i][j]).c_str(), 1);
				else if (j == 3)
					TextOut(hdc, 160, x, to_string(board[i][j]).c_str(), 1);
				else if (j == 4)
					TextOut(hdc, 200, x, to_string(board[i][j]).c_str(), 1);
				else if (j == 5)
					TextOut(hdc, 240, x, to_string(board[i][j]).c_str(), 1);
				else if (j == 6)
					TextOut(hdc, 280, x, to_string(board[i][j]).c_str(), 1);
				else if (j == 7)
					TextOut(hdc, 320, x, to_string(board[i][j]).c_str(), 1);
				else if (j == 8)
					TextOut(hdc, 360, x, to_string(board[i][j]).c_str(), 1);
				else if (j == 9)
					TextOut(hdc, 225, x, to_string(board[i][j]).c_str(), 1);


			}
		}

		EndPaint(hWnd, &ps);

	}

	switch (msg)
	{

	case WM_COMMAND:

		switch (wp)
		{
		case FILE_MENU_EXIT:
			val = MessageBoxW(hWnd, L"Are you sure?", L"wait!", MB_YESNO | MB_ICONEXCLAMATION);
			if (val == IDYES)
			{
				DestroyWindow(hWnd);
			}
			break;

		case FILE_MENU_NEW:
			MessageBeep(MB_ICONINFORMATION);
			break;
		default:
			return DefWindowProcW(hWnd, msg, wp, lp);
		}
		break;
	case WM_CREATE:
		UpdateWindow(hWnd);
		title = CreateWindow("STATIC", "Welcome to Sukoku!!", WS_VISIBLE | WS_CHILD | SS_CENTER, 50, 20, 200, 25, hWnd, NULL, NULL, NULL);
		AddMenus(hWnd);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProcW(hWnd, msg, wp, lp);
	}
}


void drawEasy(HDC hdc)
{
	Gdiplus::Graphics gf(hdc);
	Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0, 225));               // For lines, rectangles and curves
	Gdiplus::Pen pen2(Gdiplus::Color(255, 255, 0, 0));
	gf.DrawLine(&pen, 50, 50, 50, 250);  //x,y begin the x,y end, sabet kol y
	gf.DrawLine(&pen, 100, 50, 100, 250);
	gf.DrawLine(&pen2, 150, 50, 150, 250);
	gf.DrawLine(&pen, 200, 50, 200, 250);
	gf.DrawLine(&pen, 250, 50, 250, 250);

	gf.DrawLine(&pen, 50, 50, 250, 50);  //x,y begin the x,y end,sabet kol x
	gf.DrawLine(&pen, 50, 100, 250, 100);
	gf.DrawLine(&pen2, 50, 150, 250, 150);
	gf.DrawLine(&pen, 50, 200, 250, 200);
	gf.DrawLine(&pen, 50, 250, 250, 250);
}
void drawHard(HDC hdc)
{
	Gdiplus::Graphics gf(hdc);
	Gdiplus::Pen pen(Gdiplus::Color(255, 0, 0, 225));               // For lines, rectangles and curves
	Gdiplus::Pen pen2(Gdiplus::Color(255, 255, 0, 0));
	gf.DrawLine(&pen, 20, 50, 20, 410);  //x,y begin the x,y end, sabet kol y
	gf.DrawLine(&pen, 60, 50, 60, 410);
	gf.DrawLine(&pen, 100, 50, 100, 410);
	gf.DrawLine(&pen2, 140, 50, 140, 410);
	gf.DrawLine(&pen, 180, 50, 180, 410);
	gf.DrawLine(&pen, 220, 50, 220, 410);
	gf.DrawLine(&pen2, 260, 50, 260, 410);
	gf.DrawLine(&pen, 300, 50, 300, 410);
	gf.DrawLine(&pen, 340, 50, 340, 410);
	gf.DrawLine(&pen, 380, 50, 380, 410);

	gf.DrawLine(&pen, 20, 50, 380, 50);  //x,y begin the x,y end,sabet kol x
	gf.DrawLine(&pen, 20, 90, 380, 90);
	gf.DrawLine(&pen, 20, 130, 380, 130);
	gf.DrawLine(&pen2, 20, 170, 380, 170);
	gf.DrawLine(&pen, 20, 210, 380, 210);
	gf.DrawLine(&pen, 20, 250, 380, 250);
	gf.DrawLine(&pen2, 20, 290, 380, 290);
	gf.DrawLine(&pen, 20, 330, 380, 330);
	gf.DrawLine(&pen, 20, 370, 380, 370);
	gf.DrawLine(&pen, 20, 410, 380, 410);
}

void AddMenus(HWND hWnd)
{
	hMenu = CreateMenu();
	HMENU hFileMenu = CreateMenu();
	HMENU hSubMenu = CreateMenu();

	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_Upload, "Upload from file");
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(hFileMenu, MF_STRING, FILE_MENU_EXIT, "Exit");

	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
	AppendMenu(hMenu, MF_STRING, NULL, "Help");
	SetMenu(hWnd, hMenu);
}
