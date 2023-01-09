#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "MarioGameCore.h"
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

	// �ε����� ������� �޴� ��� ����Ǵ� �Լ�
	void GetDamaged() {
		switch (MarioState)
		{
		case Mario::Normal:
			GameOver();		// Normal�� ��� ���ӿ��� �Լ� ������ ����
			return;
		case Mario::Super:
			MarioState = Normal;
			break;
		case Mario::Fire:
			MarioState = Normal;
			break;
		case Mario::Cape:
			MarioState = Normal;
			break;
		default:
			break;
		}
		InvincibilityTime();	// ���� �ð� Ȱ��
		MarioGameCore::GetInst().TakeOutStock();	// ���� ������ ��ȯ
	}
	// �߶��ϰų� Normal ���¿��� ������� ���� ��� ����Ǵ� ���ӿ��� �Լ�
	void GameOver() {

	}
	// �ǰ��� �����ð� ������ �����ϴ� ���� �Լ�
	void InvincibilityTime() {

	}
};

