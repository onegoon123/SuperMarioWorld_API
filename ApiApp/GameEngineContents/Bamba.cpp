#include "Bamba.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "Map.h"
#include "Block.h"
#include "Particle.h"

Bamba::Bamba() {
}

Bamba::~Bamba() {

}

bool Bamba::IsCollisionAttack()
{
	return StateValue == State::Normal;
}

void Bamba::SpinHit()
{
	GameEngineResources::GetInst().SoundPlay("superstomp.wav");
	Death();
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

	Death();

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
		AnimationRender->SetScale(RenderScale);
		AnimationRender->CreateAnimation({ .AnimationName = "LEFT_WALK", .ImageName = "BAMBA.BMP", .Start = 0, .End = 1, .InterTime = 0.25f });
		AnimationRender->CreateAnimation({ .AnimationName = "RIGHT_WALK", .ImageName = "BAMBA.BMP", .Start = 2, .End = 3, .InterTime = 0.25f });
		AnimationRender->CreateAnimation({ .AnimationName = "LEFT_OVERTURN", .ImageName = "BAMBA.BMP", .Start = 4, .End = 5, .InterTime = 0.25f });
		AnimationRender->CreateAnimation({ .AnimationName = "RIGHT_OVERTURN", .ImageName = "BAMBA.BMP", .Start = 6, .End = 7, .InterTime = 0.25f });
		AnimationRender->ChangeAnimation("LEFT_WALK");
		AnimationRender->SetPosition(RenderPos);
	}
	// Collision 持失
	{
		Collision = CreateCollision(CollisionOrder::Monster);
		Collision->SetScale(CollisionScale);
		Collision->SetPosition(CollisionPos);
		Collision->SetDebugRenderType(CollisionType::CT_Rect);
	}
}

void Bamba::Update(float _DeltaTime)
{
	CameraInCheck();
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
	//Collision->DebugRender();
}

void Bamba::OffCamera()
{
	StateValue = State::Die;
}

void Bamba::OnCamera()
{
	StateValue = State::Normal;
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
