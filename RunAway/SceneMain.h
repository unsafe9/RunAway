#ifndef _SCENEMAIN_H_
#define _SCENEMAIN_H_

#include"Scene.h"

#include"Console.h"

class SceneMain : public IScene
{
public:
	SceneMain(void);
	virtual ~SceneMain();

public:
	virtual void update(void);

private:
	int m_nowIndex = 0;

};

#endif