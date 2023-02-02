#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class StageLevel4 : public GameEngineLevel
{
public:
	StageLevel4();
	~StageLevel4();

	StageLevel4(const StageLevel4& _Other) = delete;
	StageLevel4(StageLevel4&& _Other) noexcept = delete;
	StageLevel4& operator=(const StageLevel4& _Other) = delete;
	StageLevel4& operator=(StageLevel4&& _Other) noexcept = delete;

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

