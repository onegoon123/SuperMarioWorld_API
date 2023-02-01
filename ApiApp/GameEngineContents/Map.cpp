#include "Map.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"
Map::Map() {

}

Map::~Map() {

}

void Map::NewMap(std::string_view _SkyName, std::string_view _BackGroundName, std::string_view _StageName)
{

	SkyName = _SkyName;
	BackGroundName = _BackGroundName;
	StageName = _StageName;

	SkyRender = CreateRender(SkyName, RenderOrder::Sky);
	SkyRender->SetScale(GameEngineWindow::GetScreenSize());
	SkyRender->SetPosition(SkyRender->GetScale().half());
	SkyRender->EffectCameraOff();

	BackGroundRender = CreateRender(BackGroundName, RenderOrder::BackGround);
	BackGroundRender->SetScale(BackGroundRender->GetImage()->GetImageScale());
	BackGroundRender->SetPosition(BackGroundRender->GetImage()->GetImageScale().half());

	StageRender = CreateRender(StageName, RenderOrder::Map);
	StageRender->SetScale(StageRender->GetImage()->GetImageScale());
	StageRender->SetPosition(StageRender->GetScale().half());
}

void Map::Start()
{
	
}

void Map::Update(float _DeltaTime)
{
}
