#include<new>
#include<iostream>

#include"Scene.h"

// 현재 씬 정적멤버변수
IScene* IScene::nowScene = NULL;

// 생성자
IScene::IScene(void){}
// 소멸자
IScene::~IScene()
{
	if (m_tileMap != NULL)
		delete m_tileMap;
}
PTILEMAP IScene::getTileMap(void) const
{
	return m_tileMap;
}
// 씬변경 정적멤버함수
void IScene::changeScene(IScene *scene, bool deleteScene)
{
	if (nowScene != NULL && deleteScene)
		delete nowScene;
	nowScene = scene;
}