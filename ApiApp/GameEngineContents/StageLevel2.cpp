#include "StageLevel2.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>

#include "Mario.h"
#include "Map.h"

StageLevel2::StageLevel2() {

}

StageLevel2::~StageLevel2() {

}

void StageLevel2::Loading()
{
	BackGroundName = "BACKGROUND2.BMP";
	StageName = "STAGE2.BMP";
	StageColName = "STAGE0COL.BMP";

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");
	//GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(SkyName));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(BackGroundName));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(StageName));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(StageColName));

}

void StageLevel2::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("1"))
	{
		MarioGameCore::GetInst().ChangeLevel("Stage1");
	}
	if (GameEngineInput::IsDown("2"))
	{
		MarioGameCore::GetInst().ChangeLevel("Stage3");
	}
}

void StageLevel2::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != Mario::MainPlayer)
	{
		Mario::MainPlayer->Death();
		Mario::MainPlayer = nullptr;
	}
	SetCameraPos(float4::Zero);
}

void StageLevel2::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	CreateActor<Mario>();
	SetCameraMove({ 0, 790 });
	Map* Map1 = CreateActor<Map>();
	Map1->SetImage(BackGroundName, StageName, StageColName);
	Map1->AddStartPos({ 350 , 1534 });
	Map1->MoveMap(0);
}
