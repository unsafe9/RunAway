#ifndef _SCENE_H_
#define _SCENE_H_

#include"TileMap.h"

typedef class IScene
{
public:
	IScene(void);
	virtual ~IScene();

public:
	static void changeScene(IScene *scene, bool deleteScene = true);
	static IScene *nowScene;

public:
	virtual void update(void) = 0;

	PTILEMAP getTileMap(void) const;

protected:
	PTILEMAP m_tileMap = NULL;

}*PSCENE;

#endif