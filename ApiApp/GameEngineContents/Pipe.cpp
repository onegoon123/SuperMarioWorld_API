#include "Pipe.h"
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineCollision.h>
#include "ContentsEnums.h"
#include "LevelLoader.h"
Pipe::Pipe() {

}

Pipe::~Pipe() {

}

void Pipe::Start()
{
	Collision = CreateCollision(CollisionOrder::Check);
	Collision->SetScale(CollisionSize);
	Collision->SetDebugRenderType(CT_Rect);
}

void Pipe::Update(float _DeltaTime)
{
	CollisionCheckParameter Check = { .TargetGroup = static_cast<int>(CollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect };
	if (true == Collision->Collision(Check) && GameEngineInput::IsPress("Down"))
	{
		LevelLoader::ChangeLevel("Basement1");
	}
}

void Pipe::Render(float _DeltaTime)
{
	Collision->DebugRender();
}
