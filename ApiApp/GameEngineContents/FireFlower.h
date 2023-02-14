#pragma once
#include "ItemActor.h"
class FireFlower : public ItemActor
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

