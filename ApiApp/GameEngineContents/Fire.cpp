#include "Fire.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnums.h"

int Fire::Num = 0;

Fire::Fire() {
	Fire::Num++;
}

Fire::~Fire() {
	Fire::Num--;
}

void Fire::Start()
{
	// 렌더 생성
	{
		AnimationRender = CreateRender(RenderOrder::Player);
		AnimationRender->SetScale({ 64, 64 });
		AnimationRender->CreateAnimation({ .AnimationName = "Defalut", .ImageName = "FIRE.BMP", .Start = 0, .End = 3, .InterTime = 0.07f });
	}
	AnimationRender->ChangeAnimation("Defalut");

	// Collision 생성
	{
		BodyCollision = CreateCollision(CollisionOrder::PlayerAttack);
		BodyCollision->SetScale({ 32, 32 });
		BodyCollision->SetPosition({ 0, 0 });
		BodyCollision->SetDebugRenderType(CollisionType::CT_Rect);
	}
}

void Fire::Update(float _DeltaTime)
{
	SetMove(Dir * Speed * _DeltaTime);


	// 화면 밖으로 나갔는지 체크
	float4 InCameraPos = GetPos() - GetLevel()->GetCameraPos();
	if (0 > InCameraPos.x)
	{
		// 화면 밖으로 나가면 제거
		Death();
	}
	if (GameEngineWindow::GetScreenSize().x < InCameraPos.x)
	{ 
		// 화면 밖으로 나가면 제거
		Death();
	}

	// 적이 공격을 받았는지 체크
	std::vector<GameEngineCollision*> Collisions;
	CollisionCheckParameter Check = { .TargetGroup = static_cast<int>(CollisionOrder::Monster), .TargetColType = CT_Rect, .ThisColType = CT_Rect };
	if (true == BodyCollision->Collision(Check, Collisions))
	{
		Collisions[0]->GetActor()->Death();
		Death();
	}
}

void Fire::Render(float _DeltaTime)
{
	//BodyCollision->DebugRender();
}
