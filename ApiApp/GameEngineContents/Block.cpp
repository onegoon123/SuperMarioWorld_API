#include "Block.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineResources.h>
#include "ContentsEnums.h"

Block::Block() {

}

Block::~Block() {

}

void Block::Damage()
{
	GameEngineResources::GetInst().SoundPlay("breakblock.wav");
	Death();
}

void Block::Roll()
{
	
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
		AnimationRender->CreateAnimation({ .AnimationName = "TRUN", .ImageName = "BLOCK.BMP", .Start = 0, .End = 3, .InterTime = 0.13f });
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
			return;
		}
		if (RollTime - 0.05f < RollTimer)
		{
			AnimationRender->SetMove(float4::Up * UpSpeed * _DeltaTime);
		}
		else if (RollTime - 0.1f < RollTimer)
		{
			AnimationRender->SetMove(float4::Down * UpSpeed * _DeltaTime);
		}
		else {
			AnimationRender->ChangeAnimation("TRUN");
		}
	}
	
}

void Block::Render(float _DeltaTime)
{
	//BodyCollision->DebugRender();
}
