#pragma once
#include "StageLevel.h"

class StageLevel1 : public StageLevel
{
public:
	StageLevel1();
	~StageLevel1();

	StageLevel1(const StageLevel1& _Other) = delete;
	StageLevel1(StageLevel1&& _Other) noexcept = delete;
	StageLevel1& operator=(const StageLevel1& _Other) = delete;
	StageLevel1& operator=(StageLevel1&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update(float _DeltaTime) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
private:
};

