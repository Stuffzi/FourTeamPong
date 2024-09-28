#pragma once

//engine settings
//Window definitions
//-> I am assuming that the user has a 1440p monitor or better
#define WindowTitle L"Four Team Pong"
#define defaultWidth 2560				//default width/height of program
#define defaultHeight 1600				
#define xOffset 0						//distance of window corner from top right of monitor
#define yOffset 0 
#define defaultFont L"Calibri"
#define defaultFontSize 18.0f
#define debounceTime 5;					//Frames to ignore key inputs for debouncing


//place application-specific settings here
#define paddleHeight 100
#define paddleWidth 15
#define maxBallSpeed 40.0f
#define midX 800.0f
#define midY 500.0f
#define ballHoldTime 30;				//Hold for this many frames after a paddle death