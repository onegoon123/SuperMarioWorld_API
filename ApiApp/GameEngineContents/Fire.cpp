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
	//SetMove(Dir * Speed * _DeltaTime);


	// 화면 밖으로 나갔는지 체크
	float4 InCameraPos = GetPos() - GetLevel()->GetCameraPos();
	if (0 > InCameraPos.x + 10)
	{
		// 화면 밖으로 나가면 제거
		Death();
	}
	if (GameEngineWindow::GetScreenSize().x < InCameraPos.x - 10)
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
		Particle::CreateParticle(GetLevel(), GetPos(), "SMOKE1");
		Death();
	}

	MoveCalculation(_DeltaTime);
}

void Fire::MoveCalculation(float _DeltaTime)
{
	// 밑의 위치
	//float4 DownPos = GetPos() + float4::Down * 10;
	// MoveDir 중력 증가
	if (true == IsSlope)
	{
		MoveDir += float4::Down * GravityAcceleration * 2 * _DeltaTime;
	}
	else
	{
		MoveDir += float4::Down * GravityAcceleration * _DeltaTime;
	}
	// MoveDir 속도 증가
	
	// 현제 중력이 최대 중력을 초과한 경우
	if (GravityMax < MoveDir.y)
	{
		// 최대 중력 제한
		MoveDir.y = GravityMax;
	}

	// 이번 프레임에 이동할 위치
	float4 NextPos = GetPos() + MoveDir * _DeltaTime;

	// ______맵 충돌 체크______

	if (nullptr == ColMap)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
	}
	
	// 맵 충돌 체크용 컬러 변수
	DWORD PixelColor = ColMap->GetPixelColor(NextPos, RGB(255, 255, 255));
	float4 ForwardPos = NextPos;
	ForwardPos.y = GetPos().y - 4;
	// 벽 체크
	if (RGB(0, 0, 0) == ColMap->GetPixelColor(ForwardPos, RGB(255, 255, 255)))
	{
		Particle::CreateParticle(GetLevel(), GetPos(), "SMOKE1");
		Death();
	}

	// 바닥 체크
	if (RGB(0, 0, 0) == PixelColor)
	{
		IsSlope = false;
		NextPos.y = std::round(NextPos.y);
		// 바닥에서 제일 위로 올라간다
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
	// 아래에서 통과되는 블록들 체크 ex) 구름
	if (RGB(0, 255, 0) == PixelColor)
	{
		IsSlope = false;
		NextPos.y = std::round(NextPos.y);
		// 바닥에서 제일 위로 올라간다
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
	// 비탈길 체크
	else if (RGB(255, 0, 0) == PixelColor)
	{
		bool Check = false;
		float4 SlopePos = NextPos;
		SlopePos.x += 5;
		SlopePos.y -= 5;
		PixelColor = ColMap->GetPixelColor(SlopePos, RGB(0, 0, 0));
		// 경사로가 오른쪽
		if (RGB(255, 0, 0) == PixelColor)
		{
			if (0 < MoveDir.x)
			{
				Check = true;
			}
		}
		// 경사로가 왼쪽
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
			// 바닥에서 제일 위로 올라간다
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
