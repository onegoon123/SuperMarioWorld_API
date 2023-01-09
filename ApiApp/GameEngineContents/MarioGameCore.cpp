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
	// �Ǽ� 1.2 ���Ѵٸ� 
	GameEngineWindow::SettingWindowSize({ 1024, 896 });

	new int();

	CreateLevel<TitleLevel>("Title");
	CreateLevel<OpenningLevel>("Openning");
	CreateLevel<PlayLevel>("Play");
	// static_assert
	// CreateLevel<HPlayer>("Title1");
	ChangeLevel("Play");
}

void MarioGameCore::Update()
{

}
void MarioGameCore::End()
{

}