#include "StageLevel3.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>

#include "Mario.h"
#include "Map.h"
#include "Goal.h"
StageLevel3::StageLevel3() {

}

StageLevel3::~StageLevel3() {

}


void StageLevel3::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Overworld.mp3");

	Map* Map1 = CreateActor<Map>();
	Map1->BackGroundAnimOn();
	Map1->SetImage(BackGroundName, StageName, StageColName);
	 
	Map1->GetBackGroundRender()->CreateAnimation({ .AnimationName = "BackGroundAnim", .ImageName = BackGroundName, .Start = 0, .End = 3 });
	Map1->GetBackGroundRender()->SetScale({ 2048, 1728 });
	Map1->GetBackGroundRender()->SetPosition({ 1024, 864 });
	Map1->GetBackGroundRender()->ChangeAnimation("BackGroundAnim");

	Map1->AddStartPos({ 350 , 1534 });

	CreateActor<Mario>();
	UI = CreateActor<UIManager>();
	Map1->MoveMap(0);
	CreateActor<Goal>()->SetGoal(GridPos(302, 0));

	StageLevel::LevelChangeStart(_PrevLevel);
}
