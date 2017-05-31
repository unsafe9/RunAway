#ifndef _ENEMYMINION_H_
#define _ENEMYMINION_H_

#include"Enemy.h"

class EnemyMinion : public IEnemy
{
public:
	EnemyMinion(const Core::Pos &pos, Core::Color color);
	virtual ~EnemyMinion();

public:
	virtual void update(void);

private:
	Core::Direction m_prevDir = m_dir;

};


#endif