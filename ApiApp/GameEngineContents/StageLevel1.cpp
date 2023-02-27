#include "StageLevel1.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include "Mario.h"
#include "Map.h"
#include "Bamba.h"
#include "SuperMushroom.h"
#include "FireFlower.h"
#include "TurnBlock.h"
#include "UIManager.h"
#include "QuestionBlock.h"
#include "Goal.h"
#include "Coin.h"
#include "Pipe.h"

StageLevel1::StageLevel1() {

}

StageLevel1::~StageLevel1() {

}

void StageLevel1::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	

	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Overworld.mp3");
	BGMPlayer.LoopCount(0);

	Map* MainMap = CreateActor<Map>();
	MainMap->SetImage(BackGroundName, StageName, StageColName);
	MainMap->AddStartPos(GridPos(5,0));
	MainMap->AddStartPos({ 8945, 1279 });

	CreateActor<Mario>();
	UI = CreateActor<UIManager>();

	if ("Underground1" == _PrevLevel->GetName())
	{
		MainMap->MoveMap(1);
		SetTimer(dynamic_cast<StageLevel*>(_PrevLevel)->GetTimer());
	}
	else
	{
		MainMap->MoveMap(0);
	}
	SetCameraMove({ 0, 790 });

	
	{
		CreateActor<Bamba>(RenderOrder::Monster)->SetPos(GridPos(10, 1));
		CreateActor<Coin>(RenderOrder::Item)->SetPos(GridPos(8, 4));
		CreateActor<Coin>(RenderOrder::Item)->SetPos(GridPos(9, 4));
		CreateActor<Coin>(RenderOrder::Item)->SetPos(GridPos(10, 4));
		CreateActor<Coin>(RenderOrder::Item)->SetPos(GridPos(11, 4));
		QuestionBlock* ItemBox = CreateActor<QuestionBlock>(RenderOrder::Map);
		ItemBox->SetPos(GridPos(4, 4));
		ItemBox->SetItem(ItemType::FireFlower);
	}
	
	
	{
		CreateActor<Coin>(RenderOrder::Item)->SetPos(GridPos(11, 3));
		CreateActor<Coin>(RenderOrder::Item)->SetPos(GridPos(12, 3));
		CreateActor<Coin>(RenderOrder::Item)->SetPos(GridPos(13, 3));
		CreateActor<Coin>(RenderOrder::Item)->SetPos(GridPos(14, 3));
		CreateActor<Bamba>(RenderOrder::Monster)->SetPos(GridPos(21, 0));
		CreateActor<Bamba>(RenderOrder::Monster)->SetPos(GridPos(30, 0));

		CreateActor<TurnBlock>(RenderOrder::Map)->SetPos(GridPos(23, 3));
		QuestionBlock* ItemBox = CreateActor<QuestionBlock>(RenderOrder::Map);
		ItemBox->SetPos(GridPos(25, 3));
		ItemBox->SetItem(ItemType::SuperMushroom);
		ItemBox = CreateActor<QuestionBlock>(RenderOrder::Map);
		ItemBox->SetPos(GridPos(26, 3));
		ItemBox->SetItem(ItemType::SuperMushroom);
		CreateActor<TurnBlock>(RenderOrder::Map)->SetPos(GridPos(27, 3));

		CreateActor<Bamba>(RenderOrder::Monster)->SetPos(GridPos(55, 4));
		CreateActor<Bamba>(RenderOrder::Monster)->SetPos(GridPos(56, 4));
		CreateActor<Bamba>(RenderOrder::Monster)->SetPos(GridPos(57, 4));
		ItemBox = CreateActor<QuestionBlock>(RenderOrder::Map);
		ItemBox->SetPos(GridPos(80, 7));
		ItemBox->SetItem(ItemType::FireFlower);

		CreateActor<Bamba>(RenderOrder::Monster)->SetPos(GridPos(85, 0));
		CreateActor<Bamba>(RenderOrder::Monster)->SetPos(GridPos(90, 0));
		CreateActor<Bamba>(RenderOrder::Monster)->SetPos(GridPos(95, 0));

		CreateActor<TurnBlock>(RenderOrder::Map)->SetPos(GridPos(100, 3));
		CreateActor<TurnBlock>(RenderOrder::Map)->SetPos(GridPos(101, 3));
		CreateActor<TurnBlock>(RenderOrder::Map)->SetPos(GridPos(101, 6));
		CreateActor<Coin>(RenderOrder::Item)->SetPos(GridPos(100, 8));
		CreateActor<Coin>(RenderOrder::Item)->SetPos(GridPos(101, 8));
		CreateActor<Coin>(RenderOrder::Item)->SetPos(GridPos(102, 8));
		CreateActor<TurnBlock>(RenderOrder::Map)->SetPos(GridPos(102, 3));

		CreateActor<Bamba>(RenderOrder::Monster)->SetPos(GridPos(105, 0));
		CreateActor<Bamba>(RenderOrder::Monster)->SetPos(GridPos(106, 0));
		CreateActor<Bamba>(RenderOrder::Monster)->SetPos(GridPos(107, 0));

		CreateActor<TurnBlock>(RenderOrder::Map)->SetPos({7700, 1341});
		CreateActor<TurnBlock>(RenderOrder::Map)->SetPos({ 7764, 1341 });
		Pipe* NewPipe = CreateActor<Pipe>(RenderOrder::Map);
		NewPipe->SetPos({ 7732, 1405 });
		NewPipe->SetPipe("Underground1", Down);

		CreateActor<Bamba>(RenderOrder::Monster)->SetPos(GridPos(131, 4));
		//CreateActor<Bamba>(RenderOrder::Monster)->SetPos(GridPos(139, 4));

		CreateActor<TurnBlock>(RenderOrder::Map)->SetPos(GridPos(158, 4));
		ItemBox = CreateActor<QuestionBlock>(RenderOrder::Map);
		ItemBox->SetPos(GridPos(159, 4));
		ItemBox->SetItem(ItemType::SuperMushroom);
		CreateActor<TurnBlock>(RenderOrder::Map)->SetPos(GridPos(160, 4));

		CreateActor<Bamba>(RenderOrder::Monster)->SetPos(GridPos(175, 0));
		CreateActor<Bamba>(RenderOrder::Monster)->SetPos(GridPos(180, 0));
		CreateActor<Bamba>(RenderOrder::Monster)->SetPos(GridPos(185, 0));
		CreateActor<Bamba>(RenderOrder::Monster)->SetPos(GridPos(188, 2));

		CreateActor<TurnBlock>(RenderOrder::Map)->SetPos(GridPos(200, 4));
		CreateActor<TurnBlock>(RenderOrder::Map)->SetPos(GridPos(201, 4));
		CreateActor<TurnBlock>(RenderOrder::Map)->SetPos(GridPos(202, 4));

		for (int i = 0; i < 15; i++) {
			CreateActor<Coin>(RenderOrder::Item)->SetPos(GridPos(211 + i, 8));
			CreateActor<Coin>(RenderOrder::Item)->SetPos(GridPos(211 + i, 9));
			CreateActor<Coin>(RenderOrder::Item)->SetPos(GridPos(211 + i, 10));
		}

		CreateActor<TurnBlock>(RenderOrder::Map)->SetPos(GridPos(234, 3));
		ItemBox = CreateActor<QuestionBlock>(RenderOrder::Map);
		ItemBox->SetPos(GridPos(236, 6));
		ItemBox->SetItem(ItemType::FireFlower);
		CreateActor<TurnBlock>(RenderOrder::Map)->SetPos(GridPos(238, 3));

		CreateActor<Bamba>(RenderOrder::Monster)->SetPos(GridPos(250, 0));
		CreateActor<Bamba>(RenderOrder::Monster)->SetPos(GridPos(251, 0));
		CreateActor<Bamba>(RenderOrder::Monster)->SetPos(GridPos(252, 0));
		CreateActor<Bamba>(RenderOrder::Monster)->SetPos(GridPos(253, 0));

		CreateActor<Bamba>(RenderOrder::Monster)->SetPos(GridPos(270, 4));
		CreateActor<Bamba>(RenderOrder::Monster)->SetPos(GridPos(272, 4));
		CreateActor<Bamba>(RenderOrder::Monster)->SetPos(GridPos(274, 4));
	}
	

	CreateActor<Goal>()->SetGoal(GridPos(302, 0));
	StageLevel::LevelChangeStart(_PrevLevel);

}
