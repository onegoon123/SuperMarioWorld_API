#pragma once
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineResources.h>
class StageLevel : public GameEngineLevel
{
public:
	StageLevel();
	~StageLevel();

	GameEngineSoundPlayer GetBGMPlayer()
	{
		return BGMPlayer;
	}

	StageLevel(const StageLevel& _Other) = delete;
	StageLevel(StageLevel&& _Other) noexcept = delete;
	StageLevel& operator=(const StageLevel& _Other) = delete;
	StageLevel& operator=(StageLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

	float4 GridPos(int x, int y)
	{
		return float4(static_cast<float>(x * 64 + 32), static_cast<float>((-y + 24) * 64));
	}

	std::string_view BackGroundName = "";
	std::string_view StageName = "";
	std::string_view StageColName = "";

	GameEngineSoundPlayer BGMPlayer;
private:
};
