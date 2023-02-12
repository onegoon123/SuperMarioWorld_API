#include "Block.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnums.h"

Block::Block() {

}

Block::~Block() {

}

void Block::Damage()
{
	Death();
}

void Block::Roll()
{
	AnimationRender->ChangeAnimation("TRUN");
	IsRoll = true;
	RollTimer = RollTime;
}

void Block::Start()
{
	// 兄希 持失
	{
		AnimationRender = CreateRender(RenderOrder::Block);
		AnimationRender->SetScale({ 64, 64 });
		AnimationRender->SetPosition({ 0, -31 });
		AnimationRender->CreateAnimation({ .AnimationName = "Defalut", .ImageName = "BLOCK.BMP", .Start = 3, .End = 3, });
		AnimationRender->CreateAnimation({ .AnimationName = "TRUN", .ImageName = "BLOCK.BMP", .Start = 0, .End = 3, .InterTime = 0.15f });
		AnimationRender->ChangeAnimation("Defalut");
	}
	// Collision 持失
	{
		BodyCollision = CreateCollision(CollisionOrder::Block);
		BodyCollision->SetScale({ 50, 64 });
		BodyCollision->SetPosition({ 0, -31 });
		BodyCollision->SetDebugRenderType(CollisionType::CT_Rect);
	}
}

void Block::Update(float _DeltaTime)
{
	if (true == IsRoll)
	{
		RollTimer -= _DeltaTime;
		if (0 > RollTimer)
		{
			IsRoll = false;
			AnimationRender->ChangeAnimation("Defalut");
		}
	}
}

void Block::Render(float _DeltaTime)
{
	//BodyCollision->DebugRender();
}
