#include "TitleImage.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "MarioGameCore.h"

TitleImage::TitleImage() {

}

TitleImage::~TitleImage() {

}

void TitleImage::Start()
{
	// ������ ��ġ�� ȭ�� ���߾����� �̵�
	SetMove(GameEngineWindow::GetScreenSize().half());

	// Ÿ��Ʋ�� ǥ�õ� �̹������� �������Ѵ�
	{
		GameEngineRender* Render = CreateRender("SKY.BMP", 0);
		Render->SetScale({ 1024,896 });
	}
	{
		GameEngineRender* Render = CreateRender("BACKGROUND01.BMP", 1);
		Render->SetScale({ 2048,1728 });
		Render->SetPosition({ 0,-100 });
	}
	{
		GameEngineRender* Render = CreateRender("STAGE1.BMP", 2);
		Render->SetScale({ 21868, 1728 });
		Render->SetPosition({ 9800,-380 });
	}
	{
		GameEngineRender* Render = CreateRender("MARIO.BMP", 3);
		Render->SetScale({ 192, 192 });
		Render->SetPosition({ 0, 235 });
	}
	{
		GameEngineRender* Render = CreateRender("TITLE.BMP", 4);
		Render->SetScale({ 1024, 896 });
	}

}

void TitleImage::Update(float _DeltaTime)
{
	// (�ӽ�) Ÿ��Ʋȭ�鿡�� 3�� ��ٸ��� Play ������ �ε�
	AccTime += _DeltaTime;
	if (AccTime > 3) {
		MarioGameCore::GetInst().LoadLevel("Play");
	}

	// (�̱��� - ��ư�� �Է½� Play ������ �ε�)

}
