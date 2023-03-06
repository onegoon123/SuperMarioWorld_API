#include "Koopa.h"
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>
#include "StageLevel.h"
#include "ShieldActor.h"
#include "Mechakoopa.h"
#include "ContentsEnums.h"
#include "LevelLoader.h"
Koopa::Koopa() {

}

Koopa::~Koopa() {
}

bool Koopa::IsCollisionAttack()
{
    return false;
}

bool Koopa::IsHold()
{
    return false;
}


bool Koopa::IsHoldable()
{
    return false;
}

bool Koopa::IsDie()
{
	return false;
}

void Koopa::SpinHit()
{
}

void Koopa::JumpHit(bool IsLeft)
{
}

void Koopa::FireHit()
{
}

void Koopa::BlockHit()
{
}

void Koopa::MonsterHit(bool IsLeft)
{
	ChangeAnimation("Damage");
	HP--;
	AnimTimer = HitAnimTime;

	if (0 >= HP)
	{
		StateValue = KoopaState::Die;
		dynamic_cast<StageLevel*>(GetLevel())->GetBGMPlayer().Stop();
		GameEngineResources::GetInst().SoundPlay("KoopaDie.wav");
		return;
	}
	StateValue = KoopaState::Hit;
}

void Koopa::Hold()
{
}

void Koopa::Kick(const float4& _Force)
{
}

void Koopa::Start()
{
	EnemyActor::Start();
	KoopaRender = CreateRender(RenderOrder::Monster);
	KoopaRender->SetScale(KoopaRenderScale);
	KoopaRender->SetPosition(KoopaRenderPos);
	KoopaRender->CreateAnimation({ .AnimationName = "Left_Appear", .ImageName = "LEFT_KOOPA.BMP" ,.InterTime = 0.2f,.Loop = false,.FrameIndex = {6,5,4,3,2,1,0},});
	KoopaRender->CreateAnimation({ .AnimationName = "Left_Idle", .ImageName = "LEFT_KOOPA.BMP" , .Start = 0, .End = 0 });
	KoopaRender->CreateAnimation({ .AnimationName = "Left_Damage", .ImageName = "LEFT_KOOPA.BMP" , .Start = 7, .End = 8, .InterTime = 0.2f });
	KoopaRender->CreateAnimation({ .AnimationName = "Right_Appear", .ImageName = "RIGHT_KOOPA.BMP" ,.InterTime = 0.2f,.Loop = false,.FrameIndex = {6,5,4,3,2,1,0},});
	KoopaRender->CreateAnimation({ .AnimationName = "Right_Idle", .ImageName = "RIGHT_KOOPA.BMP" , .Start = 0, .End = 0 });
	KoopaRender->CreateAnimation({ .AnimationName = "Right_Damage", .ImageName = "RIGHT_KOOPA.BMP" , .Start = 7, .End = 8, .InterTime = 0.2f });
	KoopaRender->ChangeAnimation("Left_Appear");
	KoopaRender->Off();

	PierrotRender = CreateRender(RenderOrder::Monster);
	PierrotRender->SetScale(PierrotRenderScale);
	PierrotRender->SetPosition(PierrotRenderPos);
	PierrotRender->CreateAnimation({ .AnimationName = "Left_Idle", .ImageName = "LEFT_Pierrot.BMP" , .Start = 0, .End = 1, .FrameTime = {5.0f, 0.1f} });
	PierrotRender->CreateAnimation({ .AnimationName = "Left_Damage", .ImageName = "LEFT_Pierrot.BMP" , .Start = 3, .End = 3,});
	PierrotRender->CreateAnimation({ .AnimationName = "Right_Idle", .ImageName = "RIGHT_Pierrot.BMP" , .Start = 0, .End = 1, .FrameTime = {5.0f, 0.1f} });
	PierrotRender->CreateAnimation({ .AnimationName = "Right_Damage", .ImageName = "RIGHT_Pierrot.BMP" , .Start = 3, .End = 3,});
	PierrotRender->ChangeAnimation("Left_Idle");

	PropellerRender = CreateRender(RenderOrder::Monster);
	PropellerRender->SetScale(PropellerRenderScale);
	PropellerRender->SetPosition(PropellerRenderPos);
	PropellerRender->CreateAnimation({ .AnimationName = "Idle", .ImageName = "Propeller.BMP", .Start = 0, .End = 0,});
	PropellerRender->CreateAnimation({ .AnimationName = "Spin", .ImageName = "Propeller.BMP", .Start = 0, .End = 3, .InterTime = 0.2f });
	PropellerRender->ChangeAnimation("Spin");

	Collision = CreateCollision(CollisionOrder::Monster);
	Collision->SetScale(KoopaCollisionScale);
	Collision->SetPosition(KoopaCollisionPos);
	Collision->SetDebugRenderType(CollisionType::CT_Rect);

	ShieldActor* PierrotActor = GetLevel()->CreateActor<ShieldActor>(RenderOrder::Monster);
	PierrotActor->SetOwner(this);
	PierrotActor->SetCollision(PierrotCollisionScale, PierrotCollisionPos);

	DirSetting(float4::Left);
}

