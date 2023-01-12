#include "Mario.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>

Mario::Mario() {

}

Mario::~Mario() {

}

void Mario::Start()
{
	SetMove(GameEngineWindow::GetScreenSize().half());
	{
		GameEngineRender* Render = CreateRender("MARIO.BMP", 0);
		Render->SetScale({ 192, 192 });
	}
}

void Mario::Update(float _DeltaTime)
{
	
	SetMove(float4::Right * Speed * _DeltaTime);
}

void Mario::Render(float _DeltaTime)
{

}