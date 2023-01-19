#include "Map.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"
Map::Map() {

}

Map::~Map() {

}

void Map::Start()
{
	//SetMove(GameEngineWindow::GetScreenSize().half());

	
	{
		GameEngineRender* Render = CreateRender("SKY.BMP", RenderOrder::Sky);
		Render->SetScale({ 1024,896 });
		Render->SetPosition( GameEngineWindow::GetScreenSize().half());
	}
	{
		GameEngineRender* Render = CreateRender("BACKGROUND01.BMP", RenderOrder::BackGround);
		Render->SetScale({ 2048,1728 });
		float4 pos = { 0,-100 };
		Render->SetPosition(pos + GameEngineWindow::GetScreenSize().half());
	}

	GameEngineRender* MainRender = CreateRender("STAGE1.BMP", RenderOrder::Map);
	MainRender->SetPosition({ 512, 32 });
	MainRender->SetScale({ 1024, 1728 });

}
