#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "MarioGameCore.h"
#include "ContentsEnums.h"

// �÷��̾ �����ϰ� �Ǵ� ������ ĳ����
// �⺻ ������	�̵�, ����, ���, ��������
// �Ŀ��� ���¿� ���� �Ҳɽ��, ���� ���� �����ϴ�
// ��� ž�� ���¿� ���� ��Ű��, ���, ����, ������ ���� �����ϴ�
// ��� ž�½� ���۵� �ش� Ŭ�������� �����ȴ�

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
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	
	const float Speed = 50.0f;		// �̵� �ӵ�
	const float JumpForce = 10.0f;	// ������

	//			 MyState	   StockState
	// Normal : �⺻������		�������
	// Super  : ���۸�����		����
	// Fire   : ���̾����	��
	// Cape   : ���丶����		����
	MarioState MyState = MarioState::Normal;
	MarioState StockState = MarioState::Normal;

	bool IsRidedYoshi = false;	// ��� ž�� ����
	bool IsGrounded = true;		// �������� �� ���� �ִ��� ����

	
	
#pragma region __________ �ǰ� ���� �Լ� __________

	// �ε����� ������� �޴� ��� ����Ǵ� �Լ�
	void GetDamaged() {
		switch (MyState)
		{
		case MarioState::Normal:
			GameOver();		// Normal�� ��� ���ӿ��� �Լ� ������ ����
			return;
		case MarioState::Super:
			MyState = MarioState::Normal;
			break;
		case MarioState::Fire:
			MyState = MarioState::Normal;
			break;
		case MarioState::Cape:
			MyState = MarioState::Normal;
			break;
		default:
			break;
		}
		InvincibilityTime();	// ���� �ð� Ȱ��
		TakeOutStock();	// ���� ������ ��ȯ
	}
	// �߶��ϰų� Normal ���¿��� ������� ���� ��� ����Ǵ� ���ӿ��� �Լ�
	void GameOver() {

	}
	// �ǰ��� �����ð� ������ �����ϴ� ���� �Լ�
	void InvincibilityTime() {

	}


#pragma endregion

#pragma region __________ ���� ���� �Լ� __________

#pragma endregion

#pragma region __________ �̵� ���� �Լ� __________

#pragma endregion

#pragma region __________ ��� ���� �Լ� __________

#pragma endregion

#pragma region __________ �Ŀ� ���� �Լ� __________
	void TakeOutStock() {
		if (MarioState::Normal == StockState) {
			return;
		}
		// ( �̱��� ���忡 �ش��ϴ� �Ŀ��������� ����)
		StockState = MarioState::Normal;
	}
#pragma endregion

#pragma region __________ �浹 ���� �Լ� __________

#pragma endregion\
};

