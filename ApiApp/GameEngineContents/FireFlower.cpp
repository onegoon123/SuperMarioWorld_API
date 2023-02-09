#include "FireFlower.h"
#include <GameEngineCore/GameEngineRender.h>
#include "Mario.h"
#include "ContentsEnums.h"
FireFlower::FireFlower() {

}

FireFlower::~FireFlower() {

}

void FireFlower::Start()
{
	GameEngineRender* Render = CreateRender(RenderOrder::Item);
	Render->SetScale({ 64, 64 });
	Render->CreateAnimation({ .AnimationName = "Defalut", .ImageName = "FIREFLOWER.BMP", .Start = 0, .End = 1, .InterTime = 0.2f });
	Render->ChangeAnimation("Defalut");

	Collision = CreateCollision(CollisionOrder::Item);
	Collision->SetScale({ 48, 48 });
	Collision->SetPosition({ 0, 0 });
}

void FireFlower::Update(float _DeltaTime)
{

	// 플레이어와 충돌할 시
	CollisionCheckParameter Check = { .TargetGroup = static_cast<int>(CollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect, };
	if (true == Collision->Collision(Check))
	{
		Mario::MainPlayer->NewItem(ItemType::FireFlower);
		Death();
	}
}
