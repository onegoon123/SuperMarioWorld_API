#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineCollision.h>

class GameEngineImage;
class SuperMushroom : public GameEngineActor
{
public:
	SuperMushroom();
	~SuperMushroom();

	SuperMushroom(const SuperMushroom& _Other) = delete;
	SuperMushroom(SuperMushroom&& _Other) noexcept = delete;
	SuperMushroom& operator=(const SuperMushroom& _Other) = delete;
	SuperMushroom& operator=(SuperMushroom&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:

	const float Speed = 250;
	const float GravityMax = 1000;
	const float GravityAcceleration = 2000;

	GameEngineCollision* Collision = nullptr;
	GameEngineImage* ColMap = nullptr;
	float4 MoveDir = float4::Zero;
	float DirValue = 1;
};

