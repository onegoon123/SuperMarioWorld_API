#include "StageLevel2.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>

#include "Mario.h"
#include "Map.h"

#include "Goal.h"
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

void StageLevel2::LevelChangeStart(GameEngineLevel* _PrevLevel)
{


	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Overworld.mp3");

	Map* Map1 = CreateActor<Map>();
	Map1->SetImage(BackGroundName, StageName, StageColName);
	CreateActor<Mario>();
	UI = CreateActor<UIManager>();
	Map1->AddStartPos(GridPos(5, 0));
	Map1->MoveMap(0);
	SetCameraMove({ 0, 790 });
	CreateActor<Goal>()->SetGoal(GridPos(302, 0), "World");
	StageLevel::LevelChangeStart(_PrevLevel);
}
