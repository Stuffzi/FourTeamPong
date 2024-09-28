/*
* Program name: "Four Team Pong"
* (c) Michael Burgin, 2023
* Governed under Apache 2.0, you are free to modify and use with minimal limitation.
* Refer to LICENSE.txt or http://www.apache.org/licenses/LICENSE-2.0.
*/

#include "MainGraphics.h"


MainGraphics::MainGraphics() 
{
	this->mousePos.x = NULL; 
	this->mousePos.y = NULL;
	//Makes sure that these arn't arbitrary numbers
	this->gFactory = NULL;
	this->gRendTarget = NULL;
	this->Brush = NULL;
	this->gWrite = NULL;
	//this->LinGradBrush = NULL;
	//this->RadGradBrush = NULL;
	this->deviceContext = NULL;
	this->gFactory = NULL;
	this->normCalibriTextFormat35 = NULL;
	this->normCalibriTextFormat20 = NULL;
	this->normCalibriTextFormat70 = NULL;
	//this->LinGradStopCollection = NULL;
	this->COutput = new ClickButtonOutput{ false, false };
	this->slider = new Slider{ 0.0f, false };
}


MainGraphics::~MainGraphics() 
{
	if (this->gFactory) this->gFactory->Release();
	if (this->gRendTarget) this->gRendTarget->Release();
	if (this->Brush) this->Brush->Release();
	//if (this->LinGradBrush) this->LinGradBrush->Release();
	//if (this->RadGradBrush) this->RadGradBrush->Release();
	if (this->gFactory) this->gFactory->Release();
	if (this->normCalibriTextFormat35) this->normCalibriTextFormat35->Release();
	if (this->normCalibriTextFormat20) this->normCalibriTextFormat20->Release();
	if (this->normCalibriTextFormat70) this->normCalibriTextFormat70->Release();
	//if (this->LinGradStopCollection) this->LinGradStopCollection->Release();
	delete COutput;
}


bool MainGraphics::gInit(HWND windHand) 
{

	//initialize the basic directX stuff
	HRESULT cFactRes = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &this->gFactory);
	if (cFactRes != S_OK) return false;

	//get client's screen size for fullscreen
	RECT dScreenSize;
	GetClientRect(windHand, &dScreenSize);

	cFactRes = this->gFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(
			windHand,
			D2D1::SizeU(dScreenSize.right, dScreenSize.bottom)
		),
		&this->gRendTarget
	);
	

	//create brushes

	if (cFactRes != S_OK) return false;

	cFactRes = this->gRendTarget->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f), &Brush); //NEW

	//create gradient brush ====
	/*
	D2D1_GRADIENT_STOP stops[] =
	{
		{ 0.0f, D2D1::ColorF(D2D1::ColorF::Cyan) },
		{ 1.0f, D2D1::ColorF(D2D1::ColorF::DarkBlue) }
	};
	
	this->gRendTarget->CreateGradientStopCollection(stops, 2, &this->LinGradStopCollection);

	D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES* linStopsProperties = {};
	this->gRendTarget->CreateLinearGradientBrush(linStopsProperties,  this->LinGradStopCollection, &this->LinGradBrush);
	*/
	//====

	if (cFactRes != S_OK) return false;

	cFactRes = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(gWrite), reinterpret_cast<IUnknown**>(&gWrite));

	if (cFactRes != S_OK) return false;

	this->gWrite->CreateTextFormat(L"Calibri", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 20.0f, L"en-us", &normCalibriTextFormat20);
	this->gWrite->CreateTextFormat(L"Calibri", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 35.0f, L"en-us", &normCalibriTextFormat35);
	this->gWrite->CreateTextFormat(L"Calibri", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 70.0f, L"en-us", &normCalibriTextFormat70);


	if (cFactRes != S_OK) return false;

	this->deviceContext = GetDC(windHand);

	return true;
}


//Not to be called by anything outside of MainGraphics.cpp
void MainGraphics::startDraw() 
{
	this->gRendTarget->BeginDraw();
}


//Same as aboth
void MainGraphics::endDraw() 
{
	this->gRendTarget->EndDraw();
}


//yet another janitorial function, do not call.
void MainGraphics::clearScreen(D2D1_VECTOR_3F screenColor) 
{
	this->gRendTarget->Clear(D2D1::ColorF(screenColor.x, screenColor.y, screenColor.z));
}


