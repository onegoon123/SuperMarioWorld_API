#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineCollision.h>
class FireFlower : public GameEngineActor
{
public:
	FireFlower();
	~FireFlower();

	FireFlower(const FireFlower& _Other) = delete;
	FireFlower(FireFlower&& _Other) noexcept = delete;
	FireFlower& operator=(const FireFlower& _Other) = delete;
	FireFlower& operator=(FireFlower&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
private:

	GameEngineCollision* Collision = nullptr;
};

