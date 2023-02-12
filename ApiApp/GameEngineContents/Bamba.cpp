#include "Bamba.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>
#include "ContentsEnums.h"
#include "Map.h"

Bamba::Bamba() {
	ColMap = GameEngineResources::GetInst().ImageFind(Map::MainMap->GetStageColName());
}

Bamba::~Bamba() {

}

void Bamba::Start()
{
	// 렌더 생성
	{
		AnimationRender = CreateRender(RenderOrder::Monster);
		AnimationRender->SetScale({ 64, 64 });
		AnimationRender->CreateAnimation({ .AnimationName = "LEFT_WALK", .ImageName = "BAMBA.BMP", .Start = 0, .End = 1, .InterTime = 0.25f });
		AnimationRender->CreateAnimation({ .AnimationName = "RIGHT_WALK", .ImageName = "BAMBA.BMP", .Start = 2, .End = 3, .InterTime = 0.25f });
	}
	AnimationRender->ChangeAnimation("LEFT_WALK");
	AnimationRender->SetPosition({ 0, -28 });
	// Collision 생성
	{
		BodyCollision = CreateCollision(CollisionOrder::Monster);
		BodyCollision->SetScale({ 48, 32 });
		BodyCollision->SetPosition({ 0, 12 });
		BodyCollision->SetDebugRenderType(CollisionType::CT_Rect);
	}
	BodyCollision->SetPosition({ 0, -20 });
}

void Bamba::Update(float _DeltaTime)
{
	// 이동
	MoveDir.y += GravityAcceleration * _DeltaTime;
	if (GravityMax < MoveDir.y)
	{
		MoveDir.y = GravityMax;
	}

	if (nullptr == ColMap)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
	}


	float4 NextPos = GetPos() + MoveDir * _DeltaTime;
	float4 ForwardPos = NextPos;
	ForwardPos.y = GetPos().y - 4;

	// 맵 충돌 체크용 컬러 변수
	DWORD PixelColor = ColMap->GetPixelColor(NextPos, RGB(255, 255, 255));


	// 벽 체크
	if (RGB(0, 0, 0) == ColMap->GetPixelColor(ForwardPos, RGB(255, 255, 255)))
	{
		DirValue = -DirValue;
		MoveDir.x = Speed * DirValue;
		if (0 < DirValue)
		{
			AnimationRender->ChangeAnimation("RIGHT_WALK");
		}
		else
		{
			AnimationRender->ChangeAnimation("LEFT_WALK");
		}
		NextPos = GetPos() + MoveDir * _DeltaTime;
		PixelColor = ColMap->GetPixelColor(NextPos, RGB(255, 255, 255));
	}
	// 바닥 체크
	if (RGB(0, 0, 0) == PixelColor)
	{
		MoveDir.x = Speed * DirValue;
		NextPos.y = std::round(NextPos.y);
		// 바닥에서 제일 위로 올라간다
		while (true)
		{
			NextPos.y -= 1;
			PixelColor = ColMap->GetPixelColor(NextPos, RGB(0, 0, 0));
			if (RGB(0, 0, 0) != PixelColor)
			{
				SetPos(NextPos);
				MoveDir.y = 0;
				break;
			}
		}
	}
	// 아래에서 통과되는 블록들 체크 ex) 구름
	else if (RGB(0, 255, 0) == PixelColor)
	{
		MoveDir.x = Speed * DirValue;
		NextPos.y = std::round(NextPos.y);
		// 바닥에서 제일 위로 올라간다
		while (true)
		{
			NextPos.y -= 1;
			PixelColor = ColMap->GetPixelColor(NextPos, RGB(0, 0, 0));
			if (RGB(255, 255, 255) == PixelColor)
			{
				SetPos(NextPos);
				MoveDir.y = 0;
				break;
			}
		}
	}
	// 비탈길 체크
	else if (RGB(255, 0, 0) == PixelColor)
	{
		MoveDir.x = Speed * DirValue * 0.6f;
		float4 SlopePos = NextPos;
		SlopePos.x += 5;
		SlopePos.y -= 5;
		PixelColor = ColMap->GetPixelColor(SlopePos, RGB(0, 0, 0));
		NextPos.y = std::round(NextPos.y);
		// 바닥에서 제일 위로 올라간다
		while (true)
		{
			NextPos.y -= 1;
			PixelColor = ColMap->GetPixelColor(NextPos, RGB(0, 0, 0));
			if (RGB(255, 255, 255) == PixelColor)
			{
				SetPos(NextPos);
				MoveDir.y = 0;
				break;
			}
		}
		NextPos.x += 1;
	}

	SetMove(MoveDir * _DeltaTime);

}

void Bamba::Render(float _DeltaTime)
{
	//BodyCollision->DebugRender();
}
