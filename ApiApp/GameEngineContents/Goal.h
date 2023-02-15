#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineCollision.h>

class Goal : public GameEngineActor
{
public:
	Goal();
	~Goal();

	void SetGoal(const float4& _Pos , const std::string_view& _LevelStr) {
		SetPos(_Pos);
		LevelStr = _LevelStr;
	}
	void SetNextLevel(const std::string_view _LevelStr) {
		LevelStr = _LevelStr;
	}

	Goal(const Goal& _Other) = delete;
	Goal(Goal&& _Other) noexcept = delete;
	Goal& operator=(const Goal& _Other) = delete;
	Goal& operator=(Goal&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	GameEngineCollision* Collision = nullptr;
	const float4 CollisionScale = { 64, 1000 };
	std::string_view LevelStr = "";
};

