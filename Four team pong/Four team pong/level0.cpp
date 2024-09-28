/*
* Program name: "Four Team Pong"
* (c) Programmer Stuff, 2023
* Governed under Apache 2.0, you are free to modify and use with minimal limitation.
* Refer to LICENSE.txt or http://www.apache.orColor.y/licenses/LICENSE-2.0.
*/

#include "level0.h"
#include "ProgDefs.h"

//effectively acts as a constColor.xuctor
void level0::load()
{
	this->paused = false;
	srand((unsigned)time(0));
	this->mousePos = D2D1::Point2L(0, 0);

	//sets up all the colors
	this->lColor = D2D1::Vector4F(1.0f, 0.0f, 0.0f, 1.0f);
	this->tColor = D2D1::Vector4F(0.0f, 1.0f, 0.0f, 1.0f);
	this->rColor = D2D1::Vector4F(1.0f, 1.0f, 0.0f, 1.0f);
	this->bColor = D2D1::Vector4F(0.0f, 0.0f, 1.0f, 1.0f);


	this->ballPos = D2D1::Vector2F(100.0f, 545.0f);
	this->ballColor = D2D1::Vector4F(1.0f, 1.0f, 1.0f, 1.0f); //rColor.yba -> xyzw
	this->ballVelocity = D2D1::Vector2F(rand() % 5 + 5, rand() % 10 - 5);
	
	
	this->ballCurrentTerritory = 0;

	this->lp = D2D1::Vector2F(50.0f, 500.0f);
	this->tp = D2D1::Vector2F(800.0f, 50.0f);
	this->rp = D2D1::Vector2F(1640.0f, 500.0f);
	this->bp = D2D1::Vector2F(800.0f, 985.0f);

	this->paddlesAlive = 4;
	this->ballHoldTimer = 0;
	this->pauseDebounce = 0;
}


//acts as an deconstructor
void level0::unload() 
{

}

