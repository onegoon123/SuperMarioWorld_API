#include "Fire.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineResources.h>
#include "ContentsEnums.h"
#include "Particle.h"
#include "Map.h"
int Fire::Num = 0;

Fire::Fire() {
	Fire::Num++;
	ColMap = GameEngineResources::GetInst().ImageFind(Map::MainMap->GetStageColName());
}

Fire::~Fire() {
	Fire::Num--;
}

void Fire::Start()
{
	// ���� ����
	{
		AnimationRender = CreateRender(RenderOrder::Player);
		AnimationRender->SetScale({ 64, 64 });
		AnimationRender->CreateAnimation({ .AnimationName = "Defalut", .ImageName = "FIRE.BMP", .Start = 0, .End = 3, .InterTime = 0.07f });
	}
	AnimationRender->ChangeAnimation("Defalut");

	// Collision ����
	{
		BodyCollision = CreateCollision(CollisionOrder::PlayerAttack);
		BodyCollision->SetScale({ 32, 32 });
		BodyCollision->SetPosition({ 0, 0 });
		BodyCollision->SetDebugRenderType(CollisionType::CT_Rect);
	}
}

void Fire::Update(float _DeltaTime)
{
	//SetMove(Dir * Speed * _DeltaTime);


	// ȭ�� ������ �������� üũ
	float4 InCameraPos = GetPos() - GetLevel()->GetCameraPos();
	if (0 > InCameraPos.x + 10)
	{
		// ȭ�� ������ ������ ����
		Death();
	}
	if (GameEngineWindow::GetScreenSize().x < InCameraPos.x - 10)
	{ 
		// ȭ�� ������ ������ ����
		Death();
	}

	// ���� ������ �޾Ҵ��� üũ
	std::vector<GameEngineCollision*> Collisions;
	CollisionCheckParameter Check = { .TargetGroup = static_cast<int>(CollisionOrder::Monster), .TargetColType = CT_Rect, .ThisColType = CT_Rect };
	if (true == BodyCollision->Collision(Check, Collisions))
	{
		Collisions[0]->GetActor()->Death();
		Particle::CreateParticle(GetLevel(), GetPos(), "SMOKE1");
		Death();
	}

	MoveCalculation(_DeltaTime);
}

void Fire::MoveCalculation(float _DeltaTime)
{
	// ���� ��ġ
	//float4 DownPos = GetPos() + float4::Down * 10;
	// MoveDir �߷� ����
	if (true == IsSlope)
	{
		MoveDir += float4::Down * GravityAcceleration * 2 * _DeltaTime;
	}
	else
	{
		MoveDir += float4::Down * GravityAcceleration * _DeltaTime;
	}
	// MoveDir �ӵ� ����
	
	// ���� �߷��� �ִ� �߷��� �ʰ��� ���
	if (GravityMax < MoveDir.y)
	{
		// �ִ� �߷� ����
		MoveDir.y = GravityMax;
	}

	// �̹� �����ӿ� �̵��� ��ġ
	float4 NextPos = GetPos() + MoveDir * _DeltaTime;

	// ______�� �浹 üũ______

	if (nullptr == ColMap)
	{
		MsgAssert("�浹�� �� �̹����� �����ϴ�.");
	}
	
	// �� �浹 üũ�� �÷� ����
	DWORD PixelColor = ColMap->GetPixelColor(NextPos, RGB(255, 255, 255));
	float4 ForwardPos = NextPos;
	ForwardPos.y = GetPos().y - 4;
	// �� üũ
	if (RGB(0, 0, 0) == ColMap->GetPixelColor(ForwardPos, RGB(255, 255, 255)))
	{
		Particle::CreateParticle(GetLevel(), GetPos(), "SMOKE1");
		Death();
	}

	// �ٴ� üũ
	if (RGB(0, 0, 0) == PixelColor)
	{
		IsSlope = false;
		NextPos.y = std::round(NextPos.y);
		// �ٴڿ��� ���� ���� �ö󰣴�
		while (true)
		{
			NextPos.y -= 1;
			PixelColor = ColMap->GetPixelColor(NextPos, RGB(0, 0, 0));
			if (RGB(0, 0, 0) != PixelColor)
			{
				SetPos(NextPos);
 				MoveDir.y = -JumpForce;
				break;
			}
		}
	}
	// �Ʒ����� ����Ǵ� ��ϵ� üũ ex) ����
	if (RGB(0, 255, 0) == PixelColor)
	{
		IsSlope = false;
		NextPos.y = std::round(NextPos.y);
		// �ٴڿ��� ���� ���� �ö󰣴�
		while (true)
		{
			NextPos.y -= 1;
			PixelColor = ColMap->GetPixelColor(NextPos, RGB(0, 0, 0));
			if (RGB(255, 255, 255) == PixelColor)
			{
				SetPos(NextPos);
				MoveDir.y = -JumpForce;
				break;
			}
		}
	}
	// ��Ż�� üũ
	else if (RGB(255, 0, 0) == PixelColor)
	{
		bool Check = false;
		float4 SlopePos = NextPos;
		SlopePos.x += 5;
		SlopePos.y -= 5;
		PixelColor = ColMap->GetPixelColor(SlopePos, RGB(0, 0, 0));
		// ���ΰ� ������
		if (RGB(255, 0, 0) == PixelColor)
		{
			if (0 < MoveDir.x)
			{
				Check = true;
			}
		}
		// ���ΰ� ����
		else
		{
			if (0 > MoveDir.x)
			{
				Check = true;
			}
		}

		if (true == Check)
		{
			IsSlope = true;
			NextPos.y = std::round(NextPos.y);
			// �ٴڿ��� ���� ���� �ö󰣴�
			while (true)
			{
				NextPos.y -= 1;
				PixelColor = ColMap->GetPixelColor(NextPos, RGB(0, 0, 0));
				if (RGB(255, 255, 255) == PixelColor)
				{
					SetPos(NextPos);
					MoveDir.y = -SlopeJumpForce;
					break;
				}
			}
			NextPos.x += 1;
		}
	}
	
	SetMove(MoveDir * _DeltaTime);
}

void Fire::Render(float _DeltaTime)
{
	//BodyCollision->DebugRender();
}
