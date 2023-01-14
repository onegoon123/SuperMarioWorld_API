#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ���������� ������ ��Ÿ���� ����
// ���������� ������ҵ��� �����ȴ�. (�÷��̾�, ���, �� �� ������Ʈ)
class PlayLevel : public GameEngineLevel
{
public:
	// constrcuter destructer
	PlayLevel();
	~PlayLevel();

	// delete Function
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;

private:

};

