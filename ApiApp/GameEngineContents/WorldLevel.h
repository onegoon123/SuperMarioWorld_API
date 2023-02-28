#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>

// ������� ������ ����
// �� ������ �����ɶ� MarioGameCore�� ���� �������� Ŭ���� ������ �޾ƿͼ�
// ������ �� �ִ� ���������� �����Ѵ�
class WorldMario;
class WorldImage;
class WorldLevel : public GameEngineLevel
{
public:

	static WorldLevel* GetInstance()
	{
		return Instance;
	}

	void StageClear(const std::string_view& _StageName);

	WorldLevel();
	~WorldLevel();

	WorldLevel(const WorldLevel& _Other) = delete;
	WorldLevel(WorldLevel&& _Other) noexcept = delete;
	WorldLevel& operator=(const WorldLevel& _Other) = delete;
	WorldLevel& operator=(WorldLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

private:
	static WorldLevel* Instance;
	WorldMario* WorldData = nullptr;
	WorldImage* ImageActor = nullptr;
	GameEngineSoundPlayer BGMPlayer;
};

