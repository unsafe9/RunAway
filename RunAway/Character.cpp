#include"Character.h"

#include"Scene.h"
#include"Console.h"

using namespace Core;

ICharacter::ICharacter(const Core::Pos &pos, DWORD dwMoveSpeedMS, char *myChar, int space, Color color)
: m_dwMoveSpeedMS(dwMoveSpeedMS), m_myChar(myChar), m_space(space), m_color(color)
{
	m_pos = m_prevPos = pos;
}
ICharacter::~ICharacter(){}
inline Direction ICharacter::getDirection(void) const
{
	return m_dir;
}
inline Pos ICharacter::getPrevPos(void) const
{
	return m_prevPos;
}
inline int ICharacter::getSpace(void) const
{
	return m_space;
}
const char* ICharacter::getChar(void) const
{
	return m_myChar;
}
void ICharacter::clear(void) const
{
	clearRect(Rect(m_pos.y, m_pos.x * m_space, (m_pos.x + 1) * m_space, m_pos.y));
}
void ICharacter::render(void) const
{
	Pos pos(m_pos.x * m_space, m_pos.y);
	Core::render<const char*>(pos, m_myChar, m_color);
}
bool ICharacter::movable(const Pos &pos) const
{
	if (IScene::nowScene->getTileMap() != NULL)
		return (IScene::nowScene->getTileMap()->movable(pos));
	return false;
}
bool ICharacter::move(const Pos &pos)
{
	if (m_pos != pos)
	{
		int sx = m_pos.x - pos.x;
		int sy = m_pos.y - pos.y;
		int abs_sx = abs(sx);
		int abs_sy = abs(sy);
		if (abs_sx > abs_sy)
			m_dir = sx > 0 ? dir_left : dir_right;
		else
			m_dir = sy > 0 ? dir_up : dir_down;
	}
	if (movable(pos))
	{
		m_prevPos = m_pos;
		m_pos = pos;
		return true;
	}
	return false;
}
bool ICharacter::moveToward(const Pos &pos)
{
	Pos resPos = m_pos;

	int sx = m_pos.x - pos.x;
	int sy = m_pos.y - pos.y;
	if (sx == 0 && sy == 0)
		return false;
	int abs_sx = abs(sx);
	int abs_sy = abs(sy);

	if (abs_sx == abs_sy)
		rand() % 2 ? abs_sx++ : abs_sy++;
	if (abs_sx > abs_sy)
		sx > 0 ? resPos.x-- : resPos.x++;
	else
		sy > 0 ? resPos.y-- : resPos.y++;

	return move(resPos);
}
bool ICharacter::moveForward(void)
{
	Pos pos = m_pos;
	switch (m_dir)
	{
	case dir_up:	pos.y--; break;
	case dir_down:	pos.y++; break;
	case dir_left:	pos.x--; break;
	case dir_right:	pos.x++; break;
	}
	return move(pos);
}
bool ICharacter::moveBackward(void)
{
	Pos pos = m_pos;
	switch (m_dir)
	{
	case dir_up:	pos.y++; m_dir = dir_down;	break;
	case dir_down:	pos.y--; m_dir = dir_up;	break;
	case dir_left:	pos.x++; m_dir = dir_right;	break;
	case dir_right:	pos.x--; m_dir = dir_left;	break;
	}
	return move(pos);
}
bool ICharacter::moveRandom(void)
{
	Pos pos = m_pos;
	switch (m_dir = static_cast<Direction>(((rand() % 4) + 1) * 2))
	{
	case dir_up:	pos.y--; break;
	case dir_down:	pos.y++; break;
	case dir_left:	pos.x--; break;
	case dir_right:	pos.x++; break;
	}
	return move(pos);
}