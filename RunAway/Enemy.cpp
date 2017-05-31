#include"Enemy.h"
#include"User.h"

using namespace Core;

IEnemy::IEnemy(const Core::Pos &pos, DWORD dwMoveSpeedMS, char *myChar, int space, Color color)
: ICharacter(pos, dwMoveSpeedMS, myChar, space, color){}

void IEnemy::update(void)
{
	if (GetTickCount() - m_dwMoveTimer >= m_dwMoveSpeedMS)
	{
		clear();
		m_moveResult = m_moveResult ? moveToward(User::user->getPos()) : moveRandom();
		render();
		m_dwMoveTimer = GetTickCount();
	}
}