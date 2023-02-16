#include "WorldMario.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "ContentsEnums.h"
#include "MarioGameCore.h"

#include "LevelLoader.h"
WorldMario::WorldMario() {

}

WorldMario::~WorldMario() {
	if (nullptr != Map)
	{
		delete Map;
		Map = nullptr;
	}
}

void WorldMario::Reset()
{
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
	WorldMap::Point* Stage1 = new WorldMap::Point({ 289, 690 }, "Stage1");
	WorldMap::Point* Stage2 = new WorldMap::Point({ 676, 690 }, "Stage2");

	Center->SetLeft(Stage1);
	Center->SetRight(Stage2);

	Map = new WorldMap(Center);
}

void WorldMario::Update(float _DeltaTime)
{
	if (true == IsStart) { return; }

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
		if (true == Map->IsStage())
		{
			AnimationRender->ChangeAnimation("START");
			IsStart = true;
			LevelLoader::ChangeLevel(Map->GetStage());
		}
	}
}

void WorldMario::LevelChangeStart(GameEngineLevel* _Prev)
{
	AnimationRender->ChangeAnimation("DOWN");
	IsStart = false;
}
