#include<iostream>

#include"SceneMain.h"
#include"SceneSelHero.h"

#include"Console.h"
#include"Input.h"
#include"resource.h"

#define iSTART	0
#define iEND	1

using namespace Core;

#define drawOption(index, color)\
	draw(Pos(31 + (index) * 8, 30), 101 + (index), "бр", 2, color)
#define drawLeft(color)\
	render<const char*>(Pos(25, 32), "в╕", color)
#define drawRight(color)\
	render<const char*>(Pos(72, 32), "в║", color);

SceneMain::SceneMain(void)
{
	system("cls");
	draw(Pos(0, 0), Main, "бс", 2);
	drawLeft(WHITE); drawRight(WHITE);
	drawOption(m_nowIndex, WHITE);
}
SceneMain::~SceneMain()
{

}
void SceneMain::update(void)
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
		if (m_nowIndex == iSTART)
		{
			clearRect(Rect(37, 32, 36, 30));
			clearRect(Rect(37, 64, 68, 30));
		}
		m_nowIndex = (m_nowIndex + 1) % 2;
		drawOption(m_nowIndex, WHITE);
	}
	else if (trigger(VK_SPACE))
	{
		drawOption(m_nowIndex, LIGHTRED);
		switch (m_nowIndex)
		{
		case iSTART:
			changeScene(new SceneSelHero(5));
			break;
		case iEND:
			changeScene(NULL);
			break;
		}
	}
}