#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Block : public GameEngineActor
{
public:
	Block();
	~Block();

	void Damage();
	void Roll();
	bool GetIsRoll()
	{
		return IsRoll;
	}

	Block(const Block& _Other) = delete;
	Block(Block&& _Other) noexcept = delete;
	Block& operator=(const Block& _Other) = delete;
	Block& operator=(Block&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:
	bool IsRoll = false;
	float RollTimer = 0;
	const float RollTime = 6;
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
};

