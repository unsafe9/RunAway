#include<iostream>

#include"Console.h"
#include"Input.h"

#include"Scene.h"
#include"SceneMain.h"

using namespace Core;

void initConsole(void)
{
	// 윈도우 크기와 타이틀을 설정.
	setTitle("런어웨이 (RunAway)");
	setConSize(100, 40);

	// 윈도우를 화면 중심으로 맞춤.
	HWND hWnd = GetConsoleWindow();
	RECT rect;
	GetWindowRect(hWnd, &rect);
	SetWindowPos(hWnd, 0,
		GetSystemMetrics(SM_CXSCREEN) / 2 - (rect.right - rect.left) / 2,
		GetSystemMetrics(SM_CYSCREEN) / 2 - (rect.bottom - rect.top) / 2,
		0, 0, SWP_NOZORDER | SWP_NOSIZE);

	// 최대화버튼을 사용불가로 설정.
	SetWindowLongA(hWnd, GWL_STYLE, 
		GetWindowLongA(hWnd, GWL_STYLE) & ~WS_MAXIMIZEBOX);

	// 화면 색상과 커서를 설정.
	setBgColor(BLACK);
	setTextColor(WHITE);
	setCursorType(cursor_unvisible);
}

int main(void)
{
	initConsole();

	// 랜덤 시드 설정
	srand(static_cast<unsigned int>(GetTickCount()));
	try{
		IScene::changeScene(new SceneMain);
		// 메인루프
		while (IScene::nowScene != NULL)
		{
			updateKeyState();
			IScene::nowScene->update();
		}
	}
	catch (std::exception e){
		MessageBoxA(GetConsoleWindow(), e.what(), "exception", MB_OK);
		return 0;
	}

	return 0;
}
