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

	if ("" != StageName)
	{
		StageRender = CreateRender(StageName, RenderOrder::Map);
		StageSize = StageRender->GetImage()->GetImageScale();
		StageRender->SetScale(StageSize);
		StageRender->SetPosition(StageSize.half());
		StageRender->Off();
	}

	if ("" != BackGroundName)
	{
		BackGroundRender = CreateRender(BackGroundName, RenderOrder::BackGround);
		if (true == IsBackAnim)
		{
			BackGroundSize = BackGroundRender->GetImage()->GetImageScale();
			BackGroundSize.x /= 4;
		}
		else
		{
			BackGroundSize = BackGroundRender->GetImage()->GetImageScale();
		}
		BackGroundRender->SetScale(BackGroundSize);
		BackGroundRender->SetPosition(BackGroundSize.half());
		BackGroundRender->Off();

		int BackGroundNum = StageSize.ix() / BackGroundSize.ix();
		for (int i = 1; i <= BackGroundNum; i++)
		{
			GameEngineRender* Render = CreateRender(BackGroundName, RenderOrder::BackGround);
			if (true == IsBackAnim)
			{
				Render->CreateAnimation({ .AnimationName = "BackGroundAnim", .ImageName = BackGroundName, .Start = 0, .End = 3 });
				Render->ChangeAnimation("BackGroundAnim");
			}
			Render->SetScale(BackGroundSize);
			Render->SetPosition(BackGroundSize.half());
			Render->SetMove({ BackGroundSize.x * i, 0 });
		}
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
