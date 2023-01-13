#include "TitleLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRender.h>
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
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MARIO.BMP"))->Cut(19, 37);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SKY.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("STAGE1.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BACKGROUND01.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TITLE.BMP"));

	// Ÿ��Ʋ �̹������� ǥ���� ���� ����
	CreateActor<TitleImage>();
}

void TitleLevel::Update()
{
	
}
