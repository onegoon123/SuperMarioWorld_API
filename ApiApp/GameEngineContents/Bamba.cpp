#include "Bamba.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "Map.h"
#include "Block.h"

Bamba::Bamba() {
}

Bamba::~Bamba() {

}

void Bamba::SpinHit()
{
}

void Bamba::JumpHit()
{
	if (0 < MoveDir.x)
	{
		AnimationRender->ChangeAnimation("RIGHT_OVERTURN");
	}
	else
	{
		AnimationRender->ChangeAnimation("LEFT_OVERTURN");
	}
	StateValue = State::Overturn;
}

void Bamba::FireHit()
{
}

void Bamba::BlockHit()
{
	Death();
}

void Bamba::Start()
{
	EnemyActor::Start();
	Speed = 100;
	SlopeSpeed = Speed * 0.6f;
	DirSetting(float4::Left);
	// 兄希 持失
	{
		AnimationRender = CreateRender(RenderOrder::Monster);
		AnimationRender->SetScale({ 64, 64 });
		AnimationRender->CreateAnimation({ .AnimationName = "LEFT_WALK", .ImageName = "BAMBA.BMP", .Start = 0, .End = 1, .InterTime = 0.25f });
		AnimationRender->CreateAnimation({ .AnimationName = "RIGHT_WALK", .ImageName = "BAMBA.BMP", .Start = 2, .End = 3, .InterTime = 0.25f });
		AnimationRender->CreateAnimation({ .AnimationName = "LEFT_OVERTURN", .ImageName = "BAMBA.BMP", .Start = 4, .End = 5, .InterTime = 0.25f });
		AnimationRender->CreateAnimation({ .AnimationName = "RIGHT_OVERTURN", .ImageName = "BAMBA.BMP", .Start = 6, .End = 7, .InterTime = 0.25f });
	}
	AnimationRender->ChangeAnimation("LEFT_WALK");
	AnimationRender->SetPosition({ 0, -28 });
	// Collision 持失
	{
		Collision = CreateCollision(CollisionOrder::Monster);
		Collision->SetScale({ 48, 32 });
		Collision->SetPosition({ 0, 12 });
		Collision->SetDebugRenderType(CollisionType::CT_Rect);
	}
	Collision->SetPosition({ 0, -20 });
}

void Bamba::Update(float _DeltaTime)
{
	switch (StateValue)
	{
	case State::Normal:
		MoveUpdate(_DeltaTime);
		break;
	case State::Overturn:
		break;
	case State::Hold:
		break;
	case State::Die:
		break;
	default:
		break;
	}
}

void Bamba::Render(float _DeltaTime)
{
	//BodyCollision->DebugRender();
}

void Bamba::Turn()
{
	EnemyActor::Turn();
	if (0 < DirValue.x)
	{
		AnimationRender->ChangeAnimation("RIGHT_WALK");
	}
	else
	{
		AnimationRender->ChangeAnimation("LEFT_WALK");
	}
}

void Bamba::TurnLeft()
{
	EnemyActor::TurnLeft();
	AnimationRender->ChangeAnimation("LEFT_WALK");
}

void Bamba::TurnRight()
{
	EnemyActor::TurnRight();
	AnimationRender->ChangeAnimation("RIGHT_WALK");
}

void Bamba::OverturnUpdate(float _DeltaTime)
{
}
