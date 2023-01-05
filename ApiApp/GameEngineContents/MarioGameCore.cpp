#include "MarioGameCore.h"
#include "PlayLevel.h"
#include "TitleLevel.h"

// StudyGameCore StudyGameCore::Core = new StudyGameCore();

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
	new int();

	CreateLevel<PlayLevel>("Play");
	CreateLevel<TitleLevel>("Title");
	ChangeLevel("Title");
}

void MarioGameCore::Update()
{

}
void MarioGameCore::End()
{

}