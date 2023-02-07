#include "StageLevel1.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include "Mario.h"
#include "Map.h"
#include "Bamba.h"
#include "SuperMushroom.h"

StageLevel1::StageLevel1() {

}

StageLevel1::~StageLevel1() {

}

void StageLevel1::Loading()
{
	BackGroundName = "BACKGROUND1.BMP";
	StageName = "STAGE1.BMP";
	StageColName = "STAGE1COL.BMP";

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");
	//GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(SkyName));
	//GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(BackGroundName));
	//GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(StageName));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(StageColName));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BAMBA.BMP"))->Cut(7, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SUPERMUSHROOM.BMP"));

}

void StageLevel1::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("1"))
	{
		MarioGameCore::GetInst().ChangeLevel("Title");
	}
	if (GameEngineInput::IsDown("2"))
	{
		MarioGameCore::GetInst().ChangeLevel("Stage2");
	}
}

void StageLevel1::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != Mario::MainPlayer)
	{
		Mario::MainPlayer->Death();
		Mario::MainPlayer = nullptr;
	}
	SetCameraPos(float4::Zero);
}

void StageLevel1::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Map* Map1 = CreateActor<Map>();
	Map1->SetImage(BackGroundName, StageName, StageColName);
	CreateActor<Mario>();
	Map1->AddStartPos({ 350 , 1534 });
	Map1->MoveMap(0);
	SetCameraMove({ 0, 790 });


	CreateActor<Bamba>()->SetPos({ 700, 1506 });
	CreateActor<Bamba>()->SetPos({ 3200, 1506 });
	CreateActor<SuperMushroom>()->SetPos({ 1000, 1506 });
	CreateActor<SuperMushroom>()->SetPos({ 500, 1200 });
}
