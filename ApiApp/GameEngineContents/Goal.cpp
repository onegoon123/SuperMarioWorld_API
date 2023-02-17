#include "Goal.h"
#include "ContentsEnums.h"
#include "MarioGameCore.h"
#include "LevelLoader.h"
Goal::Goal() {

}

Goal::~Goal() {

}

void Goal::Start()
{
	Collision = CreateCollision(CollisionOrder::Check);
	Collision->SetScale(CollisionScale);
	Collision->SetDebugRenderType(CT_Rect);
}

void Goal::Update(float _DeltaTime)
{
	CollisionCheckParameter Check = { .TargetGroup = static_cast<int>(CollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect,  };
	if (true == Collision->Collision(Check))
	{
		LevelLoader::ChangeLevel("World");
	}
}

void Goal::Render(float _DeltaTime)
{
	//Collision->DebugRender();
}
