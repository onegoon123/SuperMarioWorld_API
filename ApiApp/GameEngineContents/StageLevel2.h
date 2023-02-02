#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class StageLevel2 : public GameEngineLevel
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
	void Update(float _DeltaTime) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
private:
	std::string_view BackGroundName;
	std::string_view StageName;
	std::string_view StageColName;
};

