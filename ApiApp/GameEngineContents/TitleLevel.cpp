#include "TitleLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineWindow.h>

TitleLevel::TitleLevel() {

}

TitleLevel::~TitleLevel() {

}

void TitleLevel::Loading()
{
	GameEngineDirectory Dir;
	Dir.Move("ContentsResources");
	Dir.Move("Image");

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TITLE.BMP"));

	CreateActor<TitleImage>();
}

void TitleLevel::Update()
{
	
}
