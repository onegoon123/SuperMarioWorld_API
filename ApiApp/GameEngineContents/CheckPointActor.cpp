#include "CheckPointActor.h"
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnums.h"
CheckPointActor::CheckPointActor() {

}

CheckPointActor::~CheckPointActor() {

}

void CheckPointActor::SetCheckPoint(int _CheckPoint, const float4& _Pos)
{
	CheckPoint = _CheckPoint;
	SetPos(_Pos);
}

void CheckPointActor::Start()
{
	GameEngineRender* Render = CreateRender(RenderOrder::Map);

	Collision = CreateCollision(CollisionOrder::Check);
	Collision->SetScale(CollisionScale);
	Collision->SetPosition(CollisionScale);
}

void CheckPointActor::Update(float _DeltaTime)
{
}

void CheckPointActor::Render(float _DeltaTime)
{
}
