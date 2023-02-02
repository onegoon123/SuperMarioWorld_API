#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class StageLevel1 : public GameEngineLevel
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
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
private:
	std::string_view BackGroundName;
	std::string_view StageName;
	std::string_view StageColName;
};

