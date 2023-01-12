#include "MarioGameCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "PlayLevel.h"
#include "TitleLevel.h"
#include "OpenningLevel.h"

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
	// 정수의 연산 결과값은? 무조건 정수만 나옵니다.
	// 256 x 224
	GameEngineWindow::SettingWindowSize({ 1024, 896 });

	new int();

	CreateLevel<TitleLevel>("Title");
	//CreateLevel<OpenningLevel>("Openning");
	//CreateLevel<PlayLevel>("Play");
	// static_assert
	//ChangeLevel("Play");
	ChangeLevel("Title");
}

void MarioGameCore::Update()
{

}
void MarioGameCore::End()
{

}