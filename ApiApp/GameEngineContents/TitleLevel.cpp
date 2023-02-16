#include "TitleLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include "MarioGameCore.h"
#include "PlayLevel.h"
#include "LevelLoader.h"

TitleLevel::TitleLevel() {

}

TitleLevel::~TitleLevel() {

}

void TitleLevel::Loading()
{
	
	// 시작시 타이틀화면에 표시될 이미지를 먼저 로딩한다



	// 이미지 파일 경로검색
	// 1. ContentsResources 폴더가 있는 곳을 찾는다
	// 2. ContentsResources 폴더로 이동
	// 3. Image 폴더로 이동
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");

	// 타이틀 화면에 표시될 이미지들을 로딩한다
	// 추가로 마리오는 미리 Cut 기능을 이용해 자른다 (이미지 분할 데이터 생성)
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PLAY\\RIGHT_MARIO.BMP"))->Cut(17, 9);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PLAY\\LEFT_MARIO.BMP"))->Cut(17, 9);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PLAY\\STAGE1.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PLAY\\BACKGROUND1.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PLAY\\ALLBLACK.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TITLE\\GAMEOVER.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TITLE\\TITLE.BMP"));

	// 사운드를 로딩한다
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Title.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("YoshiIsland.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("GameOver.mp3"));

	// 타이틀 이미지들을 표시할 엑터 생성

	GameEngineRender* TitleRender = CreateActor<GameEngineActor>()->CreateRender("TITLE.BMP", RenderOrder::BackGround);
	TitleRender->SetScaleToImage();
	TitleRender->SetPosition(TitleRender->GetScale().half());

	CreateActor<LevelLoader>();

}

void TitleLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsAnyKey()) {
		LevelLoader::ChangeLevel("World");
	}
}

void TitleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Title.mp3");
	BGMPlayer.LoopCount(0);
}

void TitleLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}
