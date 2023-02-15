#include "WorldMario.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "ContentsEnums.h"
#include "MarioGameCore.h"
WorldMario::WorldMario() {

}

WorldMario::~WorldMario() {
	if (nullptr != Map)
	{
		delete Map;
		Map = nullptr;
	}
}

void WorldMario::Start()
{
	AnimationRender = CreateRender(RenderOrder::Player);
	AnimationRender->SetScale({64, 64});

	AnimationRender->CreateAnimation({ .AnimationName = "DOWN", .ImageName = "MARIO.BMP", .Start = 0, .End = 3, .InterTime = 0.15f});
	AnimationRender->CreateAnimation({ .AnimationName = "UP", .ImageName = "MARIO.BMP", .Start = 4, .End = 7, .InterTime = 0.15f});
	AnimationRender->CreateAnimation({ .AnimationName = "LEFT", .ImageName = "MARIO.BMP", .Start = 8, .End = 9, .InterTime = 0.15f});
	AnimationRender->CreateAnimation({ .AnimationName = "RIGHT", .ImageName = "MARIO.BMP", .Start = 12, .End = 13, .InterTime = 0.15f});
	AnimationRender->CreateAnimation({ .AnimationName = "START", .ImageName = "MARIO.BMP", .Start = 10, .End = 10, });

	AnimationRender->ChangeAnimation("Down");

	WorldMap::Point* Center = new WorldMap::Point({ 475, 650 });
	WorldMap::Point* Stage1 = new WorldMap::Point({ 289, 706 }, "Stage1");
	WorldMap::Point* Stage2 = new WorldMap::Point({ 676, 706 }, "Stage2");

	Center->SetLeft(Stage1);
	Center->SetRight(Stage2);

	Map = new WorldMap(Center);
}

void WorldMario::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("Left"))
	{
		AnimationRender->ChangeAnimation("LEFT");
		Map->MoveLeft();
		SetPos(Map->GetPos());
		
	}
	if (GameEngineInput::IsDown("Right"))
	{
		AnimationRender->ChangeAnimation("RIGHT");
		Map->MoveRight();
		SetPos(Map->GetPos());
	}
	if (GameEngineInput::IsDown("UP"))
	{
		AnimationRender->ChangeAnimation("UP");
		Map->MoveUp();
		SetPos(Map->GetPos());
	}
	if (GameEngineInput::IsDown("DOWN"))
	{
		AnimationRender->ChangeAnimation("DOWN");
		Map->MoveDown();
		SetPos(Map->GetPos());
	}
	if (GameEngineInput::IsDown("Start") || GameEngineInput::IsDown("Dash") || GameEngineInput::IsDown("Jump") || GameEngineInput::IsDown("Spin"))
	{
		AnimationRender->ChangeAnimation("START");
		if (true == Map->IsStage())
		{
			MarioGameCore::GetInst().ChangeLevel(Map->GetStage());
		}
	}
}
