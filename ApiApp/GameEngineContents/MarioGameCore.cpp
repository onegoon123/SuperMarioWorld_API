#include "MarioGameCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include "PlayLevel.h"
#include "TitleLevel.h"
#include "StageLevel1.h"
#include "StageLevel2.h"
#include "StageLevel3.h"
#include "StageLevel4.h"

// MarioGameCore MarioGameCore::Core = new MarioGameCore();

// 중간에 절대로 지워지지 않을애를 포인터형으로 만들어서 동적할당해서 사용한다는건
// 제가보기에는 왜??? 그래야하지?
MarioGameCore MarioGameCore::Core;

MarioGameCore::MarioGameCore()
{
}

MarioGameCore::~MarioGameCore()
{
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

	CreateLevel<TitleLevel>("Title");
	CreateLevel<StageLevel1>("Stage1");
	CreateLevel<StageLevel2>("Stage2");
	CreateLevel<StageLevel3>("Stage3");
	CreateLevel<StageLevel4>("Stage4");
	ChangeLevel("Title");
}

void MarioGameCore::Update()
{

}
void MarioGameCore::End()
{

}