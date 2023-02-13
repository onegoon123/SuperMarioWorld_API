#include "SuperMushroom.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Mario.h"
#include "ContentsEnums.h"
#include "Map.h"
#include "Block.h"

SuperMushroom::SuperMushroom() {
	ColMap = GameEngineResources::GetInst().ImageFind(Map::MainMap->GetStageColName());
}

SuperMushroom::~SuperMushroom() {

}

void SuperMushroom::Start()
{
	GameEngineRender* Render = CreateRender(RenderOrder::Item);
	Render->SetImage("SUPERMUSHROOM.BMP");
	Render->SetScaleToImage();
	Render->SetPosition({ 0,-29 });
	Collision = CreateCollision(CollisionOrder::Item);
	Collision->SetScale({ 48, 48 });
	Collision->SetPosition({ 0, -25 });
	Collision->SetDebugRenderType(CT_Rect);

	DirValue = 1;
	MoveDir.x = DirValue * Speed;
}

void SuperMushroom::Update(float _DeltaTime)
{

	// 플레이어와 충돌할 시
	CollisionCheckParameter Check = { .TargetGroup = static_cast<int>(CollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect, };
	if (true == Collision->Collision(Check))
	{
		Mario::MainPlayer->NewItem(ItemType::SuperMushroom);
		Death();
	}

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
		DirValue = -DirValue;
		MoveDir.x = Speed * DirValue;
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
	Check = { .TargetGroup = static_cast<int>(CollisionOrder::Block), .TargetColType = CT_Rect, .ThisColType = CT_Rect };
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
				DirValue = -DirValue;
				MoveDir.x = Speed * DirValue;
			}
		}
	}
	SetMove(MoveDir * _DeltaTime);

}

void SuperMushroom::Render(float _DeltaTime)
{
	//Collision->DebugRender();
}
