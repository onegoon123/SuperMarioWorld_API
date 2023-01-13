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
	// 엑터의 위치를 화면 정중앙으로 이동
	SetMove(GameEngineWindow::GetScreenSize().half());

	// 타이틀에 표시될 이미지들을 렌더링한다
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
	// (임시) 타이틀화면에서 3초 기다리면 Play 레벨을 로딩
	AccTime += _DeltaTime;
	if (AccTime > 3) {
		MarioGameCore::GetInst().LoadLevel("Play");
	}

	// (미구현 - 버튼을 입력시 Play 레벨을 로딩)

}
