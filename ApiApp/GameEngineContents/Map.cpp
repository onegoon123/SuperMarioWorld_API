#include "Map.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"
Map::Map() {

}

Map::~Map() {

}

void Map::Start()
{
	SkyRender = CreateRender("SKY.BMP", RenderOrder::Sky);
	SkyRender->SetScale({ 1024,896 });
	SkyRender->SetPosition(SkyRender->GetScale().half());
	SkyRender->EffectCameraOff();

	BackGroundRender = CreateRender("BACKGROUND01.BMP", RenderOrder::BackGround);
	BackGroundRender->SetScale(BackGroundRender->GetImage()->GetImageScale());
	BackGroundRender->SetPosition(BackGroundRender->GetImage()->GetImageScale().half());
	
	StageRender = CreateRender("STAGE1.BMP", RenderOrder::Map);
	StageRender->SetScale({ 20480, 1728 });
	StageRender->SetPosition(StageRender->GetScale().half());
}

void Map::Update(float _DeltaTime)
{
}
