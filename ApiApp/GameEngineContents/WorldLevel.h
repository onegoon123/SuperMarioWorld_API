#pragma once
#include <GameEngineCore/GameEngineLevel.h>

// ������� ������ ����
// �� ������ �����ɶ� MarioGameCore�� ���� �������� Ŭ���� ������ �޾ƿͼ�
// ������ �� �ִ� ���������� �����Ѵ�
class WorldLevel : public GameEngineLevel
{
public:
	WorldLevel();
	~WorldLevel();

	WorldLevel(const WorldLevel& _Other) = delete;
	WorldLevel(WorldLevel&& _Other) noexcept = delete;
	WorldLevel& operator=(const WorldLevel& _Other) = delete;
	WorldLevel& operator=(WorldLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;

private:

};

