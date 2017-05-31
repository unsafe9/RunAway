#ifndef _SCENEFIELD_H_
#define _SCENEFIELD_H_
	
#include"Scene.h"
	
#include"EnemyCircle.h"
#include"EnemyMinion.h"
	
class SceneField : public IScene
{
public:
	SceneField(int stage, int index);
	virtual ~SceneField();

public:
	virtual void update(void);

	inline int getStage(void) const
	{
		return m_stage;
	}
private:
	int m_stage = 1;
	int m_countEnemy = 0;
	time_t m_nextTimer;
	time_t m_timeRef = 0;
	DWORD m_dwMakeTimer = 0;

	struct Enemy
	{
		~Enemy()
		{
			if (enemy != NULL)
				delete enemy;
		}
		IEnemy *enemy = NULL;
		Enemy *next = NULL;
	}*enemiesHead = NULL, *enemiesTail = NULL;
};

#endif