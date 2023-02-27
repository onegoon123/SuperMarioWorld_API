#pragma once
#include "StageLevel.h"

class StageBasement1 : public StageLevel
{
public:
	StageBasement1();
	~StageBasement1();

	StageBasement1(const StageBasement1& _Other) = delete;
	StageBasement1(StageBasement1&& _Other) noexcept = delete;
	StageBasement1& operator=(const StageBasement1& _Other) = delete;
	StageBasement1& operator=(StageBasement1&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void LevelChangeStart(GameEngineLevel* _Prev) override;
private:
	const std::string_view BackGroundName = "BACKGROUND3.BMP";
	const std::string_view StageName = "Basement1.BMP";
	const std::string_view StageColName = "Basement1COL.BMP";
};

