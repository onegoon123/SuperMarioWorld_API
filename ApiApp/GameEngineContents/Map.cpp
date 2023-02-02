#include "Map.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"

Map* Map::MainMap = nullptr;

Map::Map() {

}

Map::~Map() {

}

void Map::SetImage(const std::string_view& _SkyName, const std::string_view& _BackGroundName, const std::string_view& _StageName)
{

	SkyName = _SkyName;
	BackGroundName = _BackGroundName;
	StageName = _StageName;

	SkyRender = CreateRender(SkyName, RenderOrder::Sky);
	SkyRender->SetScale(GameEngineWindow::GetScreenSize());
	SkyRender->SetPosition(SkyRender->GetScale().half());
	SkyRender->EffectCameraOff();
	SkyRender->Off();

	BackGroundRender = CreateRender(BackGroundName, RenderOrder::BackGround);
	BackGroundRender->SetScale(BackGroundRender->GetImage()->GetImageScale());
	BackGroundRender->SetPosition(BackGroundRender->GetImage()->GetImageScale().half());
	BackGroundRender->Off();

	StageRender = CreateRender(StageName, RenderOrder::Map);
	StageRender->SetScale(StageRender->GetImage()->GetImageScale());
	StageRender->SetPosition(StageRender->GetScale().half());
	StageRender->Off();
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

void Map::Start()
{
	
}

void Map::Update(float _DeltaTime)
{
}

void Map::ObjectOn()
{
	SkyRender->On();
	BackGroundRender->On();
	StageRender->On();

	std::vector<GameEngineActor*>::iterator StartIter = Actors.begin();
	std::vector<GameEngineActor*>::iterator EndIter = Actors.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		(*StartIter)->On();
	}
}

void Map::ObjectOff()
{
	SkyRender->Off();
	BackGroundRender->Off();
	StageRender->Off();

	std::vector<GameEngineActor*>::iterator StartIter = Actors.begin();
	std::vector<GameEngineActor*>::iterator EndIter = Actors.end();
	for (; StartIter != EndIter; ++StartIter)
	{
		(*StartIter)->Off();
	}
}
