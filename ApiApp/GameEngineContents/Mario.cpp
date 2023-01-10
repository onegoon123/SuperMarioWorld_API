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
	SetPos({ 150,750 });
	//SetMove(GameEngineWindow::GetScreenSize().half());
}

void Mario::Update()
{
	
	SetMove(float4::Right * 0.0001f);
}

void Mario::Render()
{
	float4 PlayerPos = GetPos();

	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("MARIO.BMP");

	GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, PlayerPos - float4{ 50, 50 }, { 100, 100 }, float4::Zero, Image->GetImageScale());

}