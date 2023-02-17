#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>
#include "UIManager.h"
class StageLevel : public GameEngineLevel
{
public:
	StageLevel();
	~StageLevel();

	GameEngineSoundPlayer GetBGMPlayer()
	{
		return BGMPlayer;
	}
	void AddCoin();
	void AddLife();
	void AddScore(int _Score);
	void MarioDie();

	StageLevel(const StageLevel& _Other) = delete;
	StageLevel(StageLevel&& _Other) noexcept = delete;
	StageLevel& operator=(const StageLevel& _Other) = delete;
	StageLevel& operator=(StageLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

	float4 GridPos(int x, int y)
	{
		return float4(static_cast<float>(x * 64 + 32), static_cast<float>((-y + 24) * 64));
	}

	std::string_view BackGroundName = "";
	std::string_view StageName = "";
	std::string_view StageColName = "";

	GameEngineSoundPlayer BGMPlayer = GameEngineSoundPlayer();
	UIManager* UI = nullptr;
private:
	int Life = 3;
	int Star = 0;
	int Score = 0;
	int CoinNum = 0;
	float Timer = 0;
	const float Time = 300;
};
