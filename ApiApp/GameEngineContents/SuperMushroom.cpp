#include "SuperMushroom.h"
#include <GameEngineCore/GameEngineRender.h>
#include "Mario.h"
#include "ContentsEnums.h"
SuperMushroom::SuperMushroom() {

}

SuperMushroom::~SuperMushroom() {

}

void SuperMushroom::Start()
{
	GameEngineRender* Render = CreateRender(RenderOrder::Item);
	Render->SetImage("SUPERMUSHROOM.BMP");
	
	Collision = CreateCollision(CollisionOrder::Item);
	Collision->SetScale({ 48, 48 });
	Collision->SetPosition({ 0, 0 });
}

void SuperMushroom::Update(float _DeltaTime)
{

	// 플레이어와 충돌할 시
	CollisionCheckParameter Check = { .TargetGroup = static_cast<int>(CollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect, };
	if (true == Collision->Collision(Check))
	{
		//Mario::MainPlayer->NewItem(ItemType::SuperMushroom);
		Mario::MainPlayer->NewItem(ItemType::FireFlower);
		Death();
	}
}
