#include "WorldImage.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineLevel.h>
#include <GameEngineCore/GameEngineRender.h>
#include "MarioGameCore.h"
#include "ContentsEnums.h"
WorldImage::WorldImage() {

}

WorldImage::~WorldImage() {

}

void WorldImage::Start()
{
	{
		{
			GameEngineRender* Render = CreateRender("SEA.BMP", RenderOrder::Sky);
			Render->SetScale(GameEngineWindow::GetScreenSize());
			Render->SetPosition(Render->GetScale().half());
		}
		for (int i = 0; i < 42; i++)
		{
			GameEngineRender* Render = CreateRender(RenderOrder::BackGround);
			Render->SetScale({ 1024 ,8 });
			if (i % 2 == 0)
			{
				Render->CreateAnimation({ .AnimationName = "TIDE", .ImageName = "TIDE.BMP", .Start = 0, .End = 6, .InterTime = 0.2f });
			}
			else
			{
				Render->CreateAnimation({ .AnimationName = "TIDE", .ImageName = "TIDE.BMP",  .InterTime = 0.2f, .FrameIndex = {6, 5, 4, 3, 2, 1, 0} });
			}
			Render->ChangeAnimation("TIDE");
			Render->SetPosition({ 512, 168 + (i * 16.0f) });
		}
		{
			GameEngineRender* Render = CreateRender("WORLD1.BMP", RenderOrder::Map);
			Render->SetScaleToImage();
			Render->SetPosition(Render->GetScale().half());
			Render = CreateRender("WORLD1FRONT.BMP", RenderOrder::Monster);
			Render->SetScaleToImage();
			Render->SetPosition(Render->GetScale().half());
		}
		{
			GameEngineRender* Render = CreateRender(RenderOrder::Block);
			Render->SetScale({ 82 ,30 });
			Render->CreateAnimation({ .AnimationName = "CLOUD", .ImageName = "CLOUD.BMP",  .InterTime = 0.3f, .FrameIndex = {0, 1, 2, 3, 2, 1, 0} });
			Render->ChangeAnimation("CLOUD");
			Render->SetPosition({ 200, 300 });

		}
		{
			GameEngineRender* Render = CreateRender(RenderOrder::Block);
			Render->SetScale({ 82 ,30 });
			Render->CreateAnimation({ .AnimationName = "CLOUD", .ImageName = "CLOUD.BMP",  .InterTime = 0.3f, .FrameIndex = {0, 1, 2, 3, 2, 1, 0} });
			Render->ChangeAnimation("CLOUD");
			Render->SetPosition({ 575, 240 });
		}
		{
			GameEngineRender* Render = CreateRender(RenderOrder::Block);
			Render->SetScale({ 82 ,30 });
			Render->CreateAnimation({ .AnimationName = "CLOUD", .ImageName = "CLOUD.BMP",  .InterTime = 0.3f, .FrameIndex = {0, 1, 2, 3, 2, 1, 0} });
			Render->ChangeAnimation("CLOUD");
			Render->SetPosition({ 775, 280 });
		}
		{
			GameEngineRender* Render = CreateRender(RenderOrder::Block);
			Render->SetScale({ 82 ,30 });
			Render->CreateAnimation({ .AnimationName = "CLOUD", .ImageName = "CLOUD.BMP",  .InterTime = 0.3f, .FrameIndex = {0, 1, 2, 3, 2, 1, 0} });
			Render->ChangeAnimation("CLOUD");
			Render->SetPosition({ 635, 600 });
		}
		{
			GameEngineRender* Render = CreateRender(RenderOrder::Block);
			Render->SetScale({ 82 ,30 });
			Render->CreateAnimation({ .AnimationName = "CLOUD", .ImageName = "CLOUD.BMP",  .InterTime = 0.3f, .FrameIndex = {3, 2, 1, 0, 1, 2, 3} });
			Render->ChangeAnimation("CLOUD");
			Render->SetPosition({ 150, 400 });
			Render = CreateRender(RenderOrder::ForeGround);
			Render->SetScale({ 82 ,30 });
			Render->CreateAnimation({ .AnimationName = "CLOUD", .ImageName = "CLOUD.BMP",  .InterTime = 0.3f, .FrameIndex = {3, 2, 1, 0, 1, 2, 3} });
			Render->ChangeAnimation("CLOUD");
			Render->SetPosition({ 150, 320 });
		}
		{
			GameEngineRender* Render = CreateRender(RenderOrder::Block);
			Render->SetScale({ 82 ,30 });
			Render->CreateAnimation({ .AnimationName = "CLOUD", .ImageName = "CLOUD.BMP",  .InterTime = 0.3f, .FrameIndex = {3, 2, 1, 0, 1, 2, 3} });
			Render->ChangeAnimation("CLOUD");
			Render->SetPosition({ 615, 215 });
		}
		{
			GameEngineRender* Render = CreateRender(RenderOrder::Block);
			Render->SetScale({ 82 ,30 });
			Render->CreateAnimation({ .AnimationName = "CLOUD", .ImageName = "CLOUD.BMP",  .InterTime = 0.3f, .FrameIndex = {3, 2, 1, 0, 1, 2, 3} });
			Render->ChangeAnimation("CLOUD");
			Render->SetPosition({ 500, 460 });
		}
		{
			GameEngineRender* Render = CreateRender(RenderOrder::Block);
			Render->SetScale({ 82 ,30 });
			Render->CreateAnimation({ .AnimationName = "CLOUD", .ImageName = "CLOUD.BMP",  .InterTime = 0.3f, .FrameIndex = {3, 2, 1, 0, 1, 2, 3} });
			Render->ChangeAnimation("CLOUD");
			Render->SetPosition({ 820, 480 });
			Render = CreateRender(RenderOrder::Block);
			Render->SetScale({ 82 ,30 });
			Render->CreateAnimation({ .AnimationName = "CLOUD", .ImageName = "CLOUD.BMP",  .InterTime = 0.3f, .FrameIndex = {3, 2, 1, 0, 1, 2, 3} });
			Render->ChangeAnimation("CLOUD");
			Render->SetPosition({ 861, 480 });
			Render = CreateRender(RenderOrder::Block);
			Render->SetScale({ 82 ,30 });
			Render->CreateAnimation({ .AnimationName = "CLOUD", .ImageName = "CLOUD.BMP",  .InterTime = 0.3f, .FrameIndex = {3, 2, 1, 0, 1, 2, 3} });
			Render->ChangeAnimation("CLOUD");
			Render->SetPosition({ 630, 450 });
		}
	}
}

void WorldImage::Update(float _DeltaTime)
{
}
