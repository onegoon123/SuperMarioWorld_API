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
		GameEngineRender* Render = CreateRender("BACKGROUND1.BMP", RenderOrder::BackGround);
		Render->SetScale({ 2048,1728 });
		Render->SetPosition({ 0,-100 });
	}
	{
		GameEngineRender* Render = CreateRender("STAGE1.BMP", RenderOrder::Map);
		Render->SetScale({ 20480, 1728 });
		Render->SetPosition({ 3300, -418 });
	}
	{
		GameEngineRender* Render = CreateRender("RIGHT_MARIO.BMP", RenderOrder::Player);
		Render->SetScale({ 192, 192 });
		Render->SetPosition({ 0, 196 });
	}
	{
		GameEngineRender* Render = CreateRender("TITLE.BMP", RenderOrder::UI);
		Render->SetScale({ 1024, 896 });
	}

}