void Koopa::Update(float _DeltaTime)
{
	switch (StateValue)
	{
	case KoopaState::Appear:
		AppearUpdate(_DeltaTime);
		break;
	case KoopaState::Move:
		MoveUpdate(_DeltaTime);
		break;
	case KoopaState::Spawn:
		break;
	case KoopaState::Attack:
		break;
	case KoopaState::Hit:
		HitUpdate(_DeltaTime);
		break;
	case KoopaState::Die:
		DieUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Koopa::Render(float _DeltaTime)
{
	//Collision->DebugRender();
}

void Koopa::AppearUpdate(float _DeltaTime)
{
	MoveTimer += _DeltaTime * 0.5f;
	float4 NextPos = float4::LerpClamp(float4{ 1500, 1000 }, float4{900, 1000}, MoveTimer);
	SetPos(NextPos);
	if (2.5f < MoveTimer)
	{
		StateValue = KoopaState::Move;
		MoveTimer = 0;
	}
	else if (1.0f < MoveTimer)
	{
		KoopaRender->On();
	}
}

void Koopa::MoveUpdate(float _DeltaTime)
{
	MoveTimer += _DeltaTime * 0.5f;
	if (1 > MoveTimer)
	{
		TurnLeft();
		ChangeAnimation("Idle");
		float4 NextPos = float4::LerpClamp(float4{ 900, 1000 }, float4{ 150, 1000 }, MoveTimer);
		SetPos(NextPos);
	}
	else if (2 > MoveTimer)
	{
		TurnRight();
		ChangeAnimation("Idle");
		float4 NextPos = float4::LerpClamp(float4{ 150, 1000 }, float4{ 900, 1000 }, MoveTimer - 1);
		SetPos(NextPos);
	}
	else
	{
		MoveTimer = 0;
	}

	SpawnTimer += _DeltaTime;
	if (SpawnTime < SpawnTimer)
	{
		SpawnTimer = 0;
		GetLevel()->CreateActor<Mechakoopa>()->SetPos(GetPos());
	}
}

void Koopa::HitUpdate(float _DeltaTime)
{
	AnimTimer -= _DeltaTime;
	if (0 > AnimTimer)
	{
		StateValue = KoopaState::Move;
		return;
	}
}

void Koopa::DieUpdate(float _DeltaTime)
{
	AnimTimer -= _DeltaTime;
	if (-2 > AnimTimer)
	{
		LevelLoader::ChangeLevel("Ending");
	}
	if (0 > AnimTimer)
	{
		EnemyActor::DieUpdate(_DeltaTime);
	}
}

void Koopa::ChangeAnimation(const std::string_view& _Name)
{
	std::string AnimStr = "";
	if (0 < DirValue.x)
	{
		AnimStr = "Right_";
	}
	else
	{
		AnimStr = "Left_";
	}

	AnimStr += _Name;
	KoopaRender->ChangeAnimation(AnimStr);
	PierrotRender->ChangeAnimation(AnimStr);
}
