#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include"Def.h"
#include<iostream>

namespace Core
{
	// 커서 위치 설정(gotoxy)
	void setCursorPos(const Pos &pos);
	inline void gotoxy(const Pos &pos)
	{
		setCursorPos(pos);
	}
	Pos getCursorPos(void);

	// 커서 타입
	typedef enum CursorType
	{
		cursor_unvisible,
		cursor_input,
		cursor_normal
	}CursorType;
	void setCursorType(CursorType type);
	CursorType getCursorType(void);

	// 색
	typedef enum Color
	{
		BLACK			= 0x0,	// 검정색
		BLUE			= 0x1,	// 파랑색
		GREEN			= 0x2,	// 초록색
		SKYBLUE			= 0x3,	// 옥색
		RED				= 0x4,	// 빨간색
		PURPLE			= 0x5,	// 자주색
		YELLOW			= 0x6,	// 노랑색
		WHITE			= 0x7,	// 흰색
		GRAY			= 0x8,	// 회색
		LIGHTBLUE		= 0x9,	// 연한 파랑색
		LIGHTGREEN		= 0xA,	// 연한 초록색
		LIGHTSKYBLUE	= 0xB,	// 연한 옥색
		LIGHTRED		= 0xC,	// 연한 빨간색
		LIGHTPURPLE		= 0xD,	// 연한 자주색
		LIGHTYELLOW		= 0xE,	// 연한 노랑색
		BRIGHTWHITE		= 0xF,	// 밝은 흰색
		NOW_COLOR		= -1,	// 현재 컬러
		NONE			= -2	// 지정하지 않음
	}Color;
	void setTextColor(Color color);
	Color getTextColor(void);
	void setBgColor(Color color);
	Color getBgColor(void);

	// 콘솔 크기 변경
	void setConSize(int cols, int lines);

	// 지운다
	void clearRect(const Rect &rect);

	// 출력한다
	template<typename T>
	void render(const Pos &pos, T source, Color color = getTextColor())
	{
		Color oriColor = getTextColor();

		gotoxy(pos);
		if (color != NOW_COLOR && color != NONE)
			setTextColor(color);
		std::cout << source;
		if (color != NOW_COLOR && color != NONE)
			setTextColor(oriColor);
	}
	// 그림을 printf로 그린다
	void draw(const Pos &pos, int resource, const char *pszCh, int space = 1, Color color = NONE);

	// 타이틀
	inline void setTitle(const char *pszText)
	{
		SetConsoleTitleA(pszText);
	}
	inline void getTitle(char *pBuf, int nSize)
	{
		GetConsoleTitleA(pBuf, nSize);
	}
}

#endif