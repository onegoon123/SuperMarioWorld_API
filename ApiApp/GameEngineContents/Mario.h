#pragma once
#include <GameEngineCore/GameEngineActor.h>
class Mario : public GameEngineActor
{
public:
	Mario();
	~Mario();

	Mario(const Mario& _Other) = delete;
	Mario(Mario&& _Other) noexcept = delete;
	Mario& operator=(const Mario& _Other) = delete;
	Mario& operator=(Mario&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	enum State
	{
		Normal, Super, Fire, Cape
	};
	State MarioState = State::Normal;
	bool IsRidedYoshi;
	float Speed;
	float JumpForce;

	bool IsGrounded;

};

