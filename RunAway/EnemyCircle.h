#ifndef _ENEMYCIRCLE_H_
#define _ENEMYCIRCLE_H_

#include"Enemy.h"

class EnemyCircle : public IEnemy
{
public:
	EnemyCircle(const Core::Pos &pos, Core::Color color);
	virtual ~EnemyCircle();

public:
	virtual void update(void);



};


#endif