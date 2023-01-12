#include "TitleLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRender.h>
#include "TitleImage.h"

TitleLevel::TitleLevel() {

}

TitleLevel::~TitleLevel() {

}

void TitleLevel::Loading()
{
	GameEngineDirectory Dir;
	Dir.Move("ContentsResources");
	Dir.Move("Image");

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("STAGE1.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MARIO.BMP"))->Cut(19, 37);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SKY.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TITLE.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("BACKGROUND01.BMP"));

	CreateActor<TitleImage>();
}

void TitleLevel::Update()
{
	
}
