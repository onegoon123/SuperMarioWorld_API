#include "LevelLoader.h"
#include <GameEngineCore/GameEngineLevel.h>
#include "MarioGameCore.h"
#include "ContentsEnums.h"

LevelLoader* LevelLoader::MainLoader = nullptr;

LevelLoader::LevelLoader()
	: IsFadeIn(true), IsFadeOut(true)
{

}

LevelLoader::~LevelLoader() {
}

void LevelLoader::ChangeLevel(const std::string_view& _Name)
{
	MainLoader->LevelName = _Name;
	MainLoader->State = FadeState::FadeOut;
}

void LevelLoader::Start()
{
	FadeRender = CreateRender("ALLBLACK.BMP", RenderOrder::Fade);
	FadeRender->EffectCameraOff();
	FadeRender->SetScaleToImage();
	FadeRender->SetPosition(FadeRender->GetScale().half());
}

void LevelLoader::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainLoader = this;
	if (true == IsFadeIn)
	{
		State = FadeState::FadeIn;
		FadeRender->SetAlpha(255);
		Timer = 255;
	}
}

void LevelLoader::Update(float _DeltaTime)
{
	switch (State)
	{
	case FadeState::FadeIn:
		FadeInUpdate(_DeltaTime);
		break;
	case FadeState::FadeOut:
		FadeOutUpdate(_DeltaTime);
		break;
	case FadeState::STOP:
		break;
	default:
		break;
	}
}

void LevelLoader::FadeInUpdate(float _DeltaTime)
{
	Timer -= Speed * _DeltaTime;
	if (0 >= Timer)
	{
		FadeRender->SetAlpha(0);
		State = FadeState::STOP;
		return;
	}
	FadeRender->SetAlpha(static_cast<int>(Timer));
}

void LevelLoader::FadeOutUpdate(float _DeltaTime)
{
	Timer += Speed * _DeltaTime;
	if (255 <= Timer)
	{
		MarioGameCore::GetInst().ChangeLevel(LevelName);
		return;
	}
	FadeRender->SetAlpha(static_cast<int>(Timer));
}
