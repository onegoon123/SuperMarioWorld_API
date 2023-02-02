#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class StageLevel3 : public GameEngineLevel
{
public:
	StageLevel3();
	~StageLevel3();

	StageLevel3(const StageLevel3& _Other) = delete;
	StageLevel3(StageLevel3&& _Other) noexcept = delete;
	StageLevel3& operator=(const StageLevel3& _Other) = delete;
	StageLevel3& operator=(StageLevel3&& _Other) noexcept = delete;

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

