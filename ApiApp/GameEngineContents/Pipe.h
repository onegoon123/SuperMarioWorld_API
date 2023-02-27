#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Pipe : public GameEngineActor
{
public:
	Pipe();
	~Pipe();

	Pipe(const Pipe& _Other) = delete;
	Pipe(Pipe&& _Other) noexcept = delete;
	Pipe& operator=(const Pipe& _Other) = delete;
	Pipe& operator=(Pipe&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	GameEngineCollision* Collision = nullptr;
	const float4 CollisionSize = { 96, 16 };
};

