#include "Map.h"
#include <GameEngineBase/GameEngineMath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"

Map* Map::MainMap = nullptr;

Map::Map() {

}

Map::~Map() {

}

void Map::SetImage(const std::string_view& _BackGroundName, const std::string_view& _StageName, const std::string_view& _StageColName)
{
	BackGroundName = _BackGroundName;
	StageName = _StageName;
	StageColName = _StageColName;


	if ("" != BackGroundName)
	{
		BackGroundRender = CreateRender(BackGroundName, RenderOrder::BackGround);
		BackGroundRender->SetScale(BackGroundRender->GetImage()->GetImageScale());
		BackGroundRender->SetPosition(BackGroundRender->GetImage()->GetImageScale().half());
		BackGroundRender->Off();

		for (int i = 1; i <= 15; i++)
		{
			GameEngineRender* Render = CreateRender(BackGroundName, RenderOrder::BackGround);
			if (true == IsBackAnim)
			{
				Render->CreateAnimation({ .AnimationName = "BackGroundAnim", .ImageName = BackGroundName, .Start = 0, .End = 3 });
				Render->SetScale({ 2048, 1728 });
				Render->SetPosition({ 1024, 864 });
				Render->SetMove(float4::Right * 2048 * i);
				Render->ChangeAnimation("BackGroundAnim");
			}
			else
			{
				Render->SetScale(BackGroundRender->GetImage()->GetImageScale());
				Render->SetPosition(BackGroundRender->GetImage()->GetImageScale().half() + float4::Right * BackGroundRender->GetImage()->GetImageScale().x * i);
			}
		}
	}

	if ("" != StageName)
	{
		StageRender = CreateRender(StageName, RenderOrder::Map);
		StageRender->SetScale(StageRender->GetImage()->GetImageScale());
		StageRender->SetPosition(StageRender->GetScale().half());
		StageRender->Off();
	}

}

void Map::SetStartPos(const std::vector<float4>& _StartPos)
{
}

void Map::NewActor(const GameEngineActor* _Actor)
{
}

void Map::NewActor(const std::vector<GameEngineActor*> _Actors)
{
}

void Map::MoveMap(int _StartPosIndex)
{
	if (nullptr != MainMap)
	{
		if (this == MainMap)
		{
			MsgAssert("현재 사용중인 맵을 다시 사용하려 했습니다");
		}
		MainMap->ObjectOff();
	}
	MainMap = this;
	ObjectOn();
}

void Map::Update(float _DeltaTime)
{
}

void Map::ObjectOn()
{
	if (nullptr != BackGroundRender)
	{
		BackGroundRender->On();
	}
	if (nullptr != StageRender)
	{
		StageRender->On();
	}

	std::vector<GameEngineActor*>::iterator StartIter = Actors.begin();
	std::vector<GameEngineActor*>::iterator EndIter = Actors.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		(*StartIter)->On();
	}
}

void Map::ObjectOff()
{
	if (nullptr != BackGroundRender)
	{
		BackGroundRender->Off();
	}
	if (nullptr != StageRender)
	{
		StageRender->Off();
	}

	std::vector<GameEngineActor*>::iterator StartIter = Actors.begin();
	std::vector<GameEngineActor*>::iterator EndIter = Actors.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		(*StartIter)->Off();
	}
}
