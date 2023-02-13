#include "Bamba.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>
#include "ContentsEnums.h"
#include "Map.h"
#include "Block.h"

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
	DWORD PixelColor = ColMap->GetPixelColor(NextPos, White);
	// 벽 체크
	if (Black == ColMap->GetPixelColor(ForwardPos, White))
	{
		Turn();
		NextPos = GetPos() + MoveDir * _DeltaTime;
		PixelColor = ColMap->GetPixelColor(NextPos, White);
	}
	// 바닥 체크
	if (Black == PixelColor)
	{
		MoveDir.x = Speed * DirValue;
		NextPos.y = std::round(NextPos.y);
		// 바닥에서 제일 위로 올라간다
		while (true)
		{
			NextPos.y -= 1;
			PixelColor = ColMap->GetPixelColor(NextPos, Black);
			if (Black != PixelColor)
			{
				SetPos(NextPos);
				MoveDir.y = 0;
				break;
			}
		}
	}
	// 아래에서 통과되는 블록들 체크 ex) 구름
	else if (Green == PixelColor)
	{
		MoveDir.x = Speed * DirValue;
		NextPos.y = std::round(NextPos.y);
		// 바닥에서 제일 위로 올라간다
		while (true)
		{
			NextPos.y -= 1;
			PixelColor = ColMap->GetPixelColor(NextPos, Black);
			if (White == PixelColor)
			{
				SetPos(NextPos);
				MoveDir.y = 0;
				break;
			}
		}
	}
	// 비탈길 체크
	else if (Red == PixelColor)
	{
		MoveDir.x = Speed * DirValue * 0.6f;
		float4 SlopePos = NextPos;
		SlopePos.x += 5;
		SlopePos.y -= 5;
		PixelColor = ColMap->GetPixelColor(SlopePos, Black);
		NextPos.y = std::round(NextPos.y);
		// 바닥에서 제일 위로 올라간다
		while (true)
		{
			NextPos.y -= 1;
			PixelColor = ColMap->GetPixelColor(NextPos, Black);
			if (White == PixelColor)
			{
				SetPos(NextPos);
				MoveDir.y = 0;
				break;
			}
		}
		NextPos.x += 1;
	}

	// 블록 체크
	std::vector<GameEngineCollision*> Collisions;
	CollisionCheckParameter Check = { .TargetGroup = static_cast<int>(CollisionOrder::Block), .TargetColType = CT_Rect, .ThisColType = CT_Rect };
	if (true == BodyCollision->Collision(Check, Collisions))
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
			// 플레이어가 블록보다 위에 있는 경우
			if (GetPos().y < ColActor->GetPos().y - BlockYSize)
			{
				if (0 > MoveDir.y)
				{
					continue;
				}
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
			// 그 외 경우
			else
			{
				Turn();
			}
		}
	}
	SetMove(MoveDir * _DeltaTime);

}

void Bamba::Render(float _DeltaTime)
{
	//BodyCollision->DebugRender();
}

void Bamba::Turn()
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
}
