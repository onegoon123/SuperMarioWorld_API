#pragma once
#include <GameEngineCore/GameEngineActor.h>

const float BlockYSize = 60.0f;			// 블록 판정 길이
const float BlockSidePos = 52.0f;		// 블록 옆에 있을때 거리
const float BlockOnPos = 63.0f;			// 블록 위에 설때 거리

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
	const float RollTime = 5.2f;
	const float UpSpeed = 800;
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;
};

