#include "Bamba.h"
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
Bamba::Bamba() {
}

Bamba::~Bamba() {

}

bool Bamba::IsCollisionAttack()
{
	return StateValue == State::Normal;
}

bool Bamba::IsHold()
{
	return StateValue == State::Hold || StateValue == State::Die;
}

void Bamba::SpinHit()
{
	GameEngineResources::GetInst().SoundPlay("superstomp.wav");
	Particle::CreateParticle(GetLevel(), GetPos(), "SMOKE1");
	Particle::CreateMovingParticle(GetLevel(), GetPos(), {450, -450}, "StarParticle", false, true, 0.5f);
	Death();
}

void Bamba::JumpHit()
{
	if (State::Overturn == StateValue)
	{
		//MoveDir.x += 100;
		return;
	}
	if (0 < MoveDir.x)
	{
		AnimationRender->ChangeAnimation("RIGHT_OVERTURN");
	}
	else
	{
		AnimationRender->ChangeAnimation("LEFT_OVERTURN");
	}
	StateValue = State::Overturn;

	//Death();

}

void Bamba::FireHit()
{
	GetLevel()->CreateActor<Coin>(RenderOrder::Item)->SetPos(GetPos());
	Death();
}

void Bamba::BlockHit()
{
	Death();
}

void Bamba::MonsterHit(bool IsLeft)
{

	// �ִϸ��̼� ����
	if (0 < DirValue.x)
	{
		if (State::Normal == StateValue)
		{
			AnimationRender->ChangeAnimation("RIGHT_IDLE");
		}
		else
		{
			AnimationRender->ChangeAnimation("RIGHT_OVERTURN_IDLE");
		}
		
	}
	else
	{
		if (State::Normal == StateValue)
		{
			AnimationRender->ChangeAnimation("LEFT_IDLE");
		}
		else
		{
			AnimationRender->ChangeAnimation("LEFT_OVERTURN_IDLE");
		}
	}

	// ���� ����
	StateValue = State::Die;
	MoveDir = MonsterHitForce;

	// �̵� ����
	if (true == IsLeft)
	{
		MoveDir.x *= -1;
	}
}

void Bamba::Hold()
{
	StateValue = State::Hold;
}

void Bamba::Kick(const float4& _Force)
{
	StateValue = State::Kick;
	MoveDir = _Force;
}

