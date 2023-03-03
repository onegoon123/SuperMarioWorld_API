#include "MarioGameCore.h"
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "PlayLevel.h"
#include "TitleLevel.h"
#include "WorldLevel.h"
#include "StageLevel1.h"
#include "StageLevel2.h"
#include "StageLevel3.h"
#include "StageLevel4.h"
#include "StageLevel5.h"
#include "GameOverLevel.h"
#include "StageUnderground1.h"
// MarioGameCore MarioGameCore::Core = new MarioGameCore();

MarioGameCore MarioGameCore::Core;

MarioGameCore::MarioGameCore()
{
}

MarioGameCore::~MarioGameCore()
{
}

void MarioGameCore::ResetGame()
{
	Life = StartLife;
}

void MarioGameCore::Start()
{
	// 해상도 설정
	// (256 x 224) * 4
	GameEngineWindow::SettingWindowSize({ 1024, 896 });

	// 키 설정
	if (false == GameEngineInput::IsKey("Start")) {
		GameEngineInput::CreateKey("Start", VK_SPACE);	// 스타트 = 스페이스
		GameEngineInput::CreateKey("Up", 'W');
		GameEngineInput::CreateKey("Left", 'A');
		GameEngineInput::CreateKey("Down", 'S');
		GameEngineInput::CreateKey("Right", 'D');
		GameEngineInput::CreateKey("Dash", 'J');
		GameEngineInput::CreateKey("Jump", 'K');
		GameEngineInput::CreateKey("Spin", 'L');
		GameEngineInput::CreateKey("1", '1');
		GameEngineInput::CreateKey("2", '2');
		GameEngineInput::CreateKey("3", '3');
	}


	new int();

	
	ResourcesLoad();
	



	CreateLevel<TitleLevel>("Title");
	CreateLevel<WorldLevel>("World");
	CreateLevel<StageLevel1>("Stage1");
	CreateLevel<StageLevel1>("Stage2");
	CreateLevel<StageLevel3>("Stage3");
	CreateLevel<StageLevel4>("Stage4");
	CreateLevel<StageLevel5>("Stage5");
	CreateLevel<StageUnderground1>("Underground1");
	CreateLevel<GameOverLevel>("GameOver");
	ChangeLevel("Title");

	//WorldLevel::GetInstance()->StageClear("Stage2");
	//WorldLevel::GetInstance()->StageClear("Stage3");
	//WorldLevel::GetInstance()->StageClear("Stage4");
}

void MarioGameCore::Update()
{

}
void MarioGameCore::End()
{

}

void MarioGameCore::ResourcesLoad()
{
	
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("Play");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RIGHT_MARIO.BMP"))->Cut(17, 9);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LEFT_MARIO.BMP"))->Cut(17, 9);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BACKGROUND1.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BACKGROUND5.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("STAGE1.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("STAGE2.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("STAGE3.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("STAGE4.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("STAGE5.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Underground1.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("STAGE0COL.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("STAGE1COL.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("STAGE2COL.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("STAGE3COL.BMP"));
	//GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("STAGE4COL.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("STAGE5COL.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Underground1COL.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ALLBLACK.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NUMBER.BMP"))->Cut(10, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NUMBERBIG.BMP"))->Cut(10, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NUMBERYELLOW.BMP"))->Cut(10, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BACKGROUND2.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BACKGROUND3.BMP"))->Cut(4,1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("CheckPoint.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("CheckPointPass.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("CheckPointFront.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BAMBA.BMP"))->Cut(8, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RIGHT_NOKONOKO.BMP"))->Cut(3, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RIGHT_NOKONOKO_HADAKA.BMP"))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LEFT_NOKONOKO.BMP"))->Cut(3, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LEFT_NOKONOKO_HADAKA.BMP"))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SHELL.BMP"))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SUPERMUSHROOM.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("KILLER.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FIRE.BMP"))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FIREFLOWER.BMP"))->Cut(2, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("FIREFLOWERUI.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SMOKE.BMP"))->Cut(5, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SKIDDUST1.BMP"))->Cut(5, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SKIDDUST.BMP"))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("KICK.BMP"))->Cut(3, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BLOCK.BMP"))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Blockdebrits.BMP"))->Cut(6, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PLAYUI.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NONE.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Clear.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ClearBar.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Goal.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ClearBonus.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("StarParticle.BMP"))->Cut(1, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("QuestionBlock.BMP"))->Cut(5, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Coin.BMP"))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LEFT_KOOPA.BMP"))->Cut(9, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RIGHT_KOOPA.BMP"))->Cut(9, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LEFT_Mechakoopa.BMP"))->Cut(7, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RIGHT_Mechakoopa.BMP"))->Cut(7, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LEFT_Pierrot.BMP"))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RIGHT_Pierrot.BMP"))->Cut(4, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Propeller.BMP"))->Cut(1, 4);

	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("World");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("WORLD1.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("WORLD1FRONT.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("STAGEBLOCK1.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("STAGEBLOCK2.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("STAGEBLOCK3.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SEA.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MARIO.BMP"))->Cut(4, 5);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("CLOUD.BMP"))->Cut(1, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TIDE.BMP"))->Cut(1, 8);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("STAGEBUTTON.BMP"))->Cut(1, 7);

	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("TITLE");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("GAMEOVER.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TITLE.BMP"));

	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");
	std::vector<GameEngineFile> Files = Dir.GetAllFile();

	for (size_t i = 0; i < Files.size(); i++)
	{
		GameEngineResources::GetInst().SoundLoad(Files[i].GetFullPath());
	}
	
}