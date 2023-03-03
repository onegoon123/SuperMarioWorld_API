#pragma once
#include "StageLevel.h"
class StageLevel5 : public StageLevel
{
public:
	StageLevel5();
	~StageLevel5();

	StageLevel5(const StageLevel5& _Other) = delete;
	StageLevel5(StageLevel5&& _Other) noexcept = delete;
	StageLevel5& operator=(const StageLevel5& _Other) = delete;
	StageLevel5& operator=(StageLevel5&& _Other) noexcept = delete;

protected:
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
private:
	const std::string_view BackGroundName = "BACKGROUND5.BMP";
	const std::string_view StageName = "STAGE5.BMP";
	const std::string_view StageColName = "STAGE5COL.BMP";
};

