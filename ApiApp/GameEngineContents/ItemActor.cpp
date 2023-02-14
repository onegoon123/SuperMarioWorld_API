#include "ItemActor.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "Mario.h"
#include "ContentsEnums.h"
ItemActor::ItemActor() {

}

ItemActor::~ItemActor() {

}

void ItemActor::Start()
{
	Collision = CreateCollision(CollisionOrder::Item);
	Collision->SetScale(CollisionScale);
	Collision->SetPosition(CollisionPos);
	Collision->SetDebugRenderType(CT_Rect);
}


void ItemActor::Update(float _DeltaTime)
{
	// 화면 밖으로 나갔는지 체크
	float4 InCameraPos = GetPos() - GetLevel()->GetCameraPos();
	if (0 > InCameraPos.x + 100)
	{
		IsOnCamera = false;
		OffCamera();
	}
	else if (GameEngineWindow::GetScreenSize().x < InCameraPos.x - 100)
	{
		IsOnCamera = false;
		OffCamera();
	}
	else
	{
		IsOnCamera = true;
		OnCamera();
	}

	if (false == IsOnCamera)
	{
		return;
	}
	
	// 플레이어 체크
	std::vector<GameEngineCollision*> Collisions;
	CollisionCheckParameter Check = { .TargetGroup = static_cast<int>(CollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect };
	if (true == Collision->Collision(Check, Collisions))
	{
		Mario::MainPlayer->NewItem(ThisItemType);
		Death();
	}
}

void ItemActor::Render(float _DeltaTime)
{
	Collision->DebugRender();
}
