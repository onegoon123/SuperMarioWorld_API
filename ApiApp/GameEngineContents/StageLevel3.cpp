#include "StageLevel3.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>

#include "Mario.h"
#include "Map.h"

StageLevel3::StageLevel3() {

}

StageLevel3::~StageLevel3() {

}

void StageLevel3::Loading()
{
	BackGroundName = "BACKGROUND3.BMP";
	StageName = "STAGE3.BMP";
	StageColName = "STAGE0COL.BMP";

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");
	//GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(SkyName));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(BackGroundName))->Cut(4,1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(StageName));
	//GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(StageColName));

}

void StageLevel3::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("1"))
	{
		MarioGameCore::GetInst().ChangeLevel("Stage2");
	}
	if (GameEngineInput::IsDown("2"))
	{
		MarioGameCore::GetInst().ChangeLevel("Stage4");
	}
}

void StageLevel3::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != Mario::MainPlayer)
	{
		Mario::MainPlayer->Death();
		Mario::MainPlayer = nullptr;
	}
	SetCameraPos(float4::Zero);
}

void StageLevel3::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	CreateActor<Mario>();
	SetCameraMove({ 0, 790 });
	Map* Map1 = CreateActor<Map>();
	Map1->BackGroundAnimOn();
	Map1->SetImage(BackGroundName, StageName, StageColName);

	Map1->GetBackGroundRender()->CreateAnimation({ .AnimationName = "BackGroundAnim", .ImageName = BackGroundName, .Start = 0, .End = 3 });
	Map1->GetBackGroundRender()->SetScale({ 2048, 1728 });
	Map1->GetBackGroundRender()->SetPosition({ 1024, 864 });
	Map1->GetBackGroundRender()->ChangeAnimation("BackGroundAnim");

	Map1->AddStartPos({ 350 , 1534 });
	Map1->MoveMap(0);

}
