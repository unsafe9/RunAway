#include<iostream>

#include"Console.h"

#pragma warning(disable:4996)

using namespace Core;

static Core::CursorType cursorType;

HANDLE getHandle(void)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (handle == INVALID_HANDLE_VALUE)
		throw std::exception("failed to get standard output handle");
	return handle;
}
void Core::setCursorPos(const Pos &pos)
{
	COORD dwCursorPosition = { pos.x, pos.y };
	if (!SetConsoleCursorPosition(getHandle(), dwCursorPosition))
		throw std::exception("failed to set console cursor position");
}
Pos Core::getCursorPos(void)
{
	CONSOLE_SCREEN_BUFFER_INFO bufInfo;
	if (!GetConsoleScreenBufferInfo(getHandle(), &bufInfo))
		throw std::exception("failed to get console screen buffer info");
	return Pos(bufInfo.dwCursorPosition.X, bufInfo.dwCursorPosition.Y);
}

void Core::setCursorType(CursorType type)
{
	CONSOLE_CURSOR_INFO curInfo;
	switch (cursorType = type)
	{
	case cursor_unvisible:
		curInfo.dwSize = 1;
		curInfo.bVisible = FALSE;
		break;
	case cursor_input:
		curInfo.dwSize = 100;
		curInfo.bVisible = TRUE;
		break;
	case cursor_normal:
		curInfo.dwSize = 20;
		curInfo.bVisible = TRUE;
		break;
	}
	if (!SetConsoleCursorInfo(getHandle(), &curInfo))
		throw std::exception("failed to set console cursor info");
}
CursorType Core::getCursorType(void)
{
	return cursorType;
}

void Core::setTextColor(Color color)
{
	if (color != NOW_COLOR && color != NONE)
	{
		if (!SetConsoleTextAttribute(getHandle(), getBgColor() * 16 + color))
			throw std::exception("failed to set console text attribute");
	}
}
Color Core::getTextColor(void)
{
	CONSOLE_SCREEN_BUFFER_INFO bufInfo;
	if (!GetConsoleScreenBufferInfo(getHandle(), &bufInfo))
		throw std::exception("failed to get console screen buffer info");
	return static_cast<Color>(bufInfo.wAttributes % 16);
}
void Core::setBgColor(Color color)
{
	if (color != NOW_COLOR && color != NONE)
	{
		if (!SetConsoleTextAttribute(getHandle(), color * 16 + getTextColor()))
			throw std::exception("failed to set console text attribute");
	}
}
Color Core::getBgColor(void)
{
	CONSOLE_SCREEN_BUFFER_INFO bufInfo = { 0, };
	if (!GetConsoleScreenBufferInfo(getHandle(), &bufInfo))
		throw std::exception("failed to get console screen buffer info");
	return static_cast<Color>(bufInfo.wAttributes / 16);
}

void Core::setConSize(int cols, int lines)
{
	char buf[255] = { 0, };
	sprintf(buf, "mode con cols=%d lines=%d", cols, lines);
	system(buf);
}

void Core::clearRect(const Rect &rect)
{
	Pos pos(rect.left, rect.top);
	for (; pos.y <= rect.bottom; pos.y++)
	{
		gotoxy(pos);
		for (int j = rect.left; j < rect.right; j++)
			printf(" ");
	}
}

void Core::draw(const Pos &pos, int resource, const char *pszCh, int space, Color color)
{
	// 콘솔 윈도우의 핸들값을 얻음
	HWND hWnd = GetConsoleWindow();
	if (hWnd == NULL)
		throw std::exception("failed to get console window handle");
	HINSTANCE hInst = GetModuleHandleA(NULL);
	if (hInst == NULL)
		throw std::exception("failed to get module handle");
	
	HDC hDC = GetDC(NULL);
	if (hDC == NULL)
		throw std::exception("failed to get device context");
	HDC hMemDC = CreateCompatibleDC(hDC);
	if (hMemDC == NULL)
		throw std::exception("failed to create compatible device context");
	HBITMAP hBitmap = LoadBitmapA(hInst, MAKEINTRESOURCEA(resource));
	if (hBitmap == NULL)
		throw std::exception("failed to load bitmap");
	BITMAP bitmap;

	if (GetObjectA(hBitmap, sizeof(BITMAP), &bitmap) == NULL)
		throw std::exception("failed to get bitmap object");
	SelectObject(hMemDC, hBitmap);

	int height = bitmap.bmHeight + pos.y;
	int width = bitmap.bmWidth + pos.x;

	Color oriColor = getTextColor();
	if (color != NONE)
		setTextColor(color);
	for (int i = pos.y; i < height; i++)
	{
		gotoxy(Pos(pos.x, i));
		for (int j = pos.x; j < width; j++)
		{
			COLORREF colorRef = GetPixel(hMemDC, j - pos.x, i - pos.y);
			if (color == NONE)
			{
				switch (colorRef)
				{
				case RGB(0, 0, 0):
					setTextColor(WHITE); break;
				case RGB(255, 0, 0):
					setTextColor(LIGHTRED); break;
				case RGB(0, 255, 0):
					setTextColor(LIGHTGREEN); break;
				case RGB(0, 0, 255):
					setTextColor(LIGHTBLUE); break;
				case RGB(255, 255, 0):
					setTextColor(LIGHTYELLOW); break;
				case RGB(0, 255, 255):
					setTextColor(LIGHTSKYBLUE); break;
				case RGB(255, 0, 255):
					setTextColor(LIGHTPURPLE); break;
				default:
					for (int k = 0; k < space; k++)
						printf(" ");
					continue;
				}
				printf("%s", pszCh);
			}
			else
			{
				if (colorRef == RGB(0, 0, 0))
					printf("%s", pszCh);
				else
				{
					for (int k = 0; k < space; k++)
						printf(" ");
				}
			}
		}
	}
	setTextColor(oriColor);
	DeleteObject(hBitmap);
	DeleteDC(hMemDC);
	ReleaseDC(hWnd, hDC);
}
