#include"SceneClear.h"

#include"Console.h"
#include"Input.h"

#include"resource.h"

#include"SceneMain.h"

using namespace Core;

#define iEND	0
#define iMAIN	1

#define drawOption(index, color)\
	draw(Pos(39 - (index)* 4, 30), 102 + (index), "бр", 2, color)
#define drawLeft(color)\
	render<const char*>(Pos(25, 32), "в╕", color)
#define drawRight(color)\
	render<const char*>(Pos(72, 32), "в║", color)

SceneClear::SceneClear(void)
{
	system("cls");
	draw(Pos(0, 0), Clear, "бс", 2);
	drawLeft(WHITE); drawRight(WHITE);
	drawOption(m_nowIndex, WHITE);
}
SceneClear::~SceneClear(){}

void SceneClear::update(void)
{
	if (trigger(VK_LEFT))
		drawLeft(LIGHTRED);
	if (trigger(VK_RIGHT))
		drawRight(LIGHTRED);
	if (release(VK_LEFT))
		drawLeft(WHITE);
	if (release(VK_RIGHT))
		drawRight(WHITE);

	if (repeat(VK_LEFT) || repeat(VK_RIGHT))
	{
		if (m_nowIndex == iMAIN)
		{
			clearRect(Rect(37, 35, 39, 30));
			clearRect(Rect(37, 58, 65, 30));
		}
		m_nowIndex = (m_nowIndex + 1) % 2;
		drawOption(m_nowIndex, WHITE);
	}
	else if (trigger(VK_SPACE))
	{
		drawOption(m_nowIndex, LIGHTRED);
		switch (m_nowIndex)
		{
		case iMAIN:
			changeScene(new SceneMain);
			break;
		case iEND:
			changeScene(NULL);
			break;
		}
	}
}