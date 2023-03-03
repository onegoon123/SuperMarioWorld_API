#include "StageLevel2.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include "UIManager.h"
#include "Mario.h"
#include "Map.h"
#include "Bamba.h"
#include "SuperMushroom.h"
#include "FireFlower.h"
#include "TurnBlock.h"
#include "QuestionBlock.h"
#include "Goal.h"
#include "Coin.h"
#include "Pipe.h"
#include "CheckPointActor.h"
#include "Nokonoko.h"
#include "Killer.h"
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

	{
		CreateActor<Nokonoko>(RenderOrder::Monster)->SetPos(GridPos(22, 3));
		CreateActor<Nokonoko>(RenderOrder::Monster)->SetPos(GridPos(24, 3));
		CreateActor<Nokonoko>(RenderOrder::Monster)->SetPos(GridPos(25, 3));
		CreateActor<Nokonoko>(RenderOrder::Monster)->SetPos(GridPos(26, 3));
		CreateActor<Nokonoko>(RenderOrder::Monster)->SetPos(GridPos(27, 3));
		CreateActor<Nokonoko>(RenderOrder::Monster)->SetPos(GridPos(28, 3));
		CreateActor<Nokonoko>(RenderOrder::Monster)->SetPos(GridPos(29, 3));
	}
	StageLevel::LevelChangeStart(_PrevLevel);
}
