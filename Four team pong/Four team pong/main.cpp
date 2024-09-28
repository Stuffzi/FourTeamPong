/*
"Four Team Pong"
Built by ProgrammerStuff, 2023, copyrighted as such
Licensed under Apache 2.0, feel free to use in basically any context
Ver 0.5

Note: this code will only work on Windows or windows-emulation, as it
interfaces with the Windows API.
*/




#include <windows.h>
#include <d2d1_1.h>
#include <cmath>
#include "ProgDefs.h"
#include "MainGraphics.h"
#include "GameController.h"

#include "level0.h"
#include "Level1TitleScreen.h"
#include "Level2ConfigScreen.h"

//to stop bothering us about the winapi "potental loss of data!" warning
#pragma warning(push)
#pragma warning(disable: 4244)

LPCWSTR g_szClassName = L"myWindowClass";
MainGraphics* gameGraphics;

// Step 4: the Window Procedure
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		//REMEMBER: CLEANUP!
		DestroyWindow(hwnd);
		delete gameGraphics;
		std::exit(0);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{

	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;

	//Step 1: Registering the Window Class
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = g_szClassName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"Window Registration Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	//automatically compensate for the border, get true fullscreen.
	RECT screenRect = { 0, 0, defaultWidth, defaultHeight};
	AdjustWindowRectEx(&screenRect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);


	// Step 2: Creating the Window
	hwnd = CreateWindowEx(
		WS_EX_OVERLAPPEDWINDOW ^ WS_THICKFRAME,
		g_szClassName,
		WindowTitle,
		WS_OVERLAPPEDWINDOW,
		xOffset, yOffset, screenRect.right - screenRect.left, screenRect.bottom - screenRect.top,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL)
	{
		MessageBox(NULL, L"Window Creation Failed!", L"Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	
	gameGraphics = new MainGraphics();
	if (!gameGraphics->gInit(hwnd)) {
		delete gameGraphics;
		return -1;
	}
	
	GameController::loadInitialLevel(new Level1TitleScreen);

	ShowWindow(hwnd, SW_MAXIMIZE);
	UpdateWindow(hwnd);

	//message loop
	//----
	Msg.message = WM_NULL;
	while (Msg.message != WM_QUIT) {
		//deal with important messages first
		if (PeekMessage(&Msg, hwnd, 0, 0, PM_REMOVE)) {
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}
		else {
			//If doing nothing else important, do game calculations
			GameController::update();
			gameGraphics->startDraw();
			switch (GameController::render(gameGraphics))
			{
			case -1:
				//Do nothing for now, there's no switching.
				break;
			case 0:
				GameController::ChangeLevel(new level0);
				break;
			case 1:
				GameController::ChangeLevel(new Level1TitleScreen);
				break;
			case 2:
				GameController::ChangeLevel(new Level2ConfigScreen);
				break;
			default:
				//Same as -1
				break;
			}
			gameGraphics->endDraw();
		}
	}

	delete gameGraphics;
	return Msg.wParam;
}
#pragma warning(pop)