//Change all the physics, move paddles, calculate score, etc.
void level0::update()
{
	if (alivePaddles[0]) 
	{
		GetCursorPos(&this->mousePos);
		//the double->long conversion is intentional
#pragma warning(push)
#pragma warning(disable: 4244)
		this->lp.y = this->mousePos.y - 50.0;
#pragma warning(pop)
	}

	if (GetAsyncKeyState(VK_ESCAPE) && pauseDebounce == 0) {
		pauseDebounce = debounceTime;
		if (paused) {
			paused = false;
		}
		else {
			paused = true;
		}
	}
	//collision detection ----
	//"Look ahead" in which see if next intended position is inside another object
	float IntendedPosX = this->ballPos.x + this->ballVelocity.x;
	float IntendedPosY = this->ballPos.y + this->ballVelocity.y;
	//right
	if (alivePaddles[2] && IntendedPosX >= this->rp.x && IntendedPosX <= (this->rp.x + paddleWidth + 5.0f + 50.0f) && IntendedPosY >= rp.y && IntendedPosY <= (rp.y + paddleHeight))
	{
		if (ballVelocity.x > 0.0f) 
		{
			this->ballVelocity.x = this->ballVelocity.x * -1.0f;
			this->ballVelocity.x-=2;
			this->scores[2]++;
			
			IntendedPosX = this->ballPos.x + this->ballVelocity.x;
		}
	}
	//left
	else if (alivePaddles[0] && IntendedPosX >= (this->lp.x - 50.0f) && IntendedPosX <= (this->lp.x + paddleWidth + 5.0f) && IntendedPosY >= lp.y && IntendedPosY <= (lp.y + paddleHeight))
	{
		if (ballVelocity.x < 0.0f)
		{
			this->ballVelocity.x = this->ballVelocity.x * -1.0f;
			this->ballVelocity.x+=2;
			this->scores[0]++;
			IntendedPosX = this->ballPos.x + this->ballVelocity.x;
		}
	}
	//top
	else if (alivePaddles[1] && IntendedPosX >= (this->tp.x - 50.0f) && IntendedPosX <= (this->tp.x + paddleHeight) && IntendedPosY >= tp.y && IntendedPosY <= (tp.y + paddleWidth + 5.0f))
	{
		if (ballVelocity.y < 0.0f)
		{
			this->ballVelocity.y = this->ballVelocity.y * -1.0f;
			this->ballVelocity.y+=2;
			this->scores[1]++;
			IntendedPosY = this->ballPos.y + this->ballVelocity.y;
		}
	}
	else if (alivePaddles[3] && IntendedPosX >= (this->bp.x - 50.0f) && IntendedPosX <= (this->bp.x + paddleHeight) && IntendedPosY >= bp.y && IntendedPosY <= (bp.y + paddleWidth + 5.0f))
	{
		if (ballVelocity.y > 0.0f)
		{
			this->ballVelocity.y = this->ballVelocity.y * -1.0f;
			this->ballVelocity.y-=2;
			this->scores[3]++;
			IntendedPosY = this->ballPos.y + this->ballVelocity.y;
		}
	}
	//Death pane collision detection
	//left pane
	if (!alivePaddles[0]  && IntendedPosX <= 50.0f && IntendedPosY >= 0.0f && IntendedPosY <= 1050.0f) 
	{
		if (ballVelocity.x < 0.0f)
		{
			ballVelocity.x -= 2.0f;
			this->ballVelocity.x = this->ballVelocity.x * -1.0f;
			IntendedPosX = this->ballPos.x + this->ballVelocity.x;
		}
	}
	//right
	else if (!alivePaddles[2] && IntendedPosX >= 1650.0f && IntendedPosX <= 1700.0f && IntendedPosY <= 1050.0f)
	{
		if (ballVelocity.x > 0.0f)
		{
			ballVelocity.x += 2.0f;
			this->ballVelocity.x = this->ballVelocity.x * -1.0f;
			IntendedPosX = this->ballPos.x + this->ballVelocity.x;
		}
	}
	//top
	else if (!alivePaddles[1] && IntendedPosX >= 0.0f && IntendedPosX <= 1700.0f && IntendedPosY <= 50.0f)
	{
		if (ballVelocity.y < 0.0f)
		{
			ballVelocity.y -= 2.0f;
			this->ballVelocity.y = this->ballVelocity.y * -1.0f;
			IntendedPosY = this->ballPos.y + this->ballVelocity.y;
		}
	}
	else if (!alivePaddles[3] && IntendedPosX >= 0.0f && IntendedPosX <= 1700.0f && IntendedPosY >= 1000.0f)
	{
		if (ballVelocity.y > 0.0f)
		{
			ballVelocity.y += 1.0f;
			this->ballVelocity.y = this->ballVelocity.y * -1.0f;
			IntendedPosY = this->ballPos.y + this->ballVelocity.y;
		}
	}


	//Check if ball is "dead"
	if (IntendedPosX < 0.0f && alivePaddles[0])
	{
		this->alivePaddles[0] = false;
		this->ballPos.x += 100;
		this->lColor.x = 0.5f;
		this->lColor.y = 0.5f;
		this->lColor.z = 0.5f;
		IntendedPosX = 100.0f;
		IntendedPosY = 525.0f;
		this->ballVelocity.x = this->ballVelocity.x * -1.0f;
		ballHoldTimer = ballHoldTime;
	}
	else if (IntendedPosX > 1650.0f && alivePaddles[2]) {
		this->alivePaddles[2] = false;
		this->ballPos.x -= 100;
		this->rColor.x = 0.5f;
		this->rColor.y = 0.5f;
		this->rColor.z = 0.5f;
		IntendedPosX = 1535.0f;
		IntendedPosY = 525.0f;
		this->ballVelocity.x = this->ballVelocity.x * -1.0f;
		ballHoldTimer = ballHoldTime;
	}
	else if (IntendedPosY < 0.0f && alivePaddles[1]) {
		this->alivePaddles[1] = false;
		this->ballPos.y += 100;
		this->tColor.x = 0.5f;
		this->tColor.y = 0.5f;
		this->tColor.z = 0.5f;
		IntendedPosX = 800.0f;
		IntendedPosY = 150.0f;
		this->ballVelocity.y = this->ballVelocity.y * -1.0f;
		ballHoldTimer = ballHoldTime;
	}
	else if (IntendedPosY > 1050.0f && alivePaddles[3]) {
		this->alivePaddles[3] = false;
		this->ballPos.y -= 100;
		this->bColor.x = 0.5f;
		this->bColor.y = 0.5f;
		this->bColor.z = 0.5f;
		IntendedPosX = 800.0f;
		IntendedPosY = 950.0f;
		this->ballVelocity.y = this->ballVelocity.y * -1.0f;
		ballHoldTimer = ballHoldTime;
	}



	//AI paddles ------------
	//do not update if paused
	if (!paused) {
		//right
		if (this->ballVelocity.x > 0.0f /* && this->ballPos.x  >= 800.0f */ && alivePaddles[2])
		{
			float target = this->ballPos.y - 50.0f;
			if (this->rp.y >= target) {
				if ((this->rp.y - target) > 25.0f)
				{
					this->rp.y -= 25.0f;
				}
				else
				{
					this->rp.y = target;
				}
			}
			else if (this->rp.y < target) {
				if (this->rp.y < target) {
					if ((target - this->rp.y) > 25.0f)
					{
						this->rp.y += 25.0f;
					}
					else
					{
						this->rp.y = target;
					}
				}
			}
		}
		else
			//if ball isn't in "active zone", do not respond.
		{
			if (this->rp.y >= 500.0f)
			{
				if ((rp.y - 500.0f) > 10.0f)
				{
					this->rp.y -= 10.0f;
				}
				else
				{
					this->rp.y = 500.0f;
				}
			}
			else if (this->rp.y < 500.0f)
			{
				if ((rp.y - 500.0f) < 10.0f)
				{
					this->rp.y += 10.0f;
				}
				else
				{
					this->rp.y = 500.0f;
				}
			}
		}

		//top paddle
		if (this->ballVelocity.y < 0.0f /* && this->ballPos.y <= 500.0f*/ && alivePaddles[1])
		{
			float target = this->ballPos.x - 50.0f;
			if (this->tp.x >= target) {
				if ((this->tp.x - target) > 25.0f)
				{
					this->tp.x -= 25.0f;
				}
				else
				{
					this->tp.x = target;
				}
			}
			else if (this->tp.x < target) {
				if (this->tp.x < target) {
					if ((target - this->tp.x) > 25.0f)
					{
						this->tp.x += 25.0f;
					}
					else
					{
						this->tp.x = target;
					}
				}
			}
		}
		else
		{
			if (this->tp.x >= 800.0f)
			{
				if ((tp.x - 800.0f) > 10.0f)
				{
					this->tp.x -= 10.0f;
				}
				else
				{
					this->tp.x = 800.0f;
				}
			}
			else if (this->tp.x < 800.0f)
			{
				if ((tp.y - 800.0f) < 10.0f)
				{
					this->tp.x += 10.0f;
				}
				else
				{
					this->tp.x = 800.0f;
				}
			}
		}

		//bottom paddle
		if (this->ballVelocity.y > 0.0f /* && this->ballPos.y > 500.0f*/ && alivePaddles[3])
		{
			float target = this->ballPos.x - 50.0f;
			if (this->bp.x >= target) {
				if ((this->bp.x - target) > 25.0f)
				{
					this->bp.x -= 25.0f;
				}
				else
				{
					this->bp.x = target;
				}
			}
			else if (this->bp.x < target) {
				if (this->bp.x < target) {
					if ((target - this->bp.x) > 25.0f)
					{
						this->bp.x += 25.0f;
					}
					else
					{
						this->bp.x = target;
					}
				}
			}
		}
		else
		{
			if (this->bp.x >= 800.0f)
			{
				if ((bp.x - 800.0f) > 10.0f)
				{
					this->bp.x -= 10.0f;
				}
				else
				{
					this->bp.x = 800.0f;
				}
			}
			else if (this->bp.x < 800.0f)
			{
				if ((bp.x - 800.0f) < 10.0f)
				{
					this->bp.x += 10.0f;
				}
				else
				{
					this->bp.x = 800.0f;
				}
			}
		}

		//updating ---
		//Clamp speed to 40 px/frame
#pragma warning(push)
#pragma warning(disable:4244)
		if (ballVelocity.x >= maxBallSpeed) ballVelocity.x = maxBallSpeed;
		if (ballVelocity.y >= floor(maxBallSpeed * .75)) ballVelocity.y = floor(maxBallSpeed * .75);
		if (ballVelocity.x <= -maxBallSpeed) ballVelocity.x = -maxBallSpeed;
		if (ballVelocity.y <= -floor(maxBallSpeed * .75)) ballVelocity.y = -floor(maxBallSpeed * .75);
#pragma warning(pop)		
		if (ballHoldTimer == 0)
		{
			this->ballColor.x = 1.0f;
			this->ballColor.z = 1.0f;
			this->ballColor.y = 1.0f;
			this->ballPos.x = IntendedPosX;
			this->ballPos.y = IntendedPosY;
		}
	}

	if (ballHoldTimer > 0)
	{
		ballColor.x = 1.0f;
		ballColor.z = 0.2f;
		ballColor.y = 0.2f;
		ballColor.w = 1.0f;
		ballHoldTimer--;
	}
	if (pauseDebounce > 0) pauseDebounce--;
}


