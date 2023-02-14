#include "UIManager.h"
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"
UIManager::UIManager() {

}

UIManager::~UIManager() {

}

void UIManager::Start()
{
	UIImage = CreateRender("PLAYUI.bmp", RenderOrder::UI);
	UIImage->SetScaleToImage();
	UIImage->EffectCameraOff();
	UIImage->SetPosition({512, 128});
}

void UIManager::Update(float _DeltaTime)
{
}

void UIManager::Render(float _DeltaTime)
{
}
