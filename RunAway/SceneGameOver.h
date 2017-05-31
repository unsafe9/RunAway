#ifndef _SCENEGAMEOVER_H_
#define _SCENEGAMEOVER_H_

#include"Scene.h"

class SceneGameOver : public IScene
{
public:
	SceneGameOver(int stage);
	virtual ~SceneGameOver();

public:
	virtual void update(void);

private:
	int m_nowIndex = 2;
	int m_stage;

};

#endif