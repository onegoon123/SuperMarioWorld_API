#include "SuperMushroom.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Mario.h"
#include "ContentsEnums.h"
#include "Map.h"

SuperMushroom::SuperMushroom() {
	ColMap = GameEngineResources::GetInst().ImageFind(Map::MainMap->GetStageColName());
}

SuperMushroom::~SuperMushroom() {

}

void SuperMushroom::Start()
{
	GameEngineRender* Render = CreateRender(RenderOrder::Item);
	Render->SetImage("SUPERMUSHROOM.BMP");
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
	DWORD PixelColor = ColMap->GetPixelColor(NextPos, RGB(255, 255, 255));


	// 벽 체크
	if (RGB(0, 0, 0) == ColMap->GetPixelColor(ForwardPos, RGB(255, 255, 255)))
	{
		DirValue = -DirValue;
		MoveDir.x = Speed * DirValue;
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
		MoveDir.x = Speed * DirValue * 0.6;
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

void SuperMushroom::Render(float _DeltaTime)
{
	//Collision->DebugRender();
}
