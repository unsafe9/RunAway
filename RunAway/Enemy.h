#ifndef _ENEMY_H_
#define _ENEMY_H_

#include"Character.h"

class IEnemy : public ICharacter
{
public:
	IEnemy(const Core::Pos &pos, DWORD dwMoveSpeedMS, char *myChar, int space, Core::Color color);
	virtual ~IEnemy() = 0{}

public:
	virtual void update(void);

public:
	bool m_moveResult = true;

};

#endif