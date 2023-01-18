#include "TitleImage.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include "MarioGameCore.h"
#include "ContentsEnums.h"

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
		GameEngineRender* Render = CreateRender("SKY.BMP", RenderOrder::Sky);
		Render->SetScale({ 1024,896 });
	}
	{
		GameEngineRender* Render = CreateRender("BACKGROUND01.BMP", RenderOrder::BackGround);
		Render->SetScale({ 2048,1728 });
		Render->SetPosition({ 0,-100 });
	}
	{
		GameEngineRender* Render = CreateRender("STAGE1.BMP", RenderOrder::Map);
		Render->SetScale({ 21868, 1728 });
		Render->SetPosition({ 9800,-380 });
	}
	{
		GameEngineRender* Render = CreateRender("RIGHT_MARIO.BMP", RenderOrder::Player);
		Render->SetScale({ 192, 192 });
		Render->SetPosition({ 0, 235 });
	}
	{
		GameEngineRender* Render = CreateRender("TITLE.BMP", RenderOrder::UI);
		Render->SetScale({ 1024, 896 });
	}

}
