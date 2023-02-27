#include "MarioGameCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include "PlayLevel.h"
#include "TitleLevel.h"
#include "WorldLevel.h"
#include "StageLevel1.h"
#include "StageLevel2.h"
#include "StageLevel3.h"
#include "StageLevel4.h"
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
	CreateLevel<StageLevel2>("Stage2");
	CreateLevel<StageLevel3>("Stage3");
	CreateLevel<StageLevel4>("Stage4");
	CreateLevel<StageUnderground1>("Underground1");
	CreateLevel<GameOverLevel>("GameOver");
	ChangeLevel("Title");
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
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("STAGE1.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("STAGE2.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Underground1.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("STAGE0COL.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("STAGE1COL.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("Underground1COL.BMP"));
	//GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("STAGE2COL.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ALLBLACK.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NUMBER.BMP"))->Cut(10, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NUMBERBIG.BMP"))->Cut(10, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("NUMBERYELLOW.BMP"))->Cut(10, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BACKGROUND2.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BACKGROUND3.BMP"))->Cut(4,1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BAMBA.BMP"))->Cut(8, 1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SUPERMUSHROOM.BMP"));
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

	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Overworld.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("PlayerDown.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Underground.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("jump.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("spin.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("powerup.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("kick.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("damage.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("fireball.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("bump.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("ItemGet.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("1UP.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Coin.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Pipe.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("breakblock.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("superstomp.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("CourseClear.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("OutItem.wav"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Title.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("YoshiIsland.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("GameOver.mp3"));

	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("World");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("WORLD1.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("WORLD1FRONT.BMP"));
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
}