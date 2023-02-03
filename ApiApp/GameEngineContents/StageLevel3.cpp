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
	//GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(SkyName));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(BackGroundName))->Cut(4,1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(StageName))->Cut(1, 4);
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
	CreateActor<Mario>()->SetPos({ 350, 1536 });
	SetCameraMove({ 0, 790 });
	Map* Map1 = CreateActor<Map>();
	Map1->BackGroundAnimOn();
	Map1->SetImage(BackGroundName, StageName, StageColName);
	Map1->GetStageRender()->SetScale({ 30000, 1728 });
	Map1->GetStageRender()->SetPosition({ 15000 , 864});
	Map1->GetStageRender()->CreateAnimation({ .AnimationName = "MapAnim", .ImageName = StageName, .Start = 0, .End = 3 });
	Map1->GetStageRender()->ChangeAnimation("MapAnim");

	Map1->GetBackGroundRender()->CreateAnimation({ .AnimationName = "BackGroundAnim", .ImageName = BackGroundName, .Start = 0, .End = 3 });
	Map1->GetBackGroundRender()->SetScale({ 2048, 1728 });
	Map1->GetBackGroundRender()->SetPosition({ 1024, 864 });
	Map1->GetBackGroundRender()->ChangeAnimation("BackGroundAnim");

	Map1->MoveMap(1);

}
