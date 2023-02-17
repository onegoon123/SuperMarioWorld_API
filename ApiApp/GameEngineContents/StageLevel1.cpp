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

StageLevel1::StageLevel1() {

}

StageLevel1::~StageLevel1() {

}

void StageLevel1::Loading()
{
	StageLevel::Loading();

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
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BAMBA.BMP"))->Cut(8, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SUPERMUSHROOM.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FIRE.BMP"))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FIREFLOWER.BMP"))->Cut(2, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SMOKE.BMP"))->Cut(5, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SKIDDUST1.BMP"))->Cut(5, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SKIDDUST.BMP"))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("KICK.BMP"))->Cut(3, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BLOCK.BMP"))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Blockdebrits.BMP"))->Cut(6, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PLAYUI.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NONE.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NUMBER.BMP"))->Cut(10, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NUMBERBIG.BMP"))->Cut(10, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NUMBERYELLOW.BMP"))->Cut(10, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("QuestionBlock.BMP"))->Cut(5,1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Coin.BMP"))->Cut(4,1);

	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Overworld.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("PlayerDown.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("jump.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("spin.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("powerup.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("kick.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("damage.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("fireball.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("bump.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("1UP.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Coin.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("breakblock.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("superstomp.wav"));
}

void StageLevel1::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	

	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Overworld.mp3");
	BGMPlayer.LoopCount(0);

	Map* Map1 = CreateActor<Map>();
	Map1->SetImage(BackGroundName, StageName, StageColName);
	CreateActor<Mario>();
	UI = CreateActor<UIManager>();
	Map1->AddStartPos(GridPos(5,0));
	Map1->MoveMap(0);
	SetCameraMove({ 0, 790 });

	/*
	{
		CreateActor<Bamba>()->SetPos(GridPos(10, 1));
		CreateActor<Coin>()->SetPos(GridPos(8, 4));
		CreateActor<Coin>()->SetPos(GridPos(9, 4));
		CreateActor<Coin>()->SetPos(GridPos(10, 4));
		CreateActor<Coin>()->SetPos(GridPos(11, 4));
		QuestionBlock* ItemBox = CreateActor<QuestionBlock>();
		ItemBox->SetPos(GridPos(4, 4));
		ItemBox->SetItem(ItemType::SuperMushroom);
	}
	*/

	{
		CreateActor<Coin>()->SetPos(GridPos(11, 3));
		CreateActor<Coin>()->SetPos(GridPos(12, 3));
		CreateActor<Coin>()->SetPos(GridPos(13, 3));
		CreateActor<Coin>()->SetPos(GridPos(14, 3));
		CreateActor<Bamba>()->SetPos(GridPos(21, 0));
		CreateActor<Bamba>()->SetPos(GridPos(30, 0));

		CreateActor<TurnBlock>()->SetPos(GridPos(23, 3));
		QuestionBlock* ItemBox = CreateActor<QuestionBlock>();
		ItemBox->SetPos(GridPos(25, 3));
		ItemBox->SetItem(ItemType::SuperMushroom);
		CreateActor<TurnBlock>()->SetPos(GridPos(27, 3));

		CreateActor<Bamba>()->SetPos(GridPos(55, 4));
		CreateActor<Bamba>()->SetPos(GridPos(56, 4));
		CreateActor<Bamba>()->SetPos(GridPos(57, 4));
		ItemBox = CreateActor<QuestionBlock>();
		ItemBox->SetPos(GridPos(80, 7));
		ItemBox->SetItem(ItemType::FireFlower);

		CreateActor<Bamba>()->SetPos(GridPos(85, 0));
		CreateActor<Bamba>()->SetPos(GridPos(90, 0));
		CreateActor<Bamba>()->SetPos(GridPos(95, 0));

		CreateActor<TurnBlock>()->SetPos(GridPos(100, 3));
		CreateActor<TurnBlock>()->SetPos(GridPos(101, 3));
		CreateActor<TurnBlock>()->SetPos(GridPos(101, 6));
		CreateActor<Coin>()->SetPos(GridPos(100, 8));
		CreateActor<Coin>()->SetPos(GridPos(101, 8));
		CreateActor<Coin>()->SetPos(GridPos(102, 8));
		CreateActor<TurnBlock>()->SetPos(GridPos(102, 3));

		CreateActor<Bamba>()->SetPos(GridPos(105, 0));
		CreateActor<Bamba>()->SetPos(GridPos(106, 0));
		CreateActor<Bamba>()->SetPos(GridPos(107, 0));

		CreateActor<Bamba>()->SetPos(GridPos(131, 4));
		CreateActor<Bamba>()->SetPos(GridPos(139, 4));

		CreateActor<TurnBlock>()->SetPos(GridPos(158, 4));
		ItemBox = CreateActor<QuestionBlock>();
		ItemBox->SetPos(GridPos(159, 4));
		ItemBox->SetItem(ItemType::SuperMushroom);
		CreateActor<TurnBlock>()->SetPos(GridPos(160, 4));

		CreateActor<Bamba>()->SetPos(GridPos(175, 0));
		CreateActor<Bamba>()->SetPos(GridPos(180, 0));
		CreateActor<Bamba>()->SetPos(GridPos(185, 0));
		CreateActor<Bamba>()->SetPos(GridPos(188, 2));

		CreateActor<TurnBlock>()->SetPos(GridPos(200, 4));
		CreateActor<TurnBlock>()->SetPos(GridPos(201, 4));
		CreateActor<TurnBlock>()->SetPos(GridPos(202, 4));

		for (int i = 0; i < 15; i++) {
			CreateActor<Coin>()->SetPos(GridPos(211 + i, 8));
			CreateActor<Coin>()->SetPos(GridPos(211 + i, 9));
			CreateActor<Coin>()->SetPos(GridPos(211 + i, 10));
		}

		CreateActor<TurnBlock>()->SetPos(GridPos(234, 3));
		ItemBox = CreateActor<QuestionBlock>();
		ItemBox->SetPos(GridPos(236, 6));
		ItemBox->SetItem(ItemType::FireFlower);
		CreateActor<TurnBlock>()->SetPos(GridPos(238, 3));

		CreateActor<Bamba>()->SetPos(GridPos(250, 0));
		CreateActor<Bamba>()->SetPos(GridPos(251, 0));
		CreateActor<Bamba>()->SetPos(GridPos(252, 0));
		CreateActor<Bamba>()->SetPos(GridPos(253, 0));

		CreateActor<Bamba>()->SetPos(GridPos(270, 3));
		CreateActor<Bamba>()->SetPos(GridPos(272, 3));
		CreateActor<Bamba>()->SetPos(GridPos(274, 3));
	}


	CreateActor<Goal>()->SetGoal(GridPos(302, 0), "World");
	StageLevel::LevelChangeStart(_PrevLevel);
}
