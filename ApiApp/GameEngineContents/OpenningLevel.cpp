#include "OpenningLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEnginePlatform/GameEngineWindow.h>

OpenningLevel::OpenningLevel() {

}

OpenningLevel::~OpenningLevel() {

}

void OpenningLevel::Loading()
{
	GameEngineDirectory Dir;
	Dir.Move("ContentsResources");
	Dir.Move("Image");

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TITLE.BMP"));

	
}

void OpenningLevel::Update()
{
	GameEngineImage* Image = GameEngineResources::GetInst().ImageFind("TITLE.BMP");

	GameEngineWindow::GetDoubleBufferImage()->TransCopy(Image, float4{ 0, 0 }, { 1024, 896 }, float4::Left, Image->GetImageScale());
}
