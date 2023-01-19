#include "TitleLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include "MarioGameCore.h"
#include "PlayLevel.h"
#include "TitleImage.h"

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
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("RIGHT_MARIO.BMP"))->Cut(17, 9);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("LEFT_MARIO.BMP"))->Cut(17, 9);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SKY.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("STAGE1.BMP"))->Cut(20,1);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BACKGROUND01.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TITLE.BMP"));

	// Ÿ��Ʋ �̹������� ǥ���� ���� ����
	CreateActor<TitleImage>();

	
}

void TitleLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsAnyKey()) {
		MarioGameCore::GetInst().ChangeLevel("Play");
	}
}
