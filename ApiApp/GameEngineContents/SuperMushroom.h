#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineCollision.h>
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
private:

	GameEngineCollision* Collision = nullptr;
};

