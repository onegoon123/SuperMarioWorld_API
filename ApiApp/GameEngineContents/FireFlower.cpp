#include "FireFlower.h"
#include <GameEngineCore/GameEngineRender.h>
#include "Mario.h"
FireFlower::FireFlower() {

}

FireFlower::~FireFlower() {

}

void FireFlower::Start()
{
	ItemActor::Start();
	ThisItemType = ItemType::FireFlower;
	ItemRender = CreateRender(RenderOrder::Item);
	ItemRender->SetScale({ 64, 64 });
	ItemRender->SetPosition({ 0, -30 });
	ItemRender->CreateAnimation({ .AnimationName = "Defalut", .ImageName = "FIREFLOWER.BMP", .Start = 0, .End = 1, .InterTime = 0.2f });
	ItemRender->ChangeAnimation("Defalut");

	Collision = CreateCollision(CollisionOrder::Check);
	Collision->SetScale(CollisionScale);
}

void FireFlower::Update(float _DeltaTime)
{
	ItemActor::Update(_DeltaTime);
}
