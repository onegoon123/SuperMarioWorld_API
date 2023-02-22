#include "EnemyActor.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>
#include "Map.h"
#include "Block.h"
#include "ContentsEnums.h"

EnemyActor::EnemyActor() {

}

EnemyActor::~EnemyActor() {

}

void EnemyActor::Start()
{
	Collision = CreateCollision(CollisionOrder::Check);
	Collision->SetScale(CollisionScale);
}

void EnemyActor::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	ColMap = GameEngineResources::GetInst().ImageFind(Map::MainMap->GetStageColName());
}

void EnemyActor::CameraInCheck()
{
	// ȭ�� ������ �������� üũ
	float4 InCameraPos = GetPos() - GetLevel()->GetCameraPos();
	if (0 > InCameraPos.x + 100)
	{
		OffCamera();
	}
	else if (GameEngineWindow::GetScreenSize().x < InCameraPos.x - 100)
	{
		OffCamera();
	}
	else
	{
		OnCamera();
	}
}

void EnemyActor::MoveUpdate(float _DeltaTime)
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
		Turn();
		NextPos = GetPos() + MoveDir * _DeltaTime;
	}
	// �ٴ� üũ
	PixelColor = ColMap->GetPixelColor(NextPos, White);
	if (Black == PixelColor)
	{
		IsSlope = false;
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
		IsSlope = false;
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
		IsSlope = true;
		MoveDir.x = DirValue.x * SlopeSpeed;
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
				continue;
			}
			// �� �� ���
			else
			{
				Turn();
			}
		}
	}

	SetMove(MoveDir * _DeltaTime);

}

void EnemyActor::OffCamera()
{
	IsOnCamera = false;
}

void EnemyActor::OnCamera()
{
	IsOnCamera = true;
}

inline void EnemyActor::DirSetting(const float4& _DirValue)
{
	DirValue = _DirValue;
	MoveDir = DirValue * Speed;
}

inline void EnemyActor::Turn()
{
	DirValue = -DirValue;
	MoveDir = DirValue * Speed;
}

inline void EnemyActor::TurnLeft()
{
	DirValue = float4::Left;
	MoveDir = DirValue * Speed;
}

inline void EnemyActor::TurnRight()
{
	DirValue = float4::Right;
	MoveDir = DirValue * Speed;
}
