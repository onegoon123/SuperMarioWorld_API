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
	
	// ���۽� Ÿ��Ʋȭ�鿡 ǥ�õ� �̹����� ���� �ε��Ѵ�



	// �̹��� ���� ��ΰ˻�
	// 1. ContentsResources ������ �ִ� ���� ã�´�
	// 2. ContentsResources ������ �̵�
	// 3. Image ������ �̵�
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");

	// Ÿ��Ʋ ȭ�鿡 ǥ�õ� �̹������� �ε��Ѵ�
	// �߰��� �������� �̸� Cut ����� �̿��� �ڸ��� (�̹��� ���� ������ ����)
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PLAY\\RIGHT_MARIO.BMP"))->Cut(17, 9);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PLAY\\LEFT_MARIO.BMP"))->Cut(17, 9);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PLAY\\STAGE1.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PLAY\\BACKGROUND1.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("PLAY\\ALLBLACK.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TITLE\\GAMEOVER.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TITLE\\TITLE.BMP"));

	// ���带 �ε��Ѵ�
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Sound");
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("Title.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("YoshiIsland.mp3"));
	GameEngineResources::GetInst().SoundLoad(Dir.GetPlusFileName("GameOver.mp3"));

	// Ÿ��Ʋ �̹������� ǥ���� ���� ����

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