int level0::render(MainGraphics* gameGraphics) 
{
	//Draw ball and paddles
	gameGraphics->clearScreen(D2D1::Vector3F(0.0f, 0.1f, 0.0f));
	gameGraphics->createCircle(this->ballPos, 5.0f, this->ballColor, 5.0f, true);	//ball
	gameGraphics->createSquare(lp, D2D1::Vector2F(paddleWidth, paddleHeight), lColor, 1.0f, true);	//left paddle
	gameGraphics->createSquare(tp, D2D1::Vector2F(paddleHeight, paddleWidth), tColor, 1.0f, true);	//top paddle
	gameGraphics->createSquare(rp, D2D1::Vector2F(paddleWidth, paddleHeight), rColor, 1.0f, true);	//right paddle
	gameGraphics->createSquare(bp, D2D1::Vector2F(paddleHeight, paddleWidth), bColor, 1.0f, true);	//bottom paddle

	//Draw "death panes" on the four cornering sides of the screen.
	gameGraphics->createSquare(D2D1::Vector2F(0.0f, 50.0f), D2D1::Vector2F(50.0f, 1000.0f), D2D1::Vector4F(this->lColor.x / 2, this->lColor.y / 2, this->lColor.z / 2, 0.7f), 1.0f, true);					//left pane
	gameGraphics->createSquare(D2D1::Vector2F(0.0f, 0.0f), D2D1::Vector2F(1654.0f, 50.0f), D2D1::Vector4F(this->tColor.x/2, this->tColor.y/2, this->tColor.z/2, 0.7f), 1.0f, true);					//top pane
	gameGraphics->createSquare(D2D1::Vector2F(1655.0f, 0.0f), D2D1::Vector2F(50.0f, 1000.0f), D2D1::Vector4F(this->rColor.x/2, this->rColor.y/2, this->rColor.z/2, 0.7f), 1.0f, true);				//right pane
	gameGraphics->createSquare(D2D1::Vector2F(51.0f, 1000.0f), D2D1::Vector2F(1654.0f, 50.0f), D2D1::Vector4F(this->bColor.x/2, this->bColor.y/2, this->bColor.z/2, 0.7f), 1.0f, true);				//bottom pane


	//Draw text labels;
	//Gets length of score integers; uses to create a text buffer for the actual text.
	int LScoreLen = scores[0] == 0 ? 1 : (scores[0] < 0 ? static_cast<int>(log10(std::abs(scores[0]))) + 1 : static_cast<int>(log10(scores[0])) + 1);
	int TScoreLen = scores[1] == 0 ? 1 : (scores[1] < 0 ? static_cast<int>(log10(std::abs(scores[1]))) + 1 : static_cast<int>(log10(scores[1])) + 1);
	int RScoreLen = scores[2] == 0 ? 1 : (scores[2] < 0 ? static_cast<int>(log10(std::abs(scores[2]))) + 1 : static_cast<int>(log10(scores[2])) + 1);
	int BScoreLen = scores[3] == 0 ? 1 : (scores[3] < 0 ? static_cast<int>(log10(std::abs(scores[3]))) + 1 : static_cast<int>(log10(scores[3])) + 1);
	int HrzVelLen = ballVelocity.x == 0 ? 1 : (ballVelocity.x < 0 ? static_cast<int>(log10(std::abs(ballVelocity.x))) + 1 : static_cast<int>(log10(ballVelocity.x)) + 1);
	int VrtVelLen = ballVelocity.y == 0 ? 1 : (ballVelocity.y < 0 ? static_cast<int>(log10(std::abs(ballVelocity.y))) + 1 : static_cast<int>(log10(ballVelocity.y)) + 1);
	if (ballVelocity.x < 0.0f) HrzVelLen++; //account for negative numbers
	if (ballVelocity.y < 0.0f) VrtVelLen++;
	//Create (empty) text buffer for future use.
	wchar_t* LScoreChar = new wchar_t[LScoreLen + 1];
	wchar_t* TScoreChar = new wchar_t[TScoreLen + 1];
	wchar_t* RScoreChar = new wchar_t[RScoreLen + 1];
	wchar_t* BScoreChar = new wchar_t[BScoreLen + 1];
	wchar_t* HrzVelChar = new wchar_t[HrzVelLen + 1];
	wchar_t* VrtVelChar = new wchar_t[VrtVelLen + 1];
	//Converts integers to stColor.xings, fills pre-allocated buffer.
	swprintf(LScoreChar, LScoreLen + 1, L"%d", scores[0]);
	swprintf(TScoreChar, TScoreLen + 1, L"%d", scores[1]);
	swprintf(RScoreChar, RScoreLen + 1, L"%d", scores[2]);
	swprintf(BScoreChar, BScoreLen + 1, L"%d", scores[3]);
	swprintf(HrzVelChar, HrzVelLen + 1, L"%d", static_cast<int>(ballVelocity.x));
	swprintf(VrtVelChar, VrtVelLen + 1, L"%d", static_cast<int>(ballVelocity.y));
	//Display buffer to screen.
	gameGraphics->drawText(D2D1::Vector2F(5.0f, 545.0f), D2D1::Vector2F(100.0f, 50.0f), D2D1::Vector4F(1.0f, 1.0f, 1.0f, 1.0f), LScoreLen + 1, LScoreChar, 1, 270.0f, D2D1::Vector2F(5.0f, 545.0f));
	gameGraphics->drawText(D2D1::Vector2F(835.0f, 5.0f), D2D1::Vector2F(100.0f, 50.0f), D2D1::Vector4F(1.0f, 1.0f, 1.0f, 1.0f), TScoreLen + 1, TScoreChar, 1, 0.0f, D2D1::Vector2F(835.0f, 5.0f));
	gameGraphics->drawText(D2D1::Vector2F(1700.0f, 545.0f), D2D1::Vector2F(100, 50.0f), D2D1::Vector4F(1.0f, 1.0f, 1.0f, 1.0f), RScoreLen + 1, RScoreChar, 1, 90.0f, D2D1::Vector2F(1700.0f, 545.0f));
	gameGraphics->drawText(D2D1::Vector2F(835.0f, 1000.0f), D2D1::Vector2F(100.0f, 50.0f), D2D1::Vector4F(1.0f, 1.0f, 1.0f, 1.0f), BScoreLen + 1, BScoreChar, 1, 0.0f, D2D1::Vector2F(835.0f, 1000.0f));
	gameGraphics->drawText(D2D1::Vector2F(1200.0f, 100.0f), D2D1::Vector2F(400.0f, 50.0f), D2D1::Vector4F(1.0f, 1.0f, 1.0f, 1.0f), 21, L"Ball horizontal vel: ", 1, 0.0f, D2D1::Vector2F(1400.0f, 100.0f));
	gameGraphics->drawText(D2D1::Vector2F(1200.0f, 150.0f), D2D1::Vector2F(400.0f, 50.0f), D2D1::Vector4F(1.0f, 1.0f, 1.0f, 1.0f), 20, L"Ball vertical vel: ", 1, 0.0f, D2D1::Vector2F(1400.0f, 150.0f));
	gameGraphics->drawText(D2D1::Vector2F(1475.0f, 100.0f), D2D1::Vector2F(100.0f, 50.0f), D2D1::Vector4F(1.0f, 0.5f, 0.5f, 1.0f), HrzVelLen + 1, HrzVelChar, 1, 0.0f, D2D1::Vector2F(1500.0f, 100.0f));
	gameGraphics->drawText(D2D1::Vector2F(1475.0f, 150.0f), D2D1::Vector2F(100.0f, 50.0f), D2D1::Vector4F(0.5f, 1.0f, 0.5f, 1.0f), VrtVelLen + 1, VrtVelChar, 1, 0.0f, D2D1::Vector2F(1500.0f, 100.0f));
	if (paused) {
		gameGraphics->createSquare(D2D1::Vector2F(750.0f, 470.0f), D2D1::Vector2F(200.0f, 200.0f), D2D1::Vector4F(1.0f, 0.2f, 0.2f, 0.8f), 1.0f, true);
		gameGraphics->drawText(D2D1::Vector2F(800.0f, 545.0f), D2D1::Vector2F(150.0f, 50.0f), D2D1::Vector4F(1.0f, 1.0f, 1.0f, 1.0f), 7, L"Paused", 1, 0, D2D1::Vector2F(835.0f, 545.0f));
		if (gameGraphics->ClickButton(D2D1::Vector2F(800.0f, 600.0f), D2D1::Vector2F(100.0f, 50.0f), D2D1::Vector4F(1.0f, 1.0f, 1.0f, 1.0f), 1, true)->Clicked)
		{
			return 1;
		}
		gameGraphics->drawText(D2D1::Vector2F(825.0f, 610.0f), D2D1::Vector2F(50.0f, 50.0f), D2D1::Vector4F(0.0f, 0.0f, 0.0f, 1.0f), 4, L"Menu", 2, 0, D2D1::Vector2F(850.0f, 650.0f));
	}
	//After-render cleanup.
	delete[] LScoreChar;
	delete[] TScoreChar;
	delete[] RScoreChar;
	delete[] BScoreChar;
	delete[] HrzVelChar;
	delete[] VrtVelChar;
	return -1;
}