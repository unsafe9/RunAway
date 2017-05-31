#ifndef _SCENESELHERO_H_
#define _SCENESELHERO_H_

#include"Scene.h"

#include"Console.h"

class SceneSelHero : public IScene
{
public:
	SceneSelHero(int stage);
	virtual ~SceneSelHero();

public:
	virtual void update(void);

private:
	int m_nowIndex;
	int m_stage;

};
#endif