//if you want to fill the circle just set the thickness to 1. 
void MainGraphics::createCircle(D2D1_VECTOR_2F position, float rad, D2D1_VECTOR_4F circleColor, float thick, bool filled)
{
	this->Brush->SetColor(D2D1::ColorF(circleColor.x, circleColor.y, circleColor.z, circleColor.w));
	D2D1_ELLIPSE elli = D2D1::Ellipse(D2D1::Point2F(position.x, position.y), rad, rad);
	this->gRendTarget->DrawEllipse(&elli, Brush, thick);
	if (filled) this->gRendTarget->FillEllipse(&elli, this->Brush);
}


void MainGraphics::createSquare(D2D1_VECTOR_2F position, D2D1_VECTOR_2F size, D2D1_VECTOR_4F squareColor, float thick, bool filled)
{
	this->Brush->SetColor(D2D1::ColorF(squareColor.x, squareColor.y, squareColor.z, squareColor.w));
	D2D1_RECT_F rectangle = D2D1::Rect(position.x, position.y, position.x + size.x, position.y + size.y);
	this->gRendTarget->DrawRectangle(&rectangle, this->Brush, thick);
	if (filled) this->gRendTarget->FillRectangle(&rectangle, this->Brush);
}

//Takes in X, Y, Wid, Hgt to set a bounding box, then uses four colors to change the color. Then takes in the size of the buffer
//and a pointer to the array with the actual text it self. THEN it takes the amount you want it rotated and the midpoint that
//you want to rotate it around.
void MainGraphics::drawText(D2D1_VECTOR_2F position, D2D1_VECTOR_2F size, D2D1_VECTOR_4F textColor, UINT32 charCount, const WCHAR* text, int FontCode, float rot, D2D1_VECTOR_2F CenterPos)
{
	D2D1_RECT_F boxRect = D2D1::RectF(position.x, position.y, position.x + size.x, position.y + size.y);
	this->gRendTarget->SetTransform(D2D1::Matrix3x2F::Rotation(rot, D2D1::Point2F(CenterPos.x, CenterPos.y)));
	this->Brush->SetColor(D2D1::ColorF(textColor.x , textColor.y, textColor.z, textColor.w));
	switch (FontCode) {
	case 0:
		this->gRendTarget->DrawTextW(text, charCount, this->normCalibriTextFormat70, &boxRect, this->Brush, D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE_NATURAL);
		break;
	case 1:
		this->gRendTarget->DrawTextW(text, charCount, this->normCalibriTextFormat35, &boxRect, this->Brush, D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE_NATURAL);
		break;
	case 2:
		this->gRendTarget->DrawTextW(text, charCount, this->normCalibriTextFormat20, &boxRect, this->Brush, D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE_NATURAL);
		break;
	default:
		this->Brush->SetColor(D2D1::ColorF(1.0f, 0.0f, 0.0f, 1.0f));
		this->gRendTarget->DrawTextW(L"<Err Invalid FontCode>", 21, this->normCalibriTextFormat35, &boxRect, this->Brush, D2D1_DRAW_TEXT_OPTIONS_NONE, DWRITE_MEASURING_MODE_NATURAL);
		break;
	}

	this->gRendTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}


//Returns a struct with two options;
//Clicked, bool, true if it senses a mouseclick on itself
//MouseHovering, bool, true if mouse is hovering over but not nessasarily clicking.
//CAUTION: Check for clicks before checking for hovering. Otherwise you risk a odd flickering.
MainGraphics::ClickButtonOutput* MainGraphics::ClickButton(D2D1_VECTOR_2F position, D2D1_VECTOR_2F size, D2D1_VECTOR_4F buttonColor , float thick, bool filled)
{
	//visuals
	this->Brush->SetColor(D2D1::ColorF(buttonColor.x, buttonColor.y, buttonColor.z, buttonColor.w));
	D2D1_RECT_F rectangle = D2D1::Rect(position.x, position.y, position.x + size.x, position.y + size.y);
	this->gRendTarget->DrawRectangle(&rectangle, this->Brush, thick);
	if (filled) this->gRendTarget->FillRectangle(&rectangle, this->Brush);

	//mechanics
	GetCursorPos(&this->mousePos);
	if (this->mousePos.x >= position.x && this->mousePos.x <= (position.x + size.x) && this->mousePos.y >= position.y && this->mousePos.y <= (position.y + size.y))
	{
		COutput->MouseHovering = true;
		if (GetAsyncKeyState(VK_LBUTTON) & 1) 
		{
			COutput->Clicked = true;
		}
		else
		{
			COutput->Clicked = false;
		}
	}
	else
	{
		COutput->MouseHovering = false;
		COutput->Clicked = false;
	}
	return COutput;
}


MainGraphics::Slider* MainGraphics::createSlider(D2D1_VECTOR_2F position, D2D1_VECTOR_2F frameSize, float frameThick, float sliderWid, float buffer, float startPos, D2D1_VECTOR_4F color)
{
	return NULL;
}