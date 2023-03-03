#include "Nokonoko.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"
#include "Map.h"
#include "Block.h"
#include "Particle.h"
#include "Mario.h"
#include "Coin.h"
#include "Shell.h"
Nokonoko::Nokonoko() {

}

Nokonoko::~Nokonoko() {

}

bool Nokonoko::IsCollisionAttack()
{
	return StateValue == NokoState::Normal || StateValue == NokoState::Naked;
}

bool Nokonoko::IsHold()
{
	return false;
}

bool Nokonoko::IsHoldable()
{
	return false;
}

void Nokonoko::SpinHit()
{
	GameEngineResources::GetInst().SoundPlay("superstomp.wav");
	Particle::CreateParticle(GetLevel(), GetPos(), "SMOKE1");
	Particle::CreateMovingParticle(GetLevel(), GetPos(), { 450, -450 }, "StarParticle", false, true, 0.5f);
	Death();
}

void Nokonoko::JumpHit(bool IsLeft)
{
	StateValue = NokoState::Overturn;
	GetLevel()->CreateActor<Shell>(RenderOrder::Monster)->SetPos(GetPos());
	Death();
}

void Nokonoko::FireHit()
{
}

void Nokonoko::BlockHit()
{
}

void Nokonoko::MonsterHit(bool IsLeft)
{
	// �ִϸ��̼� ����
	if (0 < DirValue.x)
	{
		AnimationRender->ChangeAnimation("RIGHT_IDLE");
	}
	else
	{
		AnimationRender->ChangeAnimation("LEFT_IDLE");
	}

	// ���� ����
	StateValue = NokoState::Die;
	MoveDir = MonsterHitForce;

	// �̵� ����
	if (true == IsLeft)
	{
		MoveDir.x *= -1;
	}
}

void Nokonoko::Hold()
{
	
}

void Nokonoko::Kick(const float4& _Force)
{
}

void Nokonoko::Start()
{
	EnemyActor::Start();
	Speed = ActorSpeed;
	SlopeSpeed = ActorSlopeSpeed;
	DirSetting(float4::Left);
	// ���� ����
	{
		AnimationRender = CreateRender(RenderOrder::Monster);
		AnimationRender->SetScale(RenderScale);
		AnimationRender->CreateAnimation({ .AnimationName = "LEFT_WALK", .ImageName = "LEFT_NOKONOKO.BMP", .Start = 0, .End = 1, .InterTime = 0.25f });
		AnimationRender->CreateAnimation({ .AnimationName = "LEFT_IDLE", .ImageName = "LEFT_NOKONOKO.BMP", .Start = 0, .End = 0, });
		AnimationRender->CreateAnimation({ .AnimationName = "RIGHT_WALK", .ImageName = "RIGHT_NOKONOKO.BMP", .Start = 2, .End = 3, .InterTime = 0.25f });
		AnimationRender->CreateAnimation({ .AnimationName = "RIGHT_IDLE", .ImageName = "RIGHT_NOKONOKO.BMP", .Start = 2, .End = 2,  });
		AnimationRender->ChangeAnimation("LEFT_WALK");
		AnimationRender->SetPosition(RenderPos);
	}
	// Collision ����
	{
		Collision = CreateCollision(CollisionOrder::Monster);
		Collision->SetScale(CollisionScale);
		Collision->SetPosition(CollisionPos);
		Collision->SetDebugRenderType(CollisionType::CT_Rect);
	}
}

void Nokonoko::Update(float _DeltaTime)
{
	CameraInCheck();
	if (false == IsOnCamera) {
		return;
	}

	switch (StateValue)
	{
	case NokoState::Normal:
		MoveUpdate(_DeltaTime);
		break;
	case NokoState::Overturn:
		OverturnUpdate(_DeltaTime);
		break;
	case NokoState::Naked:
		MoveUpdate(_DeltaTime);
		break;
	case NokoState::Die:
		DieUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Nokonoko::Render(float _DeltaTime)
{
	//Collision->DebugRender();
}

void Nokonoko::Turn()
{
	EnemyActor::Turn();
}

void Nokonoko::TurnLeft()
{
	EnemyActor::TurnLeft();
}

void Nokonoko::TurnRight()
{
	EnemyActor::TurnRight();
}

void Nokonoko::OverturnUpdate(float _DeltaTime)
{
}