#ifndef _SCENECLEAR_H_
#define _SCENECLEAR_H_

#include"Scene.h"

class SceneClear : public IScene
{
public:
	SceneClear(void);
	virtual ~SceneClear();

public:
	virtual void update(void);

private:
	int m_nowIndex = 1;

};

#endif