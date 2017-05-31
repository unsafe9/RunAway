#ifndef _INPUT_H_
#define _INPUT_H_

#include"Def.h"
#include<conio.h>

#define GC_UP 72
#define GC_LEFT 75
#define GC_RIGHT 77
#define GC_DOWN 80

namespace Core
{
	// 키 업데이트
	void updateKeyState(void);

	// 누를시 1회
	bool trigger(unsigned char key);
	// 누르고있을시 계속
	bool press(unsigned char key);
	// 누르고있으면 일정간격으로 반복
	bool repeat(unsigned char key);
	// 눌렀다 뗄시 실행
	bool release(unsigned char key);
	// 마우스 범위 판단
	bool mouseInArea(const Rect &rect);
	// 4방향 입력
	Direction dir4(void);
	// 8방향 입력
	//Direction dir8(void);
}

#endif
