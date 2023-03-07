#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "MarioGameCore.h"
#include "ContentsEnums.h"

enum class MarioState
{
	IDLE,
	WALK,
	RUN,
	BRAKE,
	CROUCH,
	LOOKUP,
	JUMP,
	FALL,
	RUNJUMP,
	SPIN,
	SLIDE,
	KICK,
	CHANGEPOWER,
	Pipe,
	VICTORY,
	GameOver,
};
enum class Dir
{
	Left,
	Right
};

// �÷��̾ �����ϰ� �Ǵ� ������ ĳ����
// �⺻ ������	�̵�, ����, ���, ��������
// �Ŀ��� ���¿� ���� �Ҳɽ��, ���� ���� �����ϴ�
// ��� ž�� ���¿� ���� ��Ű��, ���, ����, ������ ���� �����ϴ�
// ��� ž�½� ���۵� �ش� Ŭ�������� �����ȴ�
class StageLevel;
class GameEngineImage;
class EnemyActor;
class Mario : public GameEngineActor
{
public:

	static Mario* MainPlayer;

	void NewItem(ItemType _Item);
	void Die();
	void StageClear();
	bool GetIsGameOver() {
		return StateValue == MarioState::GameOver || StateValue == MarioState::VICTORY;
	}
	PowerState GetPowerState() {
		return MarioPower;
	}
	void DropHold();
	void PipeIn(const float4& _PipePos, const float4& _Dir);
	void PipeOut(const float4& _Dir);
	void AddScore(int _Score);

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
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
private:

	float Speed = 705;				// �̵� �ӵ�
	float RunSpeed = 850.0f;			// �޸��� �̵� �ӵ�
	const float ClearWalkSpeed = 45;			// �޸��� �̵� �ӵ�
	const float JumpForce = 950;			// ������
	const float DashJumpForce = 1100;		// ��� �� ������
	const float RunJumpForce = 1200;		// �޸��� ������
	const float JumpPressForce = 3350;		// ���� ������
	const float SpinPressForce = 2750;		// ���� ���� ������
	const float SlopeForce = 1000;			// ��Ż�濡�� �������� ��
	const float JumpTime = 0.325f;			// ���� ���� ���ӽð�
	const float GravityMax = 1275;			// �ִ� �߷�
	const float GravityAcceleration = 4600;	// �߷� ���ӵ�
	const float BrakingForce = 5;			// �극��ũ ���½� ������
	const float StoppingForce = 1;			// ������ ������
	const float Acceleration = 1.5;			// �Ȱ� ������ ���ӷ�
	const float DashAcceleration = 2;		// ��� �� ���ӷ�
	const float InvincibilityTime = 3;		// �ǰݽ� ���� �ð�
	const float ChangePowerTime = 0.9f;		// �Ŀ� ���� �ִϸ��̼� ���ӽð�
	const float GameOverTime = 2.0f;		// ���ӿ����� �ִϸ��̼� ���ӽð�
	const float FireAnimTime = 0.2f;		// �� �� �ִϸ��̼� ���ӽð�
	const float KickAnimTime = 0.25f;		// �� ���� �Ҷ� �ִϸ��̼� ���ӽð�
	const float PipeOutTime = 1.0f;		
	const float ParticleDelay = 0.1f;		// ��ƼŬ ����� ������
	const float HeadingReaction = 150.0f;	// ����� ���ۿ� ��

	const float4 FireCreatePos = { 30, 40 };// �Ҳ� ������ ��ġ (������ ����)
	const float4 RenderScale={192,192};		// ���� ũ��
	const float4 RenderPos = { 0, -56 };	// ���� ��ġ
	const float4 CollisionScale ={ 52, 64 };// �浹ü ũ��
	const float4 CollisionPos = { 0, -32 };	// �浹ü ��ġ 
	const float4 FootCollisionScale ={ 24, 60 };// �浹ü ũ��
	const float4 FootCollisionPos = { 0, -30 };	// �浹ü ��ġ 
	const float4 HoldPos = { 40, -8 };	// �浹ü ��ġ 

	float4 ScreenSize = float4::Zero;
	float4 MapSize = float4::Zero;


