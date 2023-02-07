#include "Bamba.h"
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"
Bamba::Bamba() {

}

Bamba::~Bamba() {

}

void Bamba::Start()
{
	// 兄希 持失
	{
		AnimationRender = CreateRender(RenderOrder::Monster);
		AnimationRender->SetScale({ 64, 64 });
		AnimationRender->CreateAnimation({ .AnimationName = "LEFT_WALK", .ImageName = "BAMBA.BMP", .Start = 0, .End = 1, .InterTime = 0.25f });
		AnimationRender->CreateAnimation({ .AnimationName = "RIGHT_WALK", .ImageName = "BAMBA.BMP", .Start = 2, .End = 3, .InterTime = 0.25f });
	}
	AnimationRender->ChangeAnimation("LEFT_WALK");

	// Collision 持失
	{
		BodyCollision = CreateCollision(CollisionOrder::Monster);
		BodyCollision->SetScale({ 48, 48 });
		BodyCollision->SetPosition({ 0, 12 });
		BodyCollision->SetDebugRenderType(CollisionType::CT_Rect);
	}
}

void Bamba::Update(float _DeltaTime)
{
}

void Bamba::Render(float _DeltaTime)
{
	//BodyCollision->DebugRender();
}
