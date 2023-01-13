#include "Mario.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "MarioGameCore.h"

Mario::Mario() {

}

Mario::~Mario() {

}

void Mario::Start()
{
	// �������� ��� �����͸� �ҷ��´�
	MarioGameCore& GameCore = MarioGameCore::GetInst();
	MyState = GameCore.GetMarioStateData();
	StockState = GameCore.GetStockStateData();
	IsRidedYoshi = GameCore.GetRidedYoshiData();

	// ���� ��ġ ����
	SetMove(GameEngineWindow::GetScreenSize().half());

	// ���� ����
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