	//			 MarioPower	
	// Normal : �⺻������	
	// Super  : ���۸�����	
	// Fire   : ���̾����	
	// Cape   : ���丶����	
	PowerState MarioPower = PowerState::Normal;

	bool IsGrounded = true;			// �������� �� ���� �ִ��� ����
	bool IsSlope = false;			// �������� ��Ż�� ���� �ִ��� ����
	bool IsInvincibility = false;	// ���� �ð� ����
	bool IsOnBlock = false;			// �������� ��� ���� �ִ��� ����
	bool IsDie = false;			
	bool IsHold = false;
	float4 MoveDir = float4::Zero;	// �������� �������� ��
	float HorizontalForce = 0;
	float JumpTimeCounter = 0;
	float RunChargeTime = 0;	// ��ø� �� �ð��� ����ؼ� �޸��� ��ȯ�� �Ǵ��ϴ� ����
	float Timer = 0;
	float FireAnimTimer = 0;	// �� �� �ִϸ��̼� ���ӽð�
	float KickAnimTimer = KickAnimTime;	// ������ �� �� �ִϸ��̼� ���ӽð�
	float ParticleDelayTimer = 0;	// ��ƼŬ ����� ������

	MarioState StateValue = MarioState::IDLE;
	MarioState BeforeState = MarioState::IDLE;
	Dir DirValue = Dir::Right;
	Dir SlopeDir = Dir::Right;

	GameEngineRender* AnimationRender = nullptr;
	std::string_view BeforeAnim = "";
	GameEngineImage* ColMap = nullptr;
	GameEngineCollision* Collision = nullptr;
	GameEngineCollision* FootCollision = nullptr;
	StageLevel* CurrentLevel = nullptr;
	EnemyActor* HoldActor = nullptr;


#pragma region __________ State ���� �Լ� _________
	void ChangeState(MarioState _State);
	void UpdateState(float _DeltaTime);

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void WalkStart();
	void WalkUpdate(float _DeltaTime);
	void WalkEnd();

	void RunStart();
	void RunUpdate(float _DeltaTime);
	void RunEnd();

	void BrakeStart();
	void BrakeUpdate(float _DeltaTime);
	void BrakeEnd();

	void JumpStart();
	void JumpUpdate(float _DeltaTime);
	void JumpEnd();

	void SpinStart();
	void SpinUpdate(float _DeltaTime);
	void SpinEnd();

	void CrouchStart();
	void CrouchUpdate(float _DeltaTime);
	void CrouchEnd();

	void LookUpStart();
	void LookUpUpdate(float _DeltaTime);
	void LookUpEnd();

	void RunJumpStart();
	void RunJumpUpdate(float _DeltaTime);
	void RunJumpEnd();

	void FallStart();
	void FallUpdate(float _DeltaTime);
	void FallEnd();

	void SlideStart();
	void SlideUpdate(float _DeltaTime);
	void SlideEnd();
	
	void ChangePowerStart(MarioState _BeforeState);
	void ChangePowerUpdate(float _DeltaTime);
	void ChangePowerEnd();

	void GameOverStart();
	void GameOverUpdate(float _DeltaTime);
	void GameOverEnd();

	void VictoryUpdate(float _DeltaTime);

	void PipeStart();
	void PipeUpdate(float _DeltaTime);

#pragma endregion

#pragma region __________ �浹 ���� �Լ� __________
	void CheckCollision();
	void BlockCheck();
#pragma endregion


#pragma region __________Animation ���� �Լ� ________
	void ChangeAnimation(const std::string_view& _AnimationName);

#pragma endregion

#pragma region __________ �̵� ���� �Լ� __________
	void MoveCalculation(float _DeltaTime);
	void CameraMove(float _DeltaTime);
#pragma endregion

#pragma region __________ �ǰ� ���� �Լ� __________

	// �ε����� ������� �޴� ��� ����Ǵ� �Լ�
	void GetDamaged();
	// �߶��ϰų� Normal ���¿��� ������� ���� ��� ����Ǵ� ���ӿ��� �Լ�

#pragma endregion

#pragma region __________ �Ŀ� ���� �Լ� __________
	void FireAttack();
	void NewPower(PowerState _Power);
#pragma endregion

	void KickAttack();

};