void Bamba::Start()
{
	EnemyActor::Start();
	Speed = BambaSpeed;
	SlopeSpeed = BambaSlopeSpeed;
	DirSetting(float4::Left);
	// ���� ����
	{
		AnimationRender = CreateRender(RenderOrder::Monster);
		AnimationRender->SetScale(RenderScale);
		AnimationRender->CreateAnimation({ .AnimationName = "LEFT_WALK", .ImageName = "BAMBA.BMP", .Start = 0, .End = 1, .InterTime = 0.25f });
		AnimationRender->CreateAnimation({ .AnimationName = "LEFT_IDLE", .ImageName = "BAMBA.BMP", .Start = 0, .End = 0,});
		AnimationRender->CreateAnimation({ .AnimationName = "RIGHT_WALK", .ImageName = "BAMBA.BMP", .Start = 2, .End = 3, .InterTime = 0.25f });
		AnimationRender->CreateAnimation({ .AnimationName = "RIGHT_IDLE", .ImageName = "BAMBA.BMP", .Start = 2, .End = 2,});
		AnimationRender->CreateAnimation({ .AnimationName = "LEFT_OVERTURN", .ImageName = "BAMBA.BMP", .Start = 4, .End = 5, .InterTime = 0.25f });
		AnimationRender->CreateAnimation({ .AnimationName = "LEFT_OVERTURN_IDLE", .ImageName = "BAMBA.BMP", .Start = 4, .End = 4,});
		AnimationRender->CreateAnimation({ .AnimationName = "RIGHT_OVERTURN", .ImageName = "BAMBA.BMP", .Start = 6, .End = 7, .InterTime = 0.25f });
		AnimationRender->CreateAnimation({ .AnimationName = "RIGHT_OVERTURN_IDLE", .ImageName = "BAMBA.BMP", .Start = 6, .End = 6, });
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

void Bamba::Update(float _DeltaTime)
{
	CameraInCheck();
	if (false == IsOnCamera) { return; }
	
	switch (StateValue)
	{
	case State::Normal:
		MoveUpdate(_DeltaTime);
		break;
	case State::Overturn:
		OverturnUpdate(_DeltaTime);
		break;
	case State::Hold:
		MonsterCheck();
		break;
	case State::Die:
		DieUpdate(_DeltaTime);
		break;
	case State::Kick:
		KickUpdate(_DeltaTime);
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
	IsOnCamera = false;
}

void Bamba::OnCamera()
{
	IsOnCamera = true;
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
	// �߷�
	MoveDir.y += GravityAcceleration * _DeltaTime;
	if (GravityMax < MoveDir.y)
	{
		MoveDir.y = GravityMax;
	}

	// �浹 �̹��� �˻�
	if (nullptr == ColMap)
	{
		MsgAssert("�浹�� �� �̹����� �����ϴ�.");
	}
	// �̵��� ��ġ
	float4 NextPos = GetPos() + MoveDir * _DeltaTime;
	float4 ForwardPos = NextPos;
	ForwardPos.y = GetPos().y + float4::Up.y;

	// �� �浹 üũ�� �÷� ����
	DWORD PixelColor = ColMap->GetPixelColor(ForwardPos, White);
	// �� üũ
	if (Black == PixelColor)
	{
		MoveDir.x = 0;
	}
	// �ٴ� üũ
	PixelColor = ColMap->GetPixelColor(NextPos, White);
	if (Black == PixelColor)
	{
		NextPos.y = std::round(NextPos.y);
		// �ٴڿ��� ���� ���� �ö󰣴�
		while (true)
		{
			NextPos += float4::Up;
			PixelColor = ColMap->GetPixelColor(NextPos, Black);
			if (Black != PixelColor)
			{
				SetPos(NextPos);
				MoveDir.y = 0;
				break;
			}
		}
	}
	// �Ʒ����� ����Ǵ� ��ϵ� üũ ex) ����
	else if (Green == PixelColor)
	{
		NextPos.y = std::round(NextPos.y);
		// �ٴڿ��� ���� ���� �ö󰣴�
		while (true)
		{
			NextPos += float4::Up;
			PixelColor = ColMap->GetPixelColor(NextPos, Black);
			if (White == PixelColor)
			{
				SetPos(NextPos);
				MoveDir.y = 0;
				break;
			}
		}
	}
	// ��Ż�� üũ
	else if (Red == PixelColor)
	{
		float4 SlopePos = NextPos;
		SlopePos += SlopeRightUp;
		PixelColor = ColMap->GetPixelColor(SlopePos, Black);
		NextPos.y = std::round(NextPos.y);
		// �ٴڿ��� ���� ���� �ö󰣴�
		while (true)
		{
			NextPos += float4::Up;
			PixelColor = ColMap->GetPixelColor(NextPos, Black);
			if (White == PixelColor)
			{
				SetPos(NextPos);
				MoveDir.y = 0;
				break;
			}
		}

	}

	// ��� üũ
	std::vector<GameEngineCollision*> Collisions;
	CollisionCheckParameter Check = { .TargetGroup = static_cast<int>(CollisionOrder::Block), .TargetColType = CT_Rect, .ThisColType = CT_Rect };
	if (true == Collision->Collision(Check, Collisions))
	{
		std::vector<GameEngineCollision*>::iterator Start = Collisions.begin();
		std::vector<GameEngineCollision*>::iterator End = Collisions.end();
		for (; Start != End; Start++)
		{
			Block* ColActor = (*Start)->GetOwner<Block>();
			if (true == ColActor->GetIsRoll())
			{
				continue;
			}
			// ���Ͱ� ��Ϻ��� ���� �ִ� ���
			if (GetPos().y < ColActor->GetPos().y - BlockYSize)
			{
				float4 Pos = GetPos();
				Pos.y = ColActor->GetPos().y - BlockOnPos;
				Pos.y = std::round(Pos.y);
				SetPos(Pos);
				MoveDir.y = 0.0f;
				continue;
			}
			else if (GetPos().y > ColActor->GetPos().y + BlockYSize)
			{
				MoveDir.x = 0;
				continue;
			}
			// �� �� ���
			else
			{
				MoveDir.x = 0;
			}
		}
	}

	SetMove(MoveDir * _DeltaTime);
	
}

void Bamba::KickUpdate(float _DeltaTime)
{	
	
	// ������ Overturn ���·� ��ȯ
	if (0.1f > abs(MoveDir.y) && 0.1f > abs(MoveDir.x))
	{
		MoveDir.x = 0;
		StateValue = State::Overturn;
	}

	// �̵� ����
	if (0 < MoveDir.x)
	{
		MoveDir.x -= _DeltaTime * 1000;
		MoveDir.x = std::max<float>(MoveDir.x - _DeltaTime, 0);
	}
	else if (0 > MoveDir.x)
	{
		MoveDir.x += _DeltaTime * 1000;
		MoveDir.x = std::min<float>(MoveDir.x + _DeltaTime, 0);
	}

	// �߷� ����
	MoveDir.y += GravityAcceleration * _DeltaTime;
	if (GravityMax < MoveDir.y)
	{
		MoveDir.y = GravityMax;
	}

	// �浹 �̹��� �˻�
	if (nullptr == ColMap)
	{
		MsgAssert("�浹�� �� �̹����� �����ϴ�.");
	}
	// �̵��� ��ġ
	float4 NextPos = GetPos() + MoveDir * _DeltaTime;
	float4 ForwardPos = NextPos;
	ForwardPos.y = GetPos().y + float4::Up.y;

	// �� �浹 üũ�� �÷� ����
	DWORD PixelColor = ColMap->GetPixelColor(ForwardPos, White);

	// �� üũ
	if (Black == PixelColor)
	{
		MoveDir.x = 0;
		return;
	}
	// �ٴ� üũ
	PixelColor = ColMap->GetPixelColor(NextPos, White);
	if (Black == PixelColor)
	{
		NextPos.y = std::round(NextPos.y);
		// �ٴڿ��� ���� ���� �ö󰣴�
		while (true)
		{
			NextPos += float4::Up;
			PixelColor = ColMap->GetPixelColor(NextPos, Black);
			if (Black != PixelColor)
			{
				SetPos(NextPos);
				MoveDir.y = 0;
				//StateValue = State::Overturn;
				return;
			}
		}
	}
	// �Ʒ����� ����Ǵ� ��ϵ� üũ ex) ����
	else if (Green == PixelColor && 0 < MoveDir.y)
	{
		NextPos.y = std::round(NextPos.y);
		// �ٴڿ��� ���� ���� �ö󰣴�
		while (true)
		{
			NextPos += float4::Up;
			PixelColor = ColMap->GetPixelColor(NextPos, Black);
			if (White == PixelColor)
			{
				SetPos(NextPos);
				MoveDir.y = 0;
				//StateValue = State::Overturn;
				return;
			}
		}
	}
	// ��Ż�� üũ
	else if (Red == PixelColor && 0 < MoveDir.y)
	{
		float4 SlopePos = NextPos;
		SlopePos += SlopeRightUp;
		PixelColor = ColMap->GetPixelColor(SlopePos, Black);
		NextPos.y = std::round(NextPos.y);
		// �ٴڿ��� ���� ���� �ö󰣴�
		while (true)
		{
			NextPos += float4::Up;
			PixelColor = ColMap->GetPixelColor(NextPos, Black);
			if (White == PixelColor)
			{
				SetPos(NextPos);
				MoveDir.y = 0;
				return;
			}
		}
		
	}

	// ��� üũ
	std::vector<GameEngineCollision*> Collisions;
	CollisionCheckParameter Check = { .TargetGroup = static_cast<int>(CollisionOrder::Block), .TargetColType = CT_Rect, .ThisColType = CT_Rect };
	if (true == Collision->Collision(Check, Collisions))
	{
		std::vector<GameEngineCollision*>::iterator Start = Collisions.begin();
		std::vector<GameEngineCollision*>::iterator End = Collisions.end();
		bool Hit = false;
		for (; Start != End; Start++)
		{
			Block* HitBlock = (*Start)->GetOwner<Block>();
			if (true == HitBlock->GetIsRoll())
			{
				continue;
			}
			// ���Ͱ� ��Ϻ��� ���� �ִ� ���
			if (GetPos().y < HitBlock->GetPos().y - BlockYSize)
			{
				// ������� ����
				float4 Pos = GetPos();
				Pos.y = HitBlock->GetPos().y - BlockOnPos;
				Pos.y = std::round(Pos.y);
				SetPos(Pos);
				MoveDir.y = 0.0f;
				continue;
			}
			// �ؿ��� ���� ģ ���
			else if (GetPos().y > HitBlock->GetPos().y)
			{
				// ����� ��Ʈ�Ѵ�
				Hit = true;
				HitBlock->Hit();
				// ��� ������ �̵��Ѵ�
				float4 Pos = GetPos();
				Pos.y = HitBlock->GetPos().y + BlockOnPos;
				Pos.y = std::round(Pos.y);
				SetPos(Pos);
				MoveDir.y = HeadingReaction;
			}
			// �� �� ��� (������ ģ ���)
			else
			{
				// ���⿡ ���� ��ġ �����Ѵ�

				if (GetPos().x < HitBlock->GetPos().x)
				{
					float4 Pos = GetPos();
					Pos.x = HitBlock->GetPos().x - BlockXSize - RenderScale.hx();
					Pos.x = std::round(Pos.x);
					SetPos(Pos);
				}
				else
				{
					float4 Pos = GetPos();
					Pos.x = HitBlock->GetPos().x + BlockXSize + RenderScale.hx();
					Pos.x = std::round(Pos.x);
					SetPos(Pos);
				}
				// ����� ��Ʈ�Ѵ�
				Hit = true;
				HitBlock->Hit();
			}
			
		}
		// ����� ��Ʈ�� ��� ȿ���� �� �¿� �̵� ����
		if (true == Hit)
		{
			MoveDir.x = 0;
			GameEngineResources::GetInst().SoundPlay("bump.wav");
			return;
		}
	}

	
	MonsterCheck();

	SetMove(MoveDir * _DeltaTime);

}

void Bamba::DieUpdate(float _DeltaTime)
{
	// �߷�
	MoveDir.y += GravityAcceleration * _DeltaTime;
	if (GravityMax < MoveDir.y)
	{
		MoveDir.y = GravityMax;
	}
	SetMove(MoveDir * _DeltaTime);

}

void Bamba::MonsterCheck()
{
	// ���� üũ
	std::vector<GameEngineCollision*> Collisions;
	CollisionCheckParameter Check = { .TargetGroup = static_cast<int>(CollisionOrder::Monster), .TargetColType = CT_Rect, .ThisColType = CT_Rect };
	if (true == Collision->Collision(Check, Collisions))
	{
		std::vector<GameEngineCollision*>::iterator Start = Collisions.begin();
		std::vector<GameEngineCollision*>::iterator End = Collisions.end();
		for (; Start != End; Start++)
		{
			EnemyActor* ColActor = (*Start)->GetOwner<EnemyActor>();
			if (this == ColActor)
			{
				continue;
			}
			if (true == ColActor->IsHold())
			{
				continue;
			}

			Mario::MainPlayer->DropHold();
			GameEngineResources::GetInst().SoundPlay("kick.wav");
			Particle::CreateParticle(GetLevel(), GetPos(), "KICK");

			if (ColActor->GetPos().x < GetPos().x)
			{
				ColActor->MonsterHit(true);
				MonsterHit(false);
			}
			else
			{
				ColActor->MonsterHit(false);
				MonsterHit(true);
			}
			return;
		}
	}
}
