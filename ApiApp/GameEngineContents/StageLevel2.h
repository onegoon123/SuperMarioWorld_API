#pragma once
#include "StageLevel.h"

class StageLevel2 : public StageLevel
{
public:
	StageLevel2();
	~StageLevel2();

	StageLevel2(const StageLevel2& _Other) = delete;
	StageLevel2(StageLevel2&& _Other) noexcept = delete;
	StageLevel2& operator=(const StageLevel2& _Other) = delete;
	StageLevel2& operator=(StageLevel2&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
private:
};

