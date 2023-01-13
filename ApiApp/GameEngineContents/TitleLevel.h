#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���� ���۽� ������ ȭ��
// LEVEL1 �ʰ� �������� ȭ�鿡 ������
// ��ư�� �Է��ϸ� ����� ������ �̵�
class TitleLevel : public GameEngineLevel
{
public:
	TitleLevel();
	~TitleLevel();

	TitleLevel(const TitleLevel& _Other) = delete;
	TitleLevel(TitleLevel&& _Other) noexcept = delete;
	TitleLevel& operator=(const TitleLevel& _Other) = delete;
	TitleLevel& operator=(TitleLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;

private:

};

