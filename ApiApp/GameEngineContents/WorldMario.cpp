#include "WorldMario.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include "ContentsEnums.h"
#include "MarioGameCore.h"
#include "LevelLoader.h"
#include "WorldLevel.h"
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
	Stage1 = new WorldMap::Point({ 289, 690 }, "Stage3");
	Stage2 = new WorldMap::Point({ 676, 690 }, "Stage1");
	Stage3 = new WorldMap::Point({ 672, 568 }, "Stage2", true);
	Stage4 = new WorldMap::Point({ 804, 430 }, "Stage4", true);
	Center->SetLeft(Stage1);
	Center->SetRight(Stage2);
	Stage3->SetDown(Stage2);
	Stage4->SetDown(Stage3);
	Stage4->SetLeft(Stage3);

	Map = new WorldMap(Center);
}

void WorldMario::Update(float _DeltaTime)
{
	if (true == IsMove)
	{
		Timer += _DeltaTime * speed;
		SetPos(float4::LerpClamp(StartPos, EndPos, Timer));
		if (1 < Timer)
		{
			IsMove = false;
			Timer = 0;
		}
		return;
	}


	if (true == IsStart) { return; }

	if (GameEngineInput::IsDown("Left"))
	{
		AnimationRender->ChangeAnimation("LEFT");
		
		if (true == Map->MoveLeft())
		{
			StartPos = GetPos();
			EndPos = Map->GetPos();
			Timer = 0;
			IsMove = true;
		}
		return;
	}
	if (GameEngineInput::IsDown("Right"))
	{
		AnimationRender->ChangeAnimation("RIGHT");

		if (true == Map->MoveRight())
		{
			StartPos = GetPos();
			EndPos = Map->GetPos();
			Timer = 0;
			IsMove = true;
		}
		return;
	}
	if (GameEngineInput::IsDown("UP"))
	{
		AnimationRender->ChangeAnimation("UP");

		if (true == Map->MoveUp())
		{
			StartPos = GetPos();
			EndPos = Map->GetPos();
			Timer = 0;
			IsMove = true;
		}
		return;
	}
	if (GameEngineInput::IsDown("DOWN"))
	{
		AnimationRender->ChangeAnimation("DOWN");

		if (true == Map->MoveDown())
		{
			StartPos = GetPos();
			EndPos = Map->GetPos();
			Timer = 0;
			IsMove = true;
		}

		return;
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


	if (GameEngineInput::IsDown("3"))
	{
		WorldLevel::GetInstance()->StageClear("Stage1");
		WorldLevel::GetInstance()->StageClear("Stage2");
	}
}

void WorldMario::LevelChangeStart(GameEngineLevel* _Prev)
{
	AnimationRender->ChangeAnimation("DOWN");
	IsStart = false;
}
