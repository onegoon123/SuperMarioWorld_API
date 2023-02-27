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
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");

}

void StageLevel2::LevelChangeStart(GameEngineLevel* _PrevLevel)
{


	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Overworld.mp3");

	Map* Map1 = CreateActor<Map>();
	Map1->SetImage(BackGroundName, StageName, StageColName);
	CreateActor<Mario>();
	UI = CreateActor<UIManager>();
	Map1->AddStartPos(GridPos(3, 0));
	Map1->MoveMap(0);
	SetCameraMove({ 0, 790 });
	CreateActor<Goal>()->SetGoal(GridPos(302, 0));
	StageLevel::LevelChangeStart(_PrevLevel);
}
