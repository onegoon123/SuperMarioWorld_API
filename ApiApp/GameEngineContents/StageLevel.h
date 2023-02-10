#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class StageLevel : public GameEngineLevel
{
public:
	StageLevel();
	~StageLevel();

	StageLevel(const StageLevel& _Other) = delete;
	StageLevel(StageLevel&& _Other) noexcept = delete;
	StageLevel& operator=(const StageLevel& _Other) = delete;
	StageLevel& operator=(StageLevel&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;

	std::string_view BackGroundName = "";
	std::string_view StageName = "";
	std::string_view StageColName = "";
private:
};
