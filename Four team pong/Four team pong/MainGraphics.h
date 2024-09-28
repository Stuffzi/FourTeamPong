#pragma once
#include <Windows.h>
#include <d2d1_1.h>
#include <chrono>
#include <ctime>
#include <thread>
#include <dwrite.h>
#include <cstdlib>
using namespace std::chrono_literals;

class MainGraphics
{
private:
	//factories from direct2d
	ID2D1Factory* gFactory;
	ID2D1HwndRenderTarget* gRendTarget;
	ID2D1SolidColorBrush* Brush;
	//ID2D1LinearGradientBrush* LinGradBrush;
	//ID2D1RadialGradientBrush* RadGradBrush;
	//ID2D1GradientStopCollection* LinGradStopCollection;
	IDWriteFactory* gWrite;
	IDWriteTextFormat* normCalibriTextFormat20;
	IDWriteTextFormat* normCalibriTextFormat35;
	IDWriteTextFormat* normCalibriTextFormat70;
	HDC deviceContext;
	POINT mousePos;

public:
	struct ClickButtonOutput {
		bool MouseHovering;
		bool Clicked;
	};
	struct Slider {
		float Value;
		bool isSelected;
	};
	ClickButtonOutput* COutput;
	Slider* slider;

	//setup and plumbing
	MainGraphics();
	~MainGraphics();

	bool gInit(HWND windHand);
	void startDraw();
	void endDraw();

	//shapes and graphics
	void clearScreen(D2D1_VECTOR_3F screenColor);
	void createCircle(D2D1_VECTOR_2F position, float rad, D2D1_VECTOR_4F circleColor, float thick, bool filled);
	void createSquare(D2D1_VECTOR_2F position, D2D1_VECTOR_2F size, D2D1_VECTOR_4F squareColor, float thick, bool filled);
	void drawText(D2D1_VECTOR_2F position, D2D1_VECTOR_2F size, D2D1_VECTOR_4F textColor, UINT32 charCount, const WCHAR* text, int FontCode, float rot, D2D1_VECTOR_2F CenterPos);
	MainGraphics::ClickButtonOutput* ClickButton(D2D1_VECTOR_2F position, D2D1_VECTOR_2F size, D2D1_VECTOR_4F buttonColor, float thick, bool filled);
	Slider* createSlider(D2D1_VECTOR_2F position, D2D1_VECTOR_2F frameSize, float frameThick, float sliderWid, float buffer, float startPos, D2D1_VECTOR_4F color);
};