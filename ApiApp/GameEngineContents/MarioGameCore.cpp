#include "MarioGameCore.h"
#include <GameEnginePlatform/GameEngineWindow.h>

#include "PlayLevel.h"
#include "TitleLevel.h"
#include "OpenningLevel.h"

// MarioGameCore MarioGameCore::Core = new MarioGameCore();

// �߰��� ����� �������� �����ָ� ������������ ���� �����Ҵ��ؼ� ����Ѵٴ°�
// �������⿡�� ��??? �׷�������?
MarioGameCore MarioGameCore::Core;

MarioGameCore::MarioGameCore()
{
}

MarioGameCore::~MarioGameCore()
{
}

void MarioGameCore::Start()
{
	// ������ ���� �������? ������ ������ ���ɴϴ�.
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