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
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FIRE.BMP"))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FIREFLOWER.BMP"))->Cut(2, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SMOKE.BMP"))->Cut(5, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SKIDDUST1.BMP"))->Cut(5, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SKIDDUST.BMP"))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("KICK.BMP"))->Cut(3, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BLOCK.BMP"))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Blockdebrits.BMP"))->Cut(6, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PLAYUI.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("QuestionBlock.BMP"))->Cut(5,1);

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
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("breakblock.wav"));
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

void StageLevel1::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Overworld.mp3");

	Map* Map1 = CreateActor<Map>();
	Map1->SetImage(BackGroundName, StageName, StageColName);
	CreateActor<Mario>();
	CreateActor<UIManager>();
	Map1->AddStartPos(GridPos(5,0));
	Map1->MoveMap(0);
	SetCameraMove({ 0, 790 });
	CreateActor<TurnBlock>()->SetPos(GridPos(3, 5));
	CreateActor<Bamba>()->SetPos(GridPos(7, 5));
	CreateActor<TurnBlock>()->SetPos(GridPos(5, 4));
	CreateActor<TurnBlock>()->SetPos(GridPos(5, 5));
	CreateActor<TurnBlock>()->SetPos(GridPos(6, 4));
	CreateActor<TurnBlock>()->SetPos(GridPos(7, 4));
	CreateActor<TurnBlock>()->SetPos(GridPos(8, 4));
	CreateActor<TurnBlock>()->SetPos(GridPos(9, 4));
	CreateActor<TurnBlock>()->SetPos(GridPos(9, 5));
	//CreateActor<SuperMushroom>()->SetPos(GridPos(8, 0));
	CreateActor<TurnBlock>()->SetPos(GridPos(10, 1));
	CreateActor<TurnBlock>()->SetPos(GridPos(11, 1));
	QuestionBlock* ItemBox = CreateActor<QuestionBlock>();
	ItemBox->SetPos(GridPos(12, 1));
	ItemBox->SetItem(ItemType::FireFlower);
	CreateActor<TurnBlock>()->SetPos(GridPos(13, 1));
	CreateActor<TurnBlock>()->SetPos(GridPos(14, 1));
}
