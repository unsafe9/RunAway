#ifndef _DEFINE_H_
#define _DEFINE_H_

#include<Windows.h>

namespace Core
{
	// 결과 타입
	typedef enum RESULT
	{
		res_success		= 0x0001,
		res_null		= 0x0000,
		res_overflow	= -0x0001,
		res_underflow	= -0x0002
	}RESULT;
	inline bool failed(RESULT res)
	{ 
		return (res <= 0); 
	}
	inline bool succeeded(RESULT res)
	{ 
		return (res > 0); 
	}

	// 플래그(비트연산으로 인수를 전달)
	typedef DWORD Flags;

	// 사각형범위
	typedef struct Rect
	{
		int bottom, left, right, top;
		Rect(void){}
		Rect(int bottom, int left, int right, int top) :
			bottom(bottom), left(left), right(right), top(top){}
		inline bool operator==(const Rect &rect) const
		{
			return rect.bottom == bottom && rect.left == left &&
				rect.right == right && rect.top == top;
		}
		inline bool operator!=(const Rect &rect) const
		{
			return rect.bottom != bottom || rect.left != left ||
				rect.right != right || rect.top != top;
		}
		Rect& set(int bottom, int left, int right, int top)
		{
			this->bottom	= bottom;
			this->left		= left;
			this->right		= right;
			this->top		= top;
			return *this;
		}
		Rect& set(const Rect &rect)
		{
			bottom	= rect.bottom;
			left	= rect.left;
			right	= rect.right;
			top		= rect.top;
			return *this;
		}
	}Rect, *PRECT;

	// 좌표
	typedef struct Pos
	{
		int x, y;

		Pos(void){}
		Pos(int x, int y) : x(x), y(y){}
		inline bool operator==(const Pos &pos) const
		{
			return (pos.x == x && pos.y == y);
		}
		inline bool operator!=(const Pos &pos) const
		{
			return (pos.x != x || pos.y != y);
		}
		inline Pos operator-(const Pos &pos) const
		{
			return Pos(x - pos.x, y - pos.y);
		}
		inline Pos operator+(const Pos &pos) const
		{
			return Pos(x + pos.x, y + pos.y);
		}
		inline Pos operator*(const Pos &pos) const
		{
			return Pos(x * pos.x, y * pos.y);
		}
		inline Pos& operator-=(const Pos &pos)
		{
			x -= pos.x; y -= pos.y;
			return *this;
		}
		inline Pos& operator+=(const Pos &pos)
		{
			x += pos.x; y += pos.y;
			return *this;
		}
		inline Pos& operator*=(const Pos &pos)
		{
			x *= pos.x; y += pos.y;
			return *this;
		}
	}Pos, *PPOS;

	// 방향(0~7)
	typedef enum Direction
	{
		dir_stop		= 0, // 정지
		//dir_lower_left  = 1, // 좌하
		dir_down		= 2, // 하
		//dir_lower_right	= 3, // 우하
		dir_left		= 4, // 좌
		dir_right		= 6, // 우
		//dir_upper_left	= 7, // 좌상
		dir_up			= 8, // 상
		//dir_upper_right	= 9  // 우상
	}Direction;
}

#endif