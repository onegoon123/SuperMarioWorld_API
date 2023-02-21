#pragma once
#include <GameEnginePlatform/GameEngineImage.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineLevel.h>

class EnemyActor : public GameEngineActor
{
public:
	EnemyActor();
	~EnemyActor();

	virtual bool IsCollisionAttack() = 0;
	virtual bool IsHold() = 0;
	virtual void SpinHit() = 0;
	virtual void JumpHit() = 0;
	virtual void FireHit() = 0;
	virtual void BlockHit() = 0;
	virtual void MonsterHit() = 0;
	virtual void Hold() = 0;
	virtual void Kick(const float4& _Force) = 0;

	EnemyActor(const EnemyActor& _Other) = delete;
	EnemyActor(EnemyActor&& _Other) noexcept = delete;
	EnemyActor& operator=(const EnemyActor& _Other) = delete;
	EnemyActor& operator=(EnemyActor&& _Other) noexcept = delete;

protected:
	void Start() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;

	// 카메라 안에 있는지 체크
	void CameraInCheck();
	// 이동 처리 업데이트
	void MoveUpdate(float _DeltaTime);



	virtual void OffCamera();
	virtual void OnCamera();

	virtual void DirSetting(const float4& _DirValue);
	virtual void Turn();
	virtual void TurnLeft();
	virtual void TurnRight();

	float Speed = 250;
	float SlopeSpeed = Speed * 0.6f;

	float4 DirValue = float4::Zero;
	float4 MoveDir = float4::Zero;
	const float GravityMax = 1200;
	const float GravityAcceleration = 3000;
	GameEngineImage* ColMap = nullptr;
	GameEngineCollision* Collision = nullptr;
private:

	const float4 CollisionScale = { 16, 16 };

	bool IsOnCamera = true;
	bool IsSlope = false;
};

