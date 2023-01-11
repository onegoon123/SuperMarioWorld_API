#include "Mario.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineResources.h>

Mario::Mario() {

}

Mario::~Mario() {

}

void Mario::Start()
{
	SetMove(GameEngineWindow::GetScreenSize().half());
}

void Mario::Update()
{
	
	SetMove(float4::Right * 0.01f);
}

void Mario::Render()
{
	float4 PlayerPos = GetPos();

	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("MARIO.BMP");
	GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, 0, PlayerPos, {192, 192